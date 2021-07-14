#include <Arduino.h>
#include<EEPROM.h>
#include<SimpleTimer.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SimpleTimer positionTwoTimer(36000);
SimpleTimer demo(1800000);

SoftwareSerial WSerial(2,3);

uint8_t bSwitch = 12, fSwitch = 11, fanOut = 10;
uint8_t motA = A0, motB =A1 ;
bool forwardMotor = true, startMotor = false, timer2Active=false, timer4Active=false;
uint8_t restingPosition = 1;
bool startTimerTwo=false, startTimerOne=false;

void setup() {
    //to be removed
   // EEPROM.write(0,1);

    pinMode(bSwitch,INPUT);
    pinMode(fSwitch,INPUT);
    pinMode(motA,OUTPUT);
    pinMode(motB,OUTPUT);
    pinMode(fanOut,OUTPUT);

    Serial.begin(9600);
    WSerial.begin(9600);

    digitalWrite(motA,LOW);
    digitalWrite(motB,LOW);
    restingPosition = EEPROM.read(0);

}

void loop() {
// write your code here

//TODO: codes to listen to serial monitor for instruction on motor and fans

    StaticJsonDocument<1024> doc;
    if(WSerial.available()>0){

        DeserializationError error = deserializeJson(doc, WSerial);
        if(error){
            Serial.println("Invalid JSON object");

            return;
        }
        Serial.println("JSON Object Received");
       // Serial.println(doc["name"].as<String>());
        serializeJson(doc,Serial);
    }

if(demo.isReady()){
   // startMotor = true;
    demo.reset();
}
   // digitalWrite(fanOut,HIGH);

//    Serial.println("===================");
//    Serial.println(restingPosition);
//    Serial.println("===================");

if(startMotor==false){
    digitalWrite(motA,LOW);
    digitalWrite(motB,LOW);
}

    if(digitalRead(fSwitch)==0){
        forwardMotor = false;
        Serial.println("Forward pressed");

        if(restingPosition==1){
            startMotor=false;
            restingPosition=2;
            EEPROM.write(0,restingPosition);
        }

        if(restingPosition==4 &&startTimerTwo == false){
            startTimerTwo = true;
            positionTwoTimer.reset();

        }
    }

    if(digitalRead(bSwitch)==0){
        forwardMotor = true;
        //Serial.println("Backwards pressed");

        if(restingPosition==3){
            startMotor=false;
            restingPosition=4;
            EEPROM.write(0,restingPosition);
        }

        if(restingPosition==2 &&startTimerTwo == false){
            startTimerTwo = true;
            positionTwoTimer.reset();

        }
    }

    if(positionTwoTimer.isReady()&&startTimerTwo==true){
        startMotor=false;
        startTimerTwo=false;
        Serial.println("hapa kazi tuu.");
        if(restingPosition==4){
            restingPosition=1;
            EEPROM.write(0,restingPosition);
        }
        if(restingPosition==2){

            restingPosition=3;
            EEPROM.write(0,restingPosition);
        }
        positionTwoTimer.reset();
    }

    if(forwardMotor==true && startMotor == true){
        digitalWrite(motA,HIGH);
        digitalWrite(motB,LOW);
        Serial.println("F===========");
    }

    if(forwardMotor == false && startMotor == true){
        digitalWrite(motA,LOW);
        digitalWrite(motB,HIGH);
        Serial.println("B===========");
    }

}