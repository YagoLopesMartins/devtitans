#define LED 32
#define pinoLDRLow 2
#define pinoLDRHigh 4

void IRAM_ATTR turnLEDOn_ISR()
{
  digitalWrite(LED,HIGH);
}
void IRAM_ATTR turnLEDOff_ISR()
{
  digitalWrite(LED,LOW);
}

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(pinoLDRLow,INPUT);
  pinMode(pinoLDRHigh,INPUT);
  attachInterrupt(pinoLDRLow, turnLEDOn_ISR, RISING);
  attachInterrupt(pinoLDRHigh, turnLEDOff_ISR, FALLING);
}
void loop() {
}