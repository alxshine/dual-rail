#define PIN 9
#define DELAY 500

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
  Serial.begin(19200);
  digitalWrite(PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN, HIGH);
  Serial.println("high");
  delay(DELAY);
  digitalWrite(PIN, LOW);
  Serial.println("low");
  delay(DELAY);
}
