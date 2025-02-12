#include <Preferences.h>

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL******"
#define BLYNK_TEMPLATE_NAME "MEHEBUB  ENTERPRISE"
#define BLYNK_AUTH_TOKEN "4fYk**************"

char auth[] = BLYNK_AUTH_TOKEN;
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BluetoothSerial.h>
#include <AceButton.h>

BluetoothSerial SerialBT;
using namespace ace_button;
Preferences pref;


char ssid[] = "Mehebub_Enterprise";
char pass[] = "*************";

bool wifiConnected = false;
ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);
ButtonConfig config5;
AceButton button5(&config5);
ButtonConfig config6;
AceButton button6(&config6);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);
void handleEvent5(AceButton*, uint8_t, uint8_t);
void handleEvent6(AceButton*, uint8_t, uint8_t);

// Pin Definitions
#define doorSensorPin 36
#define indoorSensorPin 4
#define sirenPin 23
#define emergencyLight 22
#define indoorLight1 18
#define indoorLight2 19
#define outdoorLight1 21
#define bannerLight 5
#define light2Pin 15
#define secureOnLight 17
#define wifiLED 2
#define buttonPin_1 13
#define buttonPin_2 12
#define buttonPin_3 14
#define buttonPin_4 27
#define buttonPin_5 26
#define buttonPin_6 25
#define buttonPin_7 33

//Define Blynk Virtual PIN

#define VPIN_Indoor1 V0
#define VPIN_Indoor2 V1
#define VPIN_Outdoor V2
#define VPIN_Emergency V3
#define VPIN_Banner V4
#define VPIN_OutdoorSensor V5
#define VPIN_DoorSensor V6
#define VPIN_IndoorSensor V7
#define VPIN_IndoorMotion V9
#define VPIN_SecureMode V10
#define VPIN_ModeName V11
#define VPIN_Light2 V12
BlynkTimer timer;
//BlynkTimer timer2;
char btCommand;


// State Variables
// Timing Constants
const unsigned long pirSirenDuration = 10000;
const unsigned long rcwlSirenDuration = 5000;   // Siren stays on for 5 seconds
const unsigned long rcwlTimeout = 240000;
unsigned long lastReconnectAttempt = 0;
const unsigned long CONNECTION_TIMEOUT = 10000;
const unsigned long WIFI_RECONNECT_INTERVAL = 10000; // 10 seconds

unsigned long currentMillis =0;
unsigned long millis1 = 0;
unsigned long pirFirstDetected = 0;
unsigned long pirLastDetected = 0;
unsigned long rcwlSirenTime = 0;
unsigned long lastBlynkCheckTime = 0;
const unsigned long BLYNK_CHECK_INTERVAL = 60000;
bool secureIndicator = false;
bool secureModeOn = false;
bool pirActive = false;
bool rcwlActive = false;
bool rcwlSirenOn= false;
bool pirSirenOn = false;
bool doorMotionOn=false;
static bool sirenAlreadyOn = false;          // Track siren state

bool toggleState_1 = LOW;
bool toggleState_2 = LOW;
bool toggleState_3 = LOW;
bool toggleState_4 = LOW;
bool toggleState_5 = LOW;
bool toggleState_6 = LOW;

void handleBT(char btCommand){
    switch (btCommand) {
      case 'A':
      digitalWrite(indoorLight2, HIGH);
      //Blynk.virtualWrite(VPIN_Indoor2, HIGH);
      toggleState_1 = HIGH;
      Serial.println("Indoor on");
      delay(50);

        break;
      case 'B':
      digitalWrite(indoorLight2, LOW);
      //Blynk.virtualWrite(VPIN_Indoor2, LOW);
      toggleState_1 = LOW;
      Serial.println("Indoor off");
        break;

      case 'C':
      digitalWrite(light2Pin, HIGH);
      Blynk.virtualWrite(VPIN_Light2, HIGH);
      toggleState_2 = HIGH;
      Serial.println("Light2 ON");
        break;

        case 'D':
      digitalWrite(light2Pin, LOW);
      Blynk.virtualWrite(VPIN_Light2, LOW);
      toggleState_2 = LOW;
      Serial.println("Light2 OFF");
        break;

        case 'E':
      digitalWrite(indoorLight1, HIGH);
      Blynk.virtualWrite(VPIN_Indoor1, HIGH);
      toggleState_3 = HIGH;
      delay(50);
      Serial.println("IndoorLight 1 ON");
        break;

        case 'F':
      digitalWrite(indoorLight1, LOW);
      Blynk.virtualWrite(VPIN_Indoor1, LOW);
      toggleState_3 = LOW;
      delay(50);
      Serial.println("IndoorLight 1 OFF");
        break;

        case 'G':
        digitalWrite(outdoorLight1, HIGH);
        Blynk.virtualWrite(VPIN_Outdoor, HIGH);
        Serial.println("Outdoor on");
        toggleState_4 = HIGH;
        delay(50);
        Serial.println("Outdoor light on");
        break;

        case 'H':
        digitalWrite(outdoorLight1, LOW);
        Blynk.virtualWrite(VPIN_Outdoor, LOW);
        Serial.println("Outdoor off");
        toggleState_4 = LOW;
        delay(50);
        Serial.println("Outdoor light off");
        break;

        case 'I':
        digitalWrite(emergencyLight, HIGH);
        Blynk.virtualWrite(VPIN_Emergency, HIGH);
        Serial.println("Fifteen");
        toggleState_5 = HIGH;
        delay(50);
        Serial.println("Emergency Light on");
        break;

        case 'J':
        digitalWrite(emergencyLight, LOW);
        Blynk.virtualWrite(VPIN_Emergency, LOW);
        toggleState_5 = LOW;
        delay(50);
        break;

        case 'K':
        digitalWrite(bannerLight, HIGH);
        //Blynk.virtualWrite(VPIN_Banner, HIGH);
        toggleState_6 = HIGH;
        delay(50);
        break;

        case 'L':
        digitalWrite(bannerLight, LOW);
        //Blynk.virtualWrite(VPIN_Banner, LOW);
        toggleState_6 = LOW;
        break;

        case 'X':
        secureModeOn = true;
        Serial.println("Secure Mode On");
        break;

        case 'Y':
        Serial.println("Secure_OFF");
        secureModeOn = false;
        break;
        default:
        break;
}
  }
    


void setup() {
  
  Serial.begin(115200);
  unsigned long startAttemptTime = millis();

  connectToWiFi();

  Blynk.config(BLYNK_AUTH_TOKEN);


    config1.setEventHandler(handleEvent1);
    config2.setEventHandler(handleEvent2);
    config3.setEventHandler(handleEvent3);
    config4.setEventHandler(handleEvent4);
    config5.setEventHandler(handleEvent5);
    config6.setEventHandler(handleEvent6);
       
    button1.init(buttonPin_1);
    button2.init(buttonPin_2);
    button3.init(buttonPin_3);
    button4.init(buttonPin_4);
    button5.init(buttonPin_5);
    button6.init(buttonPin_6);
  SerialBT.begin("abcd");
  Serial.println("Printing Ready");
  pinMode(doorSensorPin, INPUT);
  pinMode(indoorSensorPin, INPUT);
  pinMode(indoorLight1, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(indoorLight2, OUTPUT);
  pinMode(outdoorLight1, OUTPUT);
  pinMode(emergencyLight, OUTPUT);
  pinMode(bannerLight, OUTPUT);
  pinMode(sirenPin, OUTPUT);
  pinMode(secureOnLight, OUTPUT);

  pinMode(buttonPin_1, INPUT);
  pinMode(buttonPin_2, INPUT);
  pinMode(buttonPin_3, INPUT);
  pinMode(buttonPin_4, INPUT);
  pinMode(buttonPin_5, INPUT);
  pinMode(buttonPin_6, INPUT);
  pinMode(wifiLED, OUTPUT);

  digitalWrite(secureOnLight, LOW);
  digitalWrite(indoorLight1, LOW);
  digitalWrite(light2Pin, LOW);
  digitalWrite(sirenPin, LOW);
  digitalWrite(wifiLED, LOW);

  digitalWrite(outdoorLight1, LOW);
  delay(250);
  digitalWrite(indoorLight2, LOW);
  delay(100);
  Serial.println("One");
  timer.setInterval(100L, checkSensor);
}


void checkSensor(){
  
  if (SerialBT.available()) {
  btCommand = SerialBT.read();
  handleBT(btCommand);
  Serial.println(btCommand);
  }
  pirActive = digitalRead(doorSensorPin);
  rcwlActive = digitalRead(indoorSensorPin);
  if(secureModeOn){
  handleSensors();
  digitalWrite(secureOnLight, HIGH);
  if(!secureIndicator){
    Blynk.virtualWrite(VPIN_SecureMode, HIGH);
    Blynk.virtualWrite(VPIN_ModeName, "Security ON");
    digitalWrite(outdoorLight1, HIGH);
    delay(500);
    digitalWrite(outdoorLight1, LOW);
    delay(500);
    digitalWrite(outdoorLight1, toggleState_4);
    secureIndicator = true;
  }
  }

  else {
    if(secureIndicator){
    Blynk.virtualWrite(VPIN_SecureMode, LOW);
    Blynk.virtualWrite(VPIN_ModeName, "Security OFF");
    digitalWrite(outdoorLight1, HIGH);
    delay(500);
    digitalWrite(outdoorLight1, LOW);
    delay(500);
    digitalWrite(outdoorLight1, toggleState_4);
    secureIndicator = false;
    pirSirenOn = false;
    rcwlSirenOn = false;
    sirenAlreadyOn = false;
  }
    digitalWrite(secureOnLight, LOW);
    digitalWrite(sirenPin, LOW);
     
    }

}

BLYNK_WRITE(VPIN_Indoor1) {
  toggleState_3 = param.asInt();
  digitalWrite(indoorLight1, toggleState_3);
  Serial.print("Indoor light");
  Serial.println(toggleState_3);
}

// Blynk write handlers for relays
BLYNK_WRITE(VPIN_Indoor2) {
  toggleState_1 = param.asInt();
  digitalWrite(indoorLight2, toggleState_1);
}

BLYNK_WRITE(VPIN_Outdoor) {
  toggleState_4 = param.asInt();
  digitalWrite(outdoorLight1, toggleState_4);
  Serial.println("Outdoor Light status change");
}

BLYNK_WRITE(VPIN_Banner) {
  toggleState_6 = param.asInt();
  digitalWrite(bannerLight, toggleState_6);
}

BLYNK_WRITE(VPIN_Light2) {
  toggleState_2 = param.asInt();
  digitalWrite(light2Pin, toggleState_2);
}
BLYNK_WRITE(VPIN_Emergency) {
  toggleState_5 = param.asInt();
  digitalWrite(emergencyLight, toggleState_5);
}

BLYNK_WRITE(VPIN_SecureMode) {
  secureModeOn = param.asInt();
}

void loop() {


  // Only run Blynk tasks if connected
  if (Blynk.connected()) {
    digitalWrite(wifiLED, HIGH);
    Blynk.run();
  }
  timer.run();

  if (!wifiConnected && (millis() - lastReconnectAttempt >= WIFI_RECONNECT_INTERVAL)) {
    digitalWrite(wifiLED, LOW);
    lastReconnectAttempt = millis();
    connectToWiFi();
  }

 if (millis() - lastBlynkCheckTime >= BLYNK_CHECK_INTERVAL) {
  if (WiFi.status() == WL_CONNECTED){
    lastBlynkCheckTime = millis();
    if (!Blynk.connected()) {
      Serial.println("Attempting to reconnect to Blynk...");

      connectToWiFi();
      //Blynk.connect(); // Non-blocking connection attempt
      lastBlynkCheckTime = millis();
    }
    else
  digitalWrite(wifiLED, HIGH);
  }
  else
  digitalWrite(wifiLED, LOW);
 }

  

  button1.check();
  button2.check();
  button3.check();
  button4.check();
  button5.check();
  button6.check();
  }

  void handleSensors() {
  unsigned long currentMillis = millis();

  if (pirActive) {
    pirLastDetected = currentMillis;

    if (!pirSirenOn) {
      // PIR is detected for the first time
      doorMotionOn=true;
      Serial.println("PIR detected");
      pirFirstDetected = currentMillis;
      millis1 = currentMillis;
      digitalWrite(sirenPin, HIGH);
      Blynk.virtualWrite(VPIN_DoorSensor, HIGH);
       Blynk.logEvent("door_sensor");
      Serial.println("Two");
      pirSirenOn = true;
    }
  }

  if (!pirActive){
    if (pirSirenOn && (currentMillis - pirLastDetected) > pirSirenDuration) {
      Blynk.virtualWrite(VPIN_DoorSensor, LOW);
      Serial.println("Three");
      Serial.println("Siren turned off due to PIR inactivity");
      pirSirenOn = false;
    }
  
}
 if (rcwlActive && !pirActive && (currentMillis - pirLastDetected) > rcwlTimeout) {
    if (!rcwlSirenOn){
    Serial.println("RCWL detected without PIR");
    digitalWrite(sirenPin, HIGH);
    Blynk.virtualWrite(VPIN_IndoorSensor, HIGH);
    Blynk.logEvent("indoor_sensor");
    Serial.println("Four");
    rcwlSirenOn = true;
    rcwlSirenTime = millis();
    }
  }
  if (rcwlSirenOn && !rcwlActive){
  if(millis() - rcwlSirenTime >= rcwlSirenDuration){
    Serial.println("RCWL only siren off");
    Serial.println("Five");
    Blynk.virtualWrite(VPIN_IndoorSensor, LOW);
    rcwlSirenOn = false;
  }
  }

  static unsigned long rcwlActiveStartTime = 0; // Track when RCWL became active
  

  if (rcwlActive && pirActive || rcwlActive && (currentMillis - pirLastDetected) <= rcwlTimeout) {   // add pir lastactive time
  rcwlActiveStartTime = currentMillis;    // Record when RCWL became active
    if (!sirenAlreadyOn) {
      Serial.println("RCWL detected with PIR active or recently active");
      digitalWrite(sirenPin, HIGH);           // Turn on siren
      Blynk.virtualWrite(VPIN_IndoorMotion, HIGH);
      Blynk.logEvent("indoor_motion");
      Serial.println("One");
       sirenAlreadyOn = true;                  // Record siren state
      }
  }

  if (sirenAlreadyOn && !rcwlActive) {
    if (currentMillis - rcwlActiveStartTime >= 20000) {
      Blynk.virtualWrite(VPIN_IndoorMotion, LOW);
      Serial.println("Seven");

      sirenAlreadyOn = false;      // Reset siren state
      Serial.println("Siren turned off after RCWL became inactive");
    }
  }
  if(!pirSirenOn &&!rcwlSirenOn && !sirenAlreadyOn){
    if(digitalRead(sirenPin) == HIGH){
    digitalWrite(sirenPin, LOW);
    Serial.println(" Siren Turn Off due to No Motion Available");
    }
  }

}


void handleEvent1(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventPressed:
    toggleState_5 = !toggleState_5;
    digitalWrite(emergencyLight, toggleState_5);
    Blynk.virtualWrite(VPIN_Emergency, toggleState_5);
    Serial.println("Eight");
        delay(50);
        break;
  }
}

void handleEvent2(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventPressed:
    digitalWrite(indoorLight2, !toggleState_1);
    toggleState_1 = !toggleState_1;
   // Blynk.virtualWrite(VPIN_Indoor2, toggleState_1);
    Serial.println("Nine");
        delay(50);
    break;
  }
}

void handleEvent3(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventPressed:
    digitalWrite(light2Pin, !toggleState_2);
    toggleState_2 = !toggleState_2;
    Blynk.virtualWrite(VPIN_Light2, toggleState_2);
    Serial.println("Ten");
        delay(50);
    break;
  }
}

void handleEvent4(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventPressed:
    digitalWrite(indoorLight1, !toggleState_3);
    toggleState_3 = !toggleState_3;
    Blynk.virtualWrite(VPIN_Indoor1, toggleState_3);
    Serial.println("Eleven");
        delay(50);
    break;
  }
}

void handleEvent5(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT5");
  switch (eventType) {
    case AceButton::kEventPressed:
    digitalWrite(outdoorLight1, !toggleState_4);
    toggleState_4 = !toggleState_4;
    Blynk.virtualWrite(VPIN_Outdoor, toggleState_4);
    Serial.println("Twelve");
        delay(50);
    break;
  }
}

void handleEvent6(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT6");
  switch (eventType) {
    case AceButton::kEventPressed:
    digitalWrite(bannerLight, !toggleState_6);
    toggleState_6= !toggleState_6;
   // Blynk.virtualWrite(VPIN_Banner, toggleState_6);
    Serial.println("Thirteen");
        delay(50);
    break;
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to Wi-Fi");
  for (int i = 0; i < 8; i++) { // Try for 10 seconds
    if (WiFi.status() == WL_CONNECTED) {
      wifiConnected = true;
      Serial.println("\nWi-Fi Connected!");
      Blynk.connect();
      return;
    }
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWi-Fi Connection Failed!");
  wifiConnected = false;
  digitalWrite(wifiLED, LOW);

}

