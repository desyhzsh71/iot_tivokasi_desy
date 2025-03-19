#include <Wire.h>              // Library protokol komunikasi I2C
#include <LiquidCrystal_I2C.h> // Library layar LCD I2C
#include <DHT.h>               // Library sensor DHT22

// Mendefinisikan pin
#define DHTPIN 4      // Pin data DHT22
#define LIGHT_PIN 34  // Pin fotoresistor

// Inisialisasi sensor DHT
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi LCD (sesuai alamat I2C dan ukuran LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Inisialisasi sensor DHT
  dht.begin();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.println("System initialized");
}

void loop() {
  // Membaca suhu dan kelembaban
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Membaca intensitas cahaya
  int lightIntensity = analogRead(LIGHT_PIN);
  float lightPercentage = map(lightIntensity, 0, 4095, 0, 100);

  // Memeriksa apakah ada pembacaan yang gagal
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(temperature);
    Serial.println(F("°C"));
  }

  Serial.print(F("Light: "));
  Serial.print(lightPercentage);
  Serial.println(F("%"));

  // Clear LCD
  lcd.clear();

  // Menampilkan data pada LCD
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temperature, 1) + "°C H:" + String(humidity, 1) + "%");
  lcd.setCursor(0, 1);
  lcd.print("Cahaya:" + String(lightPercentage, 1) + "%");

  // Waktu delay untuk menunggu sebelum membaca berikutnya
  delay(2000);
}