#define PIN 2
#define DELAY 500

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN, HIGH);
  delay(DELAY);
  digitalWrite(PIN, LOW);
  delay(DELAY);
}
