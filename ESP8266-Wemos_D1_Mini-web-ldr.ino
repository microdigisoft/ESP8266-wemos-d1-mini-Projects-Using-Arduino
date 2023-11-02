const int ledPin = 5;
const int ldrPin = A0;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  pinMode(ldrPin, INPUT);

}

void loop() {

  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 20) {

    digitalWrite(ledPin, HIGH);
    Serial.print(ldrStatus);
    Serial.print("LED is ON");
    Serial.println("");
    delay(1000);
  }

  else {
    Serial.print(ldrStatus);
    digitalWrite(ledPin, LOW);
    Serial.println("LED is OFF");
    Serial.println("");
    delay(1000);
  }

}
