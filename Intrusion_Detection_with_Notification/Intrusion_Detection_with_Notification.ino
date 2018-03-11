
/***************************************************
  Code is edited by Sachin Soni for it's project called
  Ultimate Home Automation

  For Project video, visit his YouTube channel named "techiesms"

  #techiesms
  explore | learn | share
 ****************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


/************************* Pin Definition *********************************/

#define S0                D3
#define S1                D4
#define analogpin         A0

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "PASS"

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(A0, INPUT);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
void loop() {
 
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  Serial.print("Motion "); Serial.println(analogRead(analogpin));
  Serial.print("...");
  
  int Value = analogRead(analogpin);
  if(Value > 500)
  {
    HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
          http.begin("http://maker.ifttt.com/trigger/EVENT_NAME/with/key/KEY"); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
  }
}  
