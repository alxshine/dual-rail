char buffer[255];
uint8_t plaintext[16];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    for (int i = 0; i < 16; i++) {
      plaintext[i] = 0;
    }
    Serial.readBytesUntil('\n', buffer, 255);
    sscanf(buffer, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n", plaintext, plaintext + 1,
           plaintext + 2, plaintext + 3, plaintext + 4, plaintext + 5, plaintext + 6, plaintext + 7,
           plaintext + 8, plaintext + 9, plaintext + 10, plaintext + 11, plaintext + 12, plaintext + 13, plaintext + 14, plaintext + 15);
    Serial.print("Arduino: ");
    for (int i = 0; i < 16; i++) {
      Serial.print(plaintext[i]);
      if (i < 15)
        Serial.print(",");
    }
    Serial.println();
  }
}
