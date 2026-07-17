/*
 * Smart Night Vision Security System
 * ----------------------------------
 * Arduino UNO Controller
 *
 * Features:
 * - Automatic Day/Night Detection using LDR
 * - IR LED Control
 * - Day Indicator LED
 * - Ultrasonic Intruder Detection
 * - Buzzer Alert
 */

const int LDR_PIN = A0;

// LED Outputs
const int IR_LED_PIN = 12;
const int DAY_LED_PIN = 13;

// Ultrasonic Sensor Pins
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;

// Buzzer Pin
const int BUZZER_PIN = 11;

// System Thresholds
const int LIGHT_THRESHOLD = 400;
const int DISTANCE_THRESHOLD = 12;   // cm

// Speed of sound (cm/µs)
const float SOUND_SPEED = 0.0343;

void setup() {

  // Configure Output Pins
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(DAY_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Configure Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start Serial Monitor
  Serial.begin(9600);
}

void loop() {

  // =====================================
  // Day / Night Detection
  // =====================================

  int lightLevel = analogRead(LDR_PIN);

  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  if (lightLevel < LIGHT_THRESHOLD) {

    // Night Mode
    digitalWrite(IR_LED_PIN, HIGH);
    digitalWrite(DAY_LED_PIN, LOW);

  } else {

    // Day Mode
    digitalWrite(IR_LED_PIN, LOW);
    digitalWrite(DAY_LED_PIN, HIGH);

  }

  // =====================================
  // Distance Measurement
  // =====================================

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  int distance = duration * SOUND_SPEED / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // =====================================
  // Intruder Detection
  // =====================================

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {

    digitalWrite(BUZZER_PIN, HIGH);

  } else {

    digitalWrite(BUZZER_PIN, LOW);

  }

  delay(300);
}