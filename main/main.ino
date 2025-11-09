#include <Servo.h>

Servo panServo;
Servo tiltServo;

int X_INPUT = A0;
int Y_INPUT = A1;
int PAN_SERVO = 10;
int TILT_SERVO = 11;
int SW = 7;
int LED1 = 5;

// Calibration values - adjust these to find the stop point
int PAN_STOP = 90;   // Try values between 85-95
int TILT_STOP = 90;  // Try values between 85-95
int SPEED = 25; // lower = slower

int buttonState = 0;

void setup() {
  panServo.attach(PAN_SERVO);
  tiltServo.attach(TILT_SERVO);
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);

  // LEDS
  pinMode(LED1, OUTPUT);

  // starting with LEDs off
  digitalWrite(LED1, LOW);
}

void loop() {
  int xValue = analogRead(X_INPUT);
  int yValue = analogRead(Y_INPUT);

   buttonState = digitalRead(SW);

  // Map around the calibrated stop values
  int panSpeed = map(xValue, 0, 1023, PAN_STOP - SPEED, PAN_STOP + SPEED);
  int tiltSpeed = map(yValue, 0, 1023, TILT_STOP - SPEED, TILT_STOP + SPEED);

  panServo.write(panSpeed);
  tiltServo.write(tiltSpeed);


  // Serial.print("Pan: ");
  // Serial.print(panSpeed);
  // Serial.print(" | Tilt: ");
  // Serial.println(tiltSpeed);

  // recognizes button clicks
  if (buttonState == LOW) {
    Serial.println("turning on led");
    digitalWrite(LED1, HIGH);
    delay(5000);
  } 
  
  delay(15);
}
