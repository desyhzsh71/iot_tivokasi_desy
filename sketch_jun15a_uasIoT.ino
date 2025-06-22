#include <WiFi.h>
#include <HTTPClient.h>

#define led_merah 2
#define buzzer 21
#define trigger 19
#define echo 18

// SSID & password WiFi (pakai hotspot HP)
const char* ssid = "Hayiii";
const char* password = "desiekaa";

// Alamat endpoint Node-RED
const char* serverName = "http://192.168.114.8:1880/jarak";

unsigned long lastSend = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke SSID: ");
  Serial.println(ssid);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi terhubung!");
    Serial.print("IP ESP32: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nGagal terhubung ke WiFi!");
  }
}

void loop() {
  long waktu, jarak;

  // Trigger sensor ultrasonik
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Baca durasi echo dengan timeout 30ms
  waktu = pulseIn(echo, HIGH, 30000);

  if (waktu == 0) {
    jarak = 0;  // Tidak ada echo, anggaplah jaraknya 0
  } else {
    jarak = (waktu / 2) / 29.1;  // Menghitung jarak dalam cm
  }

  // Tampilkan jarak di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  // Kontrol LED dan buzzer berdasarkan jarak
  if (jarak > 0 && jarak <= 10) {
    digitalWrite(led_merah, HIGH);
    tone(buzzer, 1000);
  } else {
    digitalWrite(led_merah, LOW);
    noTone(buzzer);
  }

  // Mengirim data ke Node-RED setiap 1 detik
  if (millis() - lastSend > 1000) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      String jsonData = "{\"jarak\":" + String(jarak) + "}";

      int httpResponseCode = http.POST(jsonData);

      if (httpResponseCode > 0) {
        Serial.print("Data terkirim! Kode: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Gagal kirim. Error: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("WiFi tidak terhubung saat kirim data.");
    }
    lastSend = millis();
  }

  delay(100);  // Delay kecil sebagai pembacaan sensor lancar
}