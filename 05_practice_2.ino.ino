#define PIN_LED 7
unsigned int count, toggle;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  count = 0;
  toggle = 0;
  digitalWrite(PIN_LED, toggle);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  count += 1;
  if (count <= 10) {
    toggle = toggle_state(toggle);
    digitalWrite(PIN_LED, toggle);
    delay(100);
    Serial.println(toggle);
  }
  else {
  digitalWrite(PIN_LED, 1);
  delay(1000);
  }
}

int toggle_state(int toggle){
  return 1 - toggle;
}
