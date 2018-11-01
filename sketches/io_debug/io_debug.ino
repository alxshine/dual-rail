uint8_t plaintext[17];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    for (int i = 0; i < 17; i++) {
      plaintext[i] = 0;
    }
    Serial.readBytesUntil('\n', plaintext, 17);
    Serial.print("Arduino: ");
    for (int i = 0; i < 16; i++) {
      Serial.write(plaintext[i]);
    }
    Serial.println();
  }
}
