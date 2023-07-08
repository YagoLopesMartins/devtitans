#include <WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED 2
#define BUILTIN_LED_2 3

const char* ssid = "ICOMP_1A";
const char* password = "1comp@14#";
const char* mqtt_server = "test.mosquitto.org";
  

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1' && (char)payload[1] == 'L') {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED on 
    Serial.println("LED1 LIGADO");
  } else if ((char)payload[0] == '1' && (char)payload[1] == 'D'){
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED off
    Serial.println("LED1 DESLIGADO");
  }else if ((char)payload[0] == '2' && (char)payload[1] == 'L'){
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED on
    Serial.println("LED2 LIGADO");
  }else if ((char)payload[0] == '2' && (char)payload[1] == 'D'){
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED off
    Serial.println("LED2 DESLIGADO");
  }else{
    Serial.println("Qualquer outra mensagem recebida");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outYago", "hello world");
      // ... and resubscribe
      client.subscribe("inYago");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the LED pin as an output
  pinMode(BUILTIN_LED_2, OUTPUT);   // Initialize the LED2 pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "Hello World #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outYago", msg);
  }
}
