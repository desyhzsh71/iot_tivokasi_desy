#include <Arduino.h>

// put function declarations here:
int tombol1 = 22; // Pin untuk tombol 1
int tombol2 = 21; // Pin untuk tombol 2
int tombol3 = 19; // Pin untuk tombol 3

int lampuMerah = 13; // LED Merah
int lampuKuning = 12; // LED Kuning
int lampuHijau = 14; // LED Hijau

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(tombol1, INPUT_PULLUP);
  pinMode(tombol2, INPUT_PULLUP);
  pinMode(tombol3, INPUT_PULLUP);

  pinMode(lampuMerah, OUTPUT);
  pinMode(lampuKuning, OUTPUT);
  pinMode(lampuHijau, OUTPUT);
}

void loop() {
  // Tombol 1 ditekan, lampu merah kedip 3x
  if (digitalRead(tombol1) == LOW) {
    while (digitalRead(tombol1) == LOW);    
    for (int i = 0; i < 3; i++) {
      digitalWrite(lampuMerah, HIGH);
      delay(500);
      digitalWrite(lampuMerah, LOW);
      delay(500);
    }
  }

  // Tombol 2 ditekan, lampu merah dan hijau kedip bergantian
  if(digitalRead(tombol2) == LOW) {
    while (digitalRead(tombol2) == LOW);
    for (int i = 0; i < 5; i++) {
      digitalWrite(lampuMerah, HIGH);
      digitalWrite(lampuHijau, LOW);
      delay(500);

      digitalWrite(lampuMerah, LOW);
      digitalWrite(lampuHijau, HIGH);
      delay(500);
    }
    digitalWrite(lampuHijau, LOW);
  }

  // Tombol 3 ditekan, lampu merah, kuning, hijau kedip bergantian
  if (digitalRead(tombol3) == LOW) {
    while (digitalRead(tombol3) == LOW);
    for (int i = 0; i < 5; i++) {
      digitalWrite(lampuMerah, HIGH);
      delay(500);
      digitalWrite(lampuMerah, LOW);

      digitalWrite(lampuKuning, HIGH);
      delay(500);
      digitalWrite(lampuKuning, LOW);

      digitalWrite(lampuHijau, HIGH);
      delay(500);
      digitalWrite(lampuHijau, LOW);
    }
  }
}