// Motor control
int RPWM_Output = 27; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM) 
int LPWM_Output = 14; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM) 

// Ultrasonic sensor
const int sona_ping = 5;
const int sona_echo = 18;

// Define the speed of sound in cm/ms
const float SOUND_SPEED = 0.034;

// Value to  store
float distanceMeasure;


// MQTT DEFINE =========

// WiFi credentials
#define WIFI_STA_NAME "Find Me Free Wifi"
#define WIFI_STA_PASS "11333355555577777777"
#define MQTT_SERVER   "broker.mqttdashboard.com"
#define MQTT_PORT     1883
#define MQTT_NAME     "StartUpKMITLdevice"

// Time config for Thai Time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7;
const int   daylightOffset_sec = 7 * 3600;

WiFiClient client;

// check WiFiClient where is client
PubSubClient mqtt(client);

//  timeinfo to store value
struct tm timeinfo;

// time count
//unsigned long startTime;
//unsigned long elapsedTime;
int unlock_status;
