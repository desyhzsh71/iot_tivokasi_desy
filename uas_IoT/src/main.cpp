#include <Arduino.h>

#define led_merah 5

#define buzzer 19
#define trigger 17
#define echo 18

int frekuensi = 1000; // Frekuensi buzzer dalam Hz

void setup() {
  Serial.begin(9600);
  pinMode(led_merah, OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  long waktu, jarak;

  // Mengirimkan pulsa trigger ke sensor ultrasonik
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Mengukur durasi pulsa echo
  waktu = pulseIn(echo, HIGH);

  // Menghitung jarak
  jarak = (waktu / 2) / 29.1;

  // Menampilkan jarak pada Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak <= 10) {
    digitalWrite(led_merah, HIGH); // LED menyala
    tone(buzzer, 1000);            // Buzzer bunyi
  } else {
    digitalWrite(led_merah, LOW);  // LED mati
    noTone(buzzer);                // Buzzer mati
  }

  delay(500); // Delay 500 ms sebelum pembacaan berikutnya
}