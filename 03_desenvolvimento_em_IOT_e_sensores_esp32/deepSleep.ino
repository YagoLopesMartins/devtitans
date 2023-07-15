#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP 5
#define TIME_TO_SLEEP_S TIME_TO_SLEEP * uS_TO_S_FACTOR
#define LED 26

// acordando por toque
#define Threshold 40
RTC_DATA_ATTR int bootCount = 0;


void setup(){
    Serial.begin(115200);
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    Serial.println("Blinking the LED");
    for (int i=0; i<5; i++) {
        digitalWrite(LED, HIGH); delay(500);
        digitalWrite(LED, LOW); delay(500);
    }
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_S);
    Serial.println("Sleep " + String(TIME_TO_SLEEP) + " S");
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");

    // acordando por toque
    esp_sleep_enable_touchpad_wakeup();

    touchAttachInterrupt(T4, callback, Threshold);
}