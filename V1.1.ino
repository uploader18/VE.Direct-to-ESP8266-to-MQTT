#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//#include <SoftwareSerial.h>
#include <SPI.h>
 
const char* ssid = "";
const char* password =  "";
const char* mqttServer = "";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

//SoftwareSerial Victron(D7,D8); // RX, TX //Jue changed this
WiFiClient espClient;
PubSubClient client(espClient);

char p_buffer[80];
#define P(str) (strcpy_P(p_buffer, PSTR(str)), p_buffer)
 
char c;
String V_buffer;  // Buffer to hold data from the Victron monitor

char Current[8];
char Voltage[8];
char SOC[8];
char CE[8];

String stringOne;

void reconnect() {
  //Serial.print("Reconnecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");  // As long as it is trying to connect print a . each 500ms to debugger
  }
  //Serial.println("WiFi re-connected");
  
}

void readVictronData() {
  c = 0;
  if (Serial.available()) {
    c = Serial.read();
      V_buffer += c;
 
    if (c == '\n') {  // New line.
 
      if (V_buffer.startsWith("I")) {
        String temp_string = V_buffer.substring(V_buffer.indexOf("\t")+1);
        temp_string.toCharArray(Current, temp_string.length() + 1);
       client.publish("BMV/Current", Current); 
      // Serial.print("Current: ");
      // Serial.println(temp_string);
      }     
 
      if (V_buffer.startsWith("V")) {
        String temp_string = V_buffer.substring(V_buffer.indexOf("\t")+1);
        temp_string.toCharArray(Voltage, temp_string.length() + 1);
        client.publish("BMV/Voltage", Voltage); 
       
      }     
 
      if (V_buffer.startsWith("SOC")) {
        String temp_string = V_buffer.substring(V_buffer.indexOf("\t")+1);
        temp_string.toCharArray(SOC, temp_string.length() + 1);
        client.publish("BMV/SOC", SOC); 
       
 
      }
      if (V_buffer.startsWith("CE")) {
        String temp_string = V_buffer.substring(V_buffer.indexOf("\t")+1);
        temp_string.toCharArray(CE, temp_string.length() + 1);
        client.publish("BMV/CE", CE); 
   
      }
  
     //Serial.println(V_buffer);
     V_buffer=""; // Empty V_Buffer
    } 
  }
}

void connect_mqtt() {
  
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      //Serial.println("connected");  
 
    } else {
 
     // Serial.print("failed with state ");
     // Serial.print(client.state());
      delay(2000);
      }
    client.publish("BMV/Welcome", "Welcome from Victron");
  }
}


void setup() {
 
  Serial.begin(19200);
  //Victron.begin(19200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");
  connect_mqtt();
}

 
void loop() {
  if (WiFi.status() != WL_CONNECTED) { // If wifi is not connected run reconnect() function
    reconnect();
  }
  connect_mqtt();
  readVictronData();  // Read Victron Data
  
 
}
