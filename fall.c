#include <Wire.h>
#include <BMA222.h>
#include <WiFi.h>

BMA222 mySensor;

char ssid[] = "Revati's phone";
char pass[] = "123456789@re";

char host[] = "api.thingspeak.com";
String apiKey = "756M15C9AMRFYAS3";

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  mySensor.begin();
  uint8_t chipID = mySensor.chipID();
  Serial.print("chipID: ");
  Serial.println(chipID);
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop()
{
  int8_t data = mySensor.readXData();
  Serial.print("X: ");
  Serial.print(data);
  int X = data;

  data = mySensor.readYData();
  Serial.print(" Y: ");
  Serial.print(data);
  int Y = data;

  data = mySensor.readZData();
  Serial.print(" Z: ");
  Serial.println(data);
  int Z = data;

  if (client.connect(host, 80)) {
    Serial.println("connecting...");
    client.print("GET /update?api_key=756M15C9AMRFYAS3=");
    int a= analogRead(X);
    client.print(a);
//    client.println("Host: www.energia.nu");
//    client.println("User-Agent: Energia/1.1");
    int b= analogRead(Y);
     client.print("+&field2=");
    client.println(b);
    client.println("Connection: close");
    client.println();

    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Could not connect to ThingSpeak");
  }

  client.stop();
  delay(10000);
}
