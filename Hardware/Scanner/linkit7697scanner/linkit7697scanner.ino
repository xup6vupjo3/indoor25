//-----IoT 5 Layer Reference
//---------------------------https://www.researchgate.net/figure/Five-Layer-IoT-Architecture_fig1_324797771

//[Setup] (Layer 1 - Perception Layer)-----------------------Buttons Main Variables--------------------------------------------------

#define PIN_MINUS 17
#define PIN_PLUS 16
#define PIN_SCAN 15

//Control: select each switch case in float mappingvar (int numvar)
int buttonPushCounter = 0;   // counter for the number of button presses

//Internal: Button Plus State WD
int buttonState = 0;         
int lastButtonState = 0;     

//Internal: Button Minus State WD
int buttonStateMinus = 0;         
int lastButtonStateMinus = 0;     

//Internal: Button Scan State WD
int buttonStateScan = 0;         
int lastButtonStateScan = 0;

//MQTT: variable added to payload
float distlcd;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the I2C address of the LCD controller
//    0x3F for PCF8574A
//    0x27 for PCF8574T (scanner two)
LiquidCrystal_I2C lcd(0x3F);

//LiquidCrystal_I2C lcd(0x3F);
float mappingvar(int numvar){
  switch (numvar){
    case 0:
      distlcd=0;
//      Serial.print ("Press any button");
    break;
    
    case 1:
      distlcd=0.2;
    break;

    case 2:
      distlcd=0.4;
    break;

    case 3:
      distlcd=0.6;
    break;
    
    case 4:
      distlcd=0.8;
    break;

    case 5:
      distlcd=1;
    break;

    case 6:
      distlcd=2;
    break;

    case 7:
      distlcd=3;
    break;

    case 8:
      distlcd=4;
    break;

    case 9:
      distlcd=5;
    break;

    case 10:
      distlcd=6;
    break;   

    case 11:
      distlcd=7;
    break; 

    case 12:
      distlcd=8;
    break;   

    case 13:
      distlcd=9;
    break; 

    case 14:
      distlcd=10;
    break;    

    case 15:
      distlcd=12;
    break;                                                                 
  }
//  Serial.print("Beacon distance (m): ");
//  Serial.println (distlcd);
  lcd.clear();
  lcd.print("Beacon Distance");
  lcd.setCursor(0,1);
  lcd.print(distlcd);
  lcd.print(" ");
  lcd.print("m");
}
//[Setup] (Layer 1 - Perception Layer)-----------------------Buttons Main Variables--------------------------------------------------

//[Setup] (Layer 1 - Perception Layer)-----------------------LCD Main Variables------------------------------------------------------
byte zero[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte one[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

byte two[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};

byte three[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};

byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
void setuplcd(){
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
}

//[Setup] (Layer 1 - Perception Layer)-----------------------LCD Main Variables------------------------------------------------------

//[Setup] (Layer 2 - Network Layer)-----------------------Bluetooth-MQTT-WIFI (main variables)---------------------------------------
#include <LBLE.h>
#include <LBLECentral.h>
#include <LWiFi.h>
#include <PubSubClient.h>

#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"
//#define WIFI_SSID "ExtraSSID"
//#define WIFI_PASSWORD "ExtraPassword"

int status = WL_IDLE_STATUS;
WiFiClient client;

//Scanner one
#define QIOT_SERVER_IP "8.8.8.8"
#define QIOT_SERVER_PORT 21883
#define QIOT_USERNAME "MQTTusername"
#define QIOT_PASSWORD "MQTTpassword"
#define QIOT_CLIENT_ID "MQTTclientid"
#define QIOT_TOPIC "mqtt/topic/rssi"


//looplimit = how many times we will scan
int looplimit=300;
int cyclecount=0;

int rssiglobal;
String macaddr;
String beaconname;

int mqttfails=0;
int mqttalarm=5;
PubSubClient mqttclient(client);

//modify for different type (EXT-CCA)
String antennatype = {"CCA"};
//[Setup] (Layer 2 - Network Layer)-----------------------Bluetooth-MQTT-WIFI (main variables)-------------------------------------------------

//[Function] (Layer 1 - Perception Layer)---------------------------------Hardware(LCD+Buttons)------------------------------------------------
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn)
{
  count=cyclecount;
  totalCount=looplimit;
  double factor = totalCount/80.0;          //See note above!
  int percent = (count+1)/factor;
  int number = percent/5;
  int remainder = percent%5;
  if(number > 0)
  {
     lcd.setCursor(number-1,lineToPrintOn);
     lcd.write(5);
  }
 
     lcd.setCursor(number,lineToPrintOn);
     lcd.write(remainder);   
}
int buttonplus (int buttonState){
    // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
        if (buttonPushCounter > 15){
          buttonPushCounter=0;    
        }
      
      Serial.println(buttonPushCounter); 
      mappingvar (buttonPushCounter);

    } 
    
    else {
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  lastButtonState = buttonState;
  
}
int buttonminus (int buttonStateMinus){
  
    if (buttonStateMinus != lastButtonStateMinus) {
      if (buttonStateMinus == HIGH) {
        buttonPushCounter--;
        Serial.println("on");
        Serial.print("number of button pushes: ");
          if (buttonPushCounter<0){
            buttonPushCounter = 15;
           }
        Serial.println(buttonPushCounter);
        mappingvar (buttonPushCounter);
      } 
      
      else {
        Serial.println("off");
      }
    delay(50);
  }

  lastButtonStateMinus = buttonStateMinus;
  
}
//[Function] (Layer 1 - Perception Layer)---------------------------------Hardware(LCD+Buttons)------------------------------------------------

//[Function] (Layer 1.5 - Transition Layer)-------------------------------Trigger to Network---------------------------------------------------
int buttonscan (int buttonStateScan){
  
    if (buttonStateScan != lastButtonStateScan) {
      if (buttonStateScan == HIGH) {
        lcd.clear();
        //Hardware  : Scan the beacons 100 times
        //Main condition: Block until loop finishes
        for (int j = 0; j< looplimit; j++){
            
          if (!mqttclient.connected())
            {
              mqttreconnect();
            }
          
          else
            {
            scannerfx();
            cyclecount++;
            lcd.setCursor(0,0);
            lcd.print(j);
            lcd.print("   ");
            updateProgressBar(j, looplimit, 1); 
//            Serial.println (cyclecount);
            }
          }
      } 
      
      else {
        lcd.clear();
        lcd.print("scan finished");
        lcd.setCursor(0,1);
        lcd.print("Press any button");              
//        Serial.println("scan finished");
      }
    delay(50);
  }

  else{
        //Hardware  : Read Plus-Minus buttons
        //UX-UI(LCD): Display selected beacon distance
        //Main condition: Wait until press SCAN    
        buttonplus (buttonState);
        buttonminus (buttonStateMinus);
  }
  lastButtonStateScan = buttonStateScan;
}
//[Function] (Layer 1.5 - Transition Layer)-------------------------------Trigger to Network---------------------------------------------------

//[Function] (Layer 2 - Network Layer)------------------------------------Data Transmission----------------------------------------------------
void wificonnect(){
  // first wifi connection network:
  while (status != WL_CONNECTED)
    {
//      Serial.print("Attempting to connect to SSID: ");
//      Serial.println(WIFI_SSID);
      status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

  //LCD display
//  Serial.println("Connected to wifi");
  lcd.clear();
  lcd.print("Wifi ON");
  printWifiStatus();
  randomSeed(analogRead(0));
}
void printWifiStatus(){
  // print the SSID of the network you're attached to:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());
  
  lcd.clear();
  lcd.print(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);
  lcd.setCursor(0,1);
  lcd.print("IP");
  lcd.print(" ");
  lcd.print(ip);  
}
void mqttreconnect(){
  // Loop until we're reconnected
  while (!mqttclient.connected())
  {
    //LCD display
    lcd.clear();
    lcd.print("MQTT N/A");
//    Serial.print("MQTT connection request");
    
    //Attempt to connect
    if (mqttclient.connect(QIOT_CLIENT_ID, QIOT_USERNAME, QIOT_PASSWORD)) //QIoT connection   
//    if (mqttclient.connect(QIOT_CLIENT_ID)) //NodeRED connection
      {
        //LCD display
        lcd.clear();
        lcd.print("MQTT UP");
//        Serial.println("MQTT Connected");
      }
    else
      {
        //LCD display
        lcd.clear();
        lcd.print("MQTT N/A");
//        Serial.println("MQTT not available");
//        Serial.print(mqttclient.state());
        lcd.setCursor(0,1);
        lcd.print("wait 5000ms");        
//        Serial.println(" try again in 5000ms");
        mqttfails++;
        //Wait 5 seconds to reconnect to mqtt broker
        delay(5000);
      }

      if (mqttfails==mqttalarm){
        for (int i=0; i<5; i++){
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);                       // wait for a second
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(1000);                       // wait for a second
        }
        //reset watchdog
        mqttfails=0;
      }
  }
}
void scannerfx (){
  Serial.println("BLE ready, start scan (wait 10 ms)");
  LBLECentral.scan();
  for(int i = 0; i < 2; ++i)
    {
      delay(10);
      Serial.print(".");
    }

  // list advertisements found.
  Serial.print("Total scannerfx ");
  Serial.print(LBLECentral.getPeripheralCount());
  Serial.println(" devices found:");
  Serial.println("idx\taddress\t\t\tflag\tRSSI");
  
  for (int i = 0; i < LBLECentral.getPeripheralCount(); ++i)
    {
      printDeviceInfo(i);
    }
  
  LBLECentral.stopScan();
  Serial.println("------scan stopped-------");
}
//Payload Transmission to QioT
void printDeviceInfo(int i) {
  Serial.print(i);
  Serial.print("\t");
  
  Serial.print(LBLECentral.getAddress(i));
  macaddr = LBLECentral.getAddress(i);
//  
  Serial.print("\t");
  Serial.print(LBLECentral.getAdvertisementFlag(i), HEX);
  Serial.print("\t");

  Serial.print(LBLECentral.getRSSI(i));
  rssiglobal = LBLECentral.getRSSI(i);
  Serial.print("\t");

  const String name = LBLECentral.getName(i);
  beaconname = name;
  Serial.print(name);
  
  if(name.length() == 0)
    
    {
      Serial.print("(Unknown)");
    }
//  
  Serial.print(" by ");
  const String model = LBLECentral.getManufacturer(i);
  Serial.print(model);
//  
  Serial.print(", service: ");
  if (!LBLECentral.getServiceUuid(i).isEmpty())
    {
      Serial.print(LBLECentral.getServiceUuid(i));
    } 
  else
    {
      Serial.print("(no service info)");
    } 

  if (LBLECentral.isIBeacon(i)) {
    LBLEUuid uuid;
    uint16_t major = 0, minor = 0;
    int8_t txPower = 0;
    LBLECentral.getIBeaconInfo(i, uuid, major, minor, txPower);
//
    Serial.print(" ");
    Serial.print("iBeacon->");
    Serial.print("  UUID: ");
    Serial.print(uuid);
    Serial.print("\tMajor:");
    Serial.print(major);
    Serial.print("\tMinor:");
    Serial.print(minor);
    Serial.print("\ttxPower:");
    Serial.print(txPower);
  }        //change to string

  //--------------MQTT package, sending rssi, mac-----------------------
  String payload = "{\" rssi\": \"" + String(rssiglobal) + "\", "+ "\"MAC\" : \"" +(macaddr)+ "\","+ "\"distance\" : \"" +String(distlcd)+ "\", "+ "\"Antenna\" : \"" +(antennatype)+ "\"}";
    //Note: Pay attention to the json structure, missing commas or \ generate syntax problems

  // publish to QIoT Server
  if (mqttclient.publish(QIOT_TOPIC, payload.c_str()))
    {
      Serial.println("Message => " + payload + " has been sent to " + QIOT_SERVER_IP + ".");
    }
  else
    {
      lcd.clear();
      lcd.print("Failed payload");
      lcd.setCursor(0,1);
      lcd.print("Causes MQTT-Topic-Size");      
//      Serial.println("Could not send message :(");
    }
  Serial.println();
}
//[Function] (Layer 2 - Network Layer)------------------------------------Data Transmission----------------------------------------------------

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  setuplcd();
  pinMode (PIN_PLUS, INPUT);
  pinMode (PIN_MINUS, INPUT);
  pinMode (PIN_SCAN, INPUT);

  //LED warning no MQTT connection (NAS Problems)
  pinMode(LED_BUILTIN, OUTPUT);

   //4. Initialize LCD subsystem
  
  //1. Initialize BLE subsystem
  lcd.clear();
  lcd.print("BLE begin");
//  Serial.println("BLE begin");
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(10);
  }


  //2. Initialize Wifi subsystem
  wificonnect();

  //3. Initialize MQTT subsystem
  
  //MQTT connection (Same for NodeRED and QIOT)
  lcd.clear();
  lcd.print("Setting MQTT");
  lcd.setCursor(0,1);
  lcd.print("Please wait");  
  mqttclient.setServer(QIOT_SERVER_IP, QIOT_SERVER_PORT);
    
    if (mqttclient.connect(QIOT_CLIENT_ID, QIOT_USERNAME, QIOT_PASSWORD)) //Qiot
  //   if (mqttclient.connect(QIOT_CLIENT_ID))                            //NodeRED
      {
        lcd.clear();
        lcd.print("MQTT Connected");
        lcd.setCursor(0,1);
        lcd.print("Setup Success!");        
        
//        Serial.println("MQTT Connected");
        
      } 
    else 
      {
        lcd.clear();
        lcd.print("MQTT Unreachable");
        lcd.setCursor(0,1);
        lcd.print("MQTTReconnect");           
//        Serial.println("MQTT not available");
      }

  if (!mqttclient.connected())
        {
          mqttreconnect();
        }
  
  //Setup delay
  delay (2000);
}

void loop() {
  // read the pushbutton input pin:
  if (!mqttclient.connected())
        {
          mqttreconnect();
        }  
  
  buttonState = digitalRead(PIN_PLUS);
  buttonStateMinus = digitalRead (PIN_MINUS);
  buttonStateScan = digitalRead (PIN_SCAN);

  mqttclient.loop();
  mqttclient.subscribe(QIOT_TOPIC);

  //All button functions are embedded into this function
  buttonscan (buttonStateScan);

}
