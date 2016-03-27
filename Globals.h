#define DEBUG
#define DEBUG_frame
#define USE_OTA
//#define FREERUN

#define pred_size 10
#define PIXELS 12


const char* host = "Sattrack";
const char* ap_password = "123456789";


AsyncWebServer server(80);
WebSocketsServer webSocket(81);
Sgp4 sat;
WiFiUDP UDPNTPClient;
WiFiClient client;
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PIXELS, 2);

unsigned long unixtime;
double jdtime; 
double updatejdtime;
unsigned long timemillis;
unsigned long socketrate = 0;

typedef char str3[4];
str3 monstr[13];

passinfo passPredictions[pred_size];

AsyncWebServerRequest *PredictRequest = NULL;

#ifdef DEBUG
  
  Ticker ticker;
  int framerate;

  void Second_Tick()
  {
    Serial.printf("Looprate:%d FreeMem:%d \n",framerate,ESP.getFreeHeap());
    framerate=0;  
  }
#endif

enum state_mode {
    RECALC,
    RESTART,
    IDLE
}state;

/////Flags//////

bool predError = false;
bool dataError = false;
