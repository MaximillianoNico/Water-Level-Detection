//#define BLYNK_PRINT Serial            // defenisikan Blynk Serial 
//#include <ESP8266_Lib.h>              // menyertakan Library ESP8266 kedalam program
//#include <BlynkSimpleShieldEsp8266.h> // menyertakan Library Blynk kedalam program
//
//char auth[] = "2pqrVNOrS7s87thzBuJGyKrmxwms5oBE";
//
//// Your WiFi credentials.
//// Set password to "" for open networks.
//char ssid[] = "Max1";
//char pass[] = "nikomax149108";
//
//
//#include <SoftwareSerial.h> // menyertakan Library SoftSer kedalam program#include <SoftwareSerial.h>
//SoftwareSerial MySerial(0, 1); //Pick a more meaningful name!
//
//#define ESP8266_BAUD 9600 //set baudrate ESP8266 default 115200 atau 9600 silahkan ganti dengan yang sesuai
//
//ESP8266 wifi(&MySerial);

#define pinEcho 10
#define pinTrigger 9
#define pinLED 13
#define CommandSerial 9600



int river_height_limit = 15; // in cm


void setup() {
//  //setup wifi
//  Serial.begin(9600); // program komunikasi atau setup untuk serial monitor dan kecepatan komunikasi (baudrate)
//  delay(10); // jeda 10ms
//
//  MySerial.begin(ESP8266_BAUD); // program komunikasi ESP8266 setup kecepatan komunikasi (baudrate)
//  delay(10); // jeda 10ms
//
//  Blynk.begin(auth, wifi, ssid, pass); // program komunikasi blynk menggunakan wifi

  declare();
}

void declare(){
    //register pinLED as OUTPUT
  pinMode(pinLED, OUTPUT);
  
  //register pinTrigger as OUTPUT
  pinMode(pinTrigger, OUTPUT);
  
  //register pinEcho as INPUT
  pinMode(pinEcho, INPUT);

  //declare Serial 9600 as output
  Serial.begin(CommandSerial);
}

// the loop function runs over and over again forever
void loop() {
//  Blynk.run(); //menjalankan program blynk
  int distance = calculate_water();
  check_water(distance);
}

void check_water(int distance){
  if(distance < river_height_limit){
    
    Serial.println(String("Beware! River Height is ") + distance + String(" cm"));
    digitalWrite(pinLED, HIGH);   // turn the LED on (HIGH is the voltage level)
 
  } else {
                        // wait for a second
    digitalWrite(pinLED, LOW);    // turn the LED off by making the voltage LOW
  
  }
}

int calculate_water(){
  int duration, distance;
    digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  
  duration = pulseIn(pinEcho, HIGH);

  distance = duration* 0.034 /2;

  return distance;
}

