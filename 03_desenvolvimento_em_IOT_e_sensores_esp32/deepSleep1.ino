#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP 3
#define TIME_TO_SLEEP_S TIME_TO_SLEEP * uS_TO_S_FACTOR
#define LED 26

RTC_DATA_ATTR int bootCount = 0;

void setup(){
    Serial.begin(115200);
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    Serial.println("Blinking the LED");
    for (int i=0; i<3; i++) {
        digitalWrite(LED, HIGH); delay(300);
        digitalWrite(LED, LOW); delay(300);
    }
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_S);
    Serial.println("Sleep " + String(TIME_TO_SLEEP) + " S");
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}