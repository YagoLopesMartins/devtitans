RTC_DATA_ATTR int bootCount = 0;
void setup(){
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1);
    Serial.println("Blinking the LED");
    for (int i=0; i<5; i++) {
        digitalWrite(LED, HIGH); delay(500);
        digitalWrite(LED, LOW); delay(500);
    }
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}