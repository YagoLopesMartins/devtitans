#define pinButton 23
#define pinLedVermelho 32
#define pinLedVerde 25
boolean pressLedVermelho = false;


void setup(){
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
}

void loop(){
  digitalWrite(pinLedVerde, HIGH);
  delay (200);
  digitalWrite(pinLedVerde, LOW);
  delay (200);
    if (digitalRead(pinButton))
      pressLedVermelho = true;
    if (digitalRead(pinButton)==LOW && pressLedVermelho) {
      digitalWrite(pinLedVermelho,!digitalRead(pinLedVermelho));
      pressLedVermelho = false;
    }
}