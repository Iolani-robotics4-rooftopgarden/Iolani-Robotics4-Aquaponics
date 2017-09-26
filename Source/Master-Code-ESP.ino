#include <UbidotsMicroESP8266.h>

/* This Master code incorporates the float sensors, temperature sensors, and fish feeder control in order
to gather data that can be used to monitor the aquaponics system on 4th floor Sullivan. Created by Shane and Matthew
Project: RoofTopGarden */
#include <OneWire.h>
#include <DallasTemperature.h>
#include "HTTPSRedirect.h"
#include <ESP8266WiFi.h>
#include <WifiUDP.h>
#include <String.h>
#include <Wire.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>



// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "ca.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String date;
String t;
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
const char * ampm[] = {"AM", "PM"} ;

#define ID1 "5890e3fc76254253b40c38b5" // temp sensor
#define ID2 "588baa1e762542036842ef85" // float sensor
#define ID3 "5890e63476254253b40c4d2c" //fishfeeder
#define ID4 "589e1b3e76254210a06ba5db" // ...
#define TOKEN "wemRu3qNO3DyZHDLKkNMhQboTOXH3O" // Put here your Ubidots TOKEN
#define WIFISSID "Palila"
#define PASSWORD "io71redbird51"
#define ONE_WIRE_BUS D1
#define SensorPin A0

OneWire oneWire (ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);

Ubidots client1(TOKEN);

//float values for the code
float value;
float value3;
float phValue;

//integer values for the code
int lvl1 = D2;
int lvl2 = D3;
int lvl3 = D7;
int lvl4 = D5;

int fv1;
int fv2;
int fv3;
int fv4;
int oldvalue;
unsigned long timeoldvalue = 0;
int oldoldvalue = 0;

unsigned long t1 = 0;

// The ID below comes from Google Sheets.
// Towards the bottom of this page, it will explain how this can be obtained
const char *GScriptId = "AKfycbyADaLgXg7z5jGJZCI5vA0eaqvZslhVr2qLIveNxy4ULRgCpb40";

// Push data on this interval
const int dataPostDelay = 300000; 
const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";

const int httpsPort =  443;
HTTPSRedirect client(httpsPort);
String url = String("/macros/s/") + GScriptId + "/exec?";

const char* fingerprint = "F0 5C 74 77 3F 6B 25 D7 3B 66 4D 43 2F 7E BC 5B E9 28 86 AD";


void setup() {
  // Put your setup code here, to run once:
  // Begin the Serial Monitor
  Serial.begin(115200);
  delay(10);
  //Connect the ESP to the Wifi
  timeClient.begin();   // Start the NTP UDP client

  Wire.pins(0, 2);  // Start the OLED with GPIO 0 and 2 on ESP-01
  Wire.begin(0, 2); // 0=sda, 2=scl
  
  client1.wifiConnection(WIFISSID, PASSWORD);
  //Declare what each pin will do 
  pinMode(D2, INPUT_PULLUP);

  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client.connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
    if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    Serial.flush();
    return;
  }
  pinMode(D3, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D8, OUTPUT);

}

void waterlevel(){
if(fv4 == 1){
  if(fv3 == 1){
    if(fv2 == 1){
      if(fv1 == 1){
        value = 0;
      }
      else{
        value = 1;
      }
    }
    else{
      value = 2;
    }
  }
  else{
    value = 3;
  }
}
  else{
    value = 4;
  }
}

void postData(float fsensor, float temps, float pHs){
  if (!client.connected()){
    Serial.println("Connecting to client again..."); 
    client.connect(host, httpsPort);
  }
  String urlFinal = url + "fsensor=" + String(fsensor) + "&temps=" + String(temps) + "&pHs=" + String(pHs);
  client.printRedir(urlFinal, host, googleRedirHost);
}

void loop() {
  // put your main code here, to run repeatedly:
  fv1 = digitalRead(lvl1);
  fv2 = digitalRead(lvl2);
  fv3 = digitalRead(lvl3);
  fv4 = digitalRead(lvl4);
  waterlevel();
  getpH();
  float value2 = getTemp();
  value3 = client1.getValue(ID3);
  Serial.println(value3);
  if(value3 != oldvalue){
    digitalWrite(D8, HIGH);
    oldoldvalue= 1;
    oldvalue = value3;
    Serial.print(" : ");
    Serial.print(oldvalue);
    delay(10);
  }
  else if(oldoldvalue == 1){
    Serial.println("did not go through");
    digitalWrite(D8, LOW);
    oldoldvalue = 0;
  }
  client1.add(ID1, value);
  client1.add(ID2, value2);
  client1.add(ID4, phValue); 
  client1.sendAll();


  postData(value, value2, phValue);


  //checkTime();
  checkRealtime();

}

float getTemp(){
    sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  if(temp > -127 && temp <50){
    return temp;
  }
}



void getpH(){
float phValue=analogRead(SensorPin)*5.0/1024; //convert the analog into millivolt
phValue=3.5*phValue;
phValue = phValue++;//convert the millivolt into pH value
}

void checkTime(){ // fisx this first if statement, maybe sending high and low 
  t1 = millis() - timeoldvalue;
  if(t1 > 120000 /*&& superoldvalue == 0*/){
    digitalWrite(D8, HIGH);
    Serial.println("Feeding...");
    //digitalWrite(D8, LOW);
    //superoldvalue = 1;
  }
  if(t1> 125000){
    timeoldvalue = millis();
    digitalWrite(D8, LOW);
    Serial.println("Stop Feeding...");
    //superoldvalue = 0;
  }
}
void checkRealtime(){
  date = "";  // clear the variables
    t = "";
    
    // update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    unsigned long epochTime =  timeClient.getEpochTime();

    // convert received time stamp to time_t object
    time_t local, utc;
    utc = epochTime;

    // Then convert the UTC UNIX timestamp to local time
    TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -600};  //UTC - 5 hours - change this as needed
    TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -660};   //UTC - 6 hours - change this as needed
    Timezone usEastern(usEST, usEST);
    local = usEastern.toLocal(utc);

    // now format the Time variables into strings with proper names for month, day etc
    date += days[weekday(local)-1];
    date += ", ";
    date += months[month(local)-1];
    date += " ";
    date += day(local);
    date += ", ";
    date += year(local);

    // format the time to 12-hour format with AM/PM and no seconds
    t += hourFormat12(local);
    t += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      t += "0";
    t += minute(local);
    t += " ";
    t += ampm[isPM(local)];

    // Display the date and time
    /*Serial.println("");
    Serial.print("Local date: ");
    Serial.print(date);
    Serial.println("");
    Serial.print("Local time: ");
    Serial.print(t);*/
    //if(minute(local) % 2 == 0){
    if(t == "3:00 AM" ||t == "3:00 PM"){
    digitalWrite(D8, HIGH);
    Serial.println("Feeding...");
    }
    else{
    digitalWrite(D8, LOW);
    Serial.println("Stop Feeding...");}
}
