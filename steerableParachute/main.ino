#include <ServoTimer2.h> 
//using this Library because of problems with GPS.begin and servos
//the latest Arduino compiler (1.6) doesnt compile right!
//redundant
#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>
/* 
Connect Receiver to D6
Connect Servo to D4
Connect RotaryEncoder1: DT -> D7 & CLK  -> D2 (Can be used as interrupt!)
//Serial1RX to GPS TX
//Serial1TX to GPS RX
//GPS Modul uses 5V/3v3 also possible
*/

//Gps
//SoftwareSerial GPSPort(12, 13);
//Adafruit_GPS GPS(&GPSPort);
//#define rxGPS 0
//#define txGPS 1
//SoftwareSerial serialGPS = SoftwareSerial(rxGPS, txGPS);
//Rotary Encoders (2&3 are Interupt Pins on Nano)


//onboard pin for information Communication
#define ledPin LED_BUILTIN

#define ServoMaxRot -50 //~15 is one rotation
#define turnServoCW 1450
#define turnServoCCW 1550

#define Servo2 4
#define Servo1 5

#define ServoStop 1500

#define Receiver 6

int ReceiverValue;
int prevReceiverValue = 1500;
int addrEEPROM = 1;

volatile int positionEnc1 = 0;
volatile int positionEnc2 = 0;

void setupGPS();
void setupEncoders();
void GPSloop();

const word printInterval = 1000;
unsigned long previousPrint;

ServoTimer2 servo1;
ServoTimer2 servo2;

void setup() {
  
  servo1.attach(Servo1);
  servo2.attach(Servo2);
  servo1.write(ServoStop);//1300-1700 mid: 1500 Doc for servo: https://www.parallax.com/sites/default/files/downloads/900-00025-High-Speed-CR-Servo-Guide-v1.1.pdf
  servo2.write(ServoStop);
  //Setup GPS
  setupGPS();
  //start Serial Connection
  Serial.begin(9600);
  setupEncoders();
  //init Receiver
  pinMode(Receiver, INPUT);
  pinMode(ledPin, OUTPUT);
  delay(200);
  
}

void loop() {
  
  ReceiverValue = pulseIn(Receiver,HIGH,35000);//range of 1000-2000 in this case (old Graupner) (depends on used receiver!)
  loopGPS(); //TODO enable!!!!!
  //servo1.write(turnServoCCW);
  if (ReceiverValue <= 1000 or ReceiverValue >= 2000){
    //ReceiverValue = prevReceiverValue;
    digitalWrite(ledPin, HIGH);
    }
  else if (ReceiverValue>=1300 && ReceiverValue<=1700){
    
    if (positionEnc1<0){
      servo1.write(turnServoCW);
      }
    if (positionEnc2<0){ 
      servo2.write(turnServoCW);
      }
    delay(50);
    }
  else if (ReceiverValue < 1300){

    //Serial.println(ReceiverValue);
    //the interupts get called (because Encoders are attached)
    if (positionEnc2>ServoMaxRot){
       servo2.write(turnServoCCW);
      }
    
    if (positionEnc1<0){
      servo1.write(turnServoCW);
      }
    delay(50);

    //Serial.println(RotEnc1Pos); 
    }
    
  else if ((ReceiverValue > 1700)){
    if (positionEnc1>ServoMaxRot){
       servo1.write(turnServoCCW);
      }
   
    if (positionEnc2<0){
      servo2.write(turnServoCW);
      }
    delay(50);
  }
  //stop servor after the prevoius delay
  servo1.write(ServoStop);
  servo2.write(ServoStop);
  //printMillis();
}

void printMillis(){  
  if ((millis() - previousPrint) >= printInterval ) {
    previousPrint = millis();
    noInterrupts();
    int Variable_Copy = positionEnc1;
    int Variable_Copy2 = positionEnc2;
    interrupts();

    
  }
  }

