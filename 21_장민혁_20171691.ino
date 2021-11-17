#include <Servo.h>

// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10
#define _DIST_ALPHA 0.35 // EMA weight of new sample (range: 0 to 1). Setting this value to 1 effectively disables EMA filter.
#define _DUTY_MIN 550 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1475 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counterclockwise position (180 degree)

float former_reading, alpha;
Servo myservo;
int a, b; // unit: mm

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  myservo.attach(PIN_SERVO); 
  alpha = _DIST_ALPHA;
  former_reading = 0;
  
// initialize serial port
  Serial.begin(57600);
  myservo.writeMicroseconds(_DUTY_NEU);
  delay(1000);

  a = 92;
  b = 396;
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
  float raw_dist = ir_distance();
  if (former_reading > raw_dist+former_reading*(0.15)) {
    raw_dist = former_reading;
  }
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  if(dist_cali > 255) {
    digitalWrite(PIN_LED, 0);
    myservo.writeMicroseconds(1150);
    delay(20);
  }
  else {
    digitalWrite(PIN_LED, 255);
    myservo.writeMicroseconds(1620);
    delay(20);
  }
  former_reading = raw_dist;
  delay(20);
}
