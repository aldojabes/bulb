#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define LED D7
#define LightSensor A0
WiFiClient wifiClient;
const int threshold = 200;
void setup() {
pinMode(LED, OUTPUT);
connectWifi();    // LED pin as output.
}
void loop() {
  Serial.println(analogRead(LightSensor));
  processResponse(); 
  lowlight();
  delay(200);
}
void processResponse(){
  HTTPClient http;   
  // String Link = "http://iot.benax.rw/projects/38db9f4aba26c82191c27b38d92aac2c/bulb/device.php";
  String Link = "http://192.168.0.172/bulb/device.php";
  
  http.begin(wifiClient,Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload

  // Serial.println(httpCode);
  Serial.println("> "+payload);
  
  if(payload == "on"){
    digitalWrite(LED,LOW);
  }else{
    digitalWrite(LED,HIGH);
  }    //Print request response payload

  http.end();  //Close connection
}

void connectWifi(){
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin("Benax-WiFi(2.4G)","Rc@Nyabihu2023");     //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //If connection successful show IP address in serial monitor 
  Serial.print("Connected to ");
  Serial.println("RCA-WIFI");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void lowlight(){
  Serial.println("burigo");
   if (analogRead(LightSensor) > threshold) {
     HTTPClient http;
     http.begin(wifiClient,"http://192.168.0.172/bulb/getstatus.php");
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     String RequestData = "status=off"; 
     int ResponseCode = http.POST(RequestData);
      Serial.print("HTTP Response code for off: ");
      Serial.println(ResponseCode);
     http.end();
  }else {
    HTTPClient http;
     http.begin(wifiClient,"http://192.168.0.172/bulb/getstatus.php");
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     String RequestData = "status=on"; 
     int ResponseCode = http.POST(RequestData);
      Serial.print("HTTP Response code for on: ");
      Serial.println(ResponseCode);
     http.end();
  }
}