#define Threshold 40
RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

void setup(){
    Serial.begin(115200);
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    print_wakeup_touchpad();
    touchAttachInterrupt(T4, callback, Threshold);
    esp_sleep_enable_touchpad_wakeup();
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}
void print_wakeup_touchpad(){
    touchPin = esp_sleep_get_touchpad_wakeup_status();
    switch(touchPin)
    {
        case 0 : Serial.println("Touch on GPIO 4"); break;
        case 1 : Serial.println("Touch on GPIO 0"); break;
        case 2 : Serial.println("Touch on GPIO 2"); break;
        case 3 : Serial.println("Touch on GPIO 15"); break;
        case 4 : Serial.println("Touch on GPIO 13"); break;
        case 5 : Serial.println("Touch on GPIO 12"); break;
        case 6 : Serial.println("Touch on GPIO 14"); break;
        case 7 : Serial.println("Touch on GPIO 27"); break;
        case 8 : Serial.println("Touch on GPIO 33"); break;
        case 9 : Serial.println("Touch on GPIO 32"); break;
        default : Serial.println("Wakeup not by touchpad");
        break;
    }
}