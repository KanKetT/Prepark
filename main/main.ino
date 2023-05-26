#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#include "time.h"
#include "define.h"
#include "preparkFunction.h"

void printLocalTime();

// ============================================================================================ VOID SETUP
void setup() {
  Serial.begin(9600);
  //===================================================== Motor and Ultra Control setup
  // Set up the pins for the ultrasonic sensor
  pinMode(sona_ping, OUTPUT);
  pinMode(sona_echo, INPUT);
  ledcSetup(0, 9000, 8);
  // Set up the pins for the motor
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  ledcSetup(1, 9000, 8);
  ledcAttachPin(RPWM_Output, 1);
  ledcSetup(2, 9000, 8);
  ledcAttachPin(LPWM_Output, 2);

  //  startTime = millis(); // Record the current time
  //===================================================== connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(WIFI_STA_NAME);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(callback);
}

// ============================================================================================ MQTT SETUP
void callback(char* topic, byte* payload, unsigned int length) {
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
  }

  char  date_time_All[40];

  strftime(date_time_All,40,"%d%B%Y %H:%M:%S", &timeinfo);
  
  Serial.println(date_time_All);

  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  Serial.println("[" + topic_str + "]: " + payload_str);

  

  Serial.println((payload_str == "ON") ? "HIGH" : "LOW");

  // code start
  if (payload_str == "ON") {
    strftime(date_time_All,40,"%d%B%Y %H:%M:%S ON", &timeinfo);
    mqtt.publish("device_status/all", date_time_All);
    CCW_motor(256);
    delay(2800);
    stop_motor();
  }

  if (payload_str == "OFF") {
     strftime(date_time_All,40,"%d%B%Y %H:%M:%S OFF", &timeinfo);
     mqtt.publish("device_status/all", date_time_All);
     CW_motor(256);
     delay(2800);
     stop_motor();
  }

  if (payload_str == "unlock") {
      strftime(date_time_All,40,"%d%B%Y %H:%M:%S unlock", &timeinfo);
      mqtt.publish("device_status/all", date_time_All);
      unlock_status = 0;
      CW_motor(256);
      delay(2800);
      stop_motor();
      
      while(distanceMeasure>70){
        distanceMeasure = start_sona();
        Serial.println("waiting car pass");
      }
      while(distanceMeasure<70){
          unlock_status = 1;
          delay(200);
          distanceMeasure = start_sona();
          Serial.println("Car is passing");
      }
      
      if(distanceMeasure>70 and unlock_status==1){
        Serial.println("ON");
        delay(15000);
        CCW_motor(256);
        delay(2800);
        stop_motor();
        unlock_status = 0;
    }

  }
}

void pub() {
  char demoString[15] = "IT'S WORKING";
  Serial.print("DemoString: ");
  Serial.println(demoString);
  mqtt.publish("device_status", demoString);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

// ============================================================================================ START THE LOOP
void loop() {
  distanceMeasure = start_sona();
  //  elapsedTime = (millis() - startTime)/1000;
  //  Serial.print("elapsedTime: ", elapsedTime);
  // cannot connect statement
  if (mqtt.connected() == false) {
    Serial.print("MQTT connection... ");
    if (mqtt.connect(MQTT_NAME)) {
      Serial.println("connected");
      mqtt.subscribe("device_status/command");
    } else {
      Serial.println("failed");
      delay(5000);
    }
  } else {
    mqtt.loop();
  }
}
