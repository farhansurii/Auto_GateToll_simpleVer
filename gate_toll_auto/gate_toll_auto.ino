#include <ESP32Servo.h>

#define SERVO_PIN 26
#define BUZZER_PIN 2

#define LED_GREEN_PIN 32  // LED hijau
#define LED_RED_PIN 33    // LED merah

Servo servoMotor;

#define SOUND_SPEED 0.034 // satuan cm/us

const int trigPin = 5;
const int echoPin = 18;

long duration; // satuan us
float distance; // satuan cm

const int setpoint = 7; // satuan cm

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(90);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  readDistance();
  servoControl();
  delay(50); // delay agar ada jeda singkat

}

void readDistance() {
  // trigger pin harus rendah dahulu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // kirim pulsa trigger selama 10 us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // baca durasi pulsa echo
  duration = pulseIn(echoPin, HIGH);
  
  // hasil jarak
  distance = (duration * SOUND_SPEED) / 2;
  Serial.println(distance);
}

void servoControl() {
  if (distance < setpoint) {
    // Jarak kurang dari 10 cm - putar servo ke 90 derajat
    servoMotor.write(180);
    Serial.println("servo naik");
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    buzzerControl();
    Serial.println("LED: Green ON, Red OFF");
    delay(1700);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);
    Serial.println("LED: Green OFF, Red ON");
    servoMotor.write(90);
    Serial.println("servo turun");
  }
}

void buzzerControl() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}