volatile boolean ledOn = false;
const int pinoBotao = 23;
const int pinoLed = 32;

// const int TEMPO_DEBOUNCE = 100;
// unsigned long ultimo_acionamento = 0;

void IRAM_ATTR buttonPressed_ISR() {
  ledOn = !ledOn;
  // if ( (xTaskGetTickCount() - ultimo_acionamento)
  //   >= TEMPO_DEBOUNCE ) {
  //   ledOn = !ledOn;
  //   ultimo_acionamento = xTaskGetTickCount();
  // }
}
void setup() {
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoLed, LOW);
  attachInterrupt(pinoBotao, buttonPressed_ISR, RISING);
}
void loop() {
  if(ledOn) digitalWrite(pinoLed,LOW);
  if(!ledOn) digitalWrite(pinoLed,HIGH);
}
