#include <Arduino.h>
#include<EEPROM.h>
#include <SoftwareSerial.h>
#include<SimpleTimer.h>
#include <ArduinoJson.h>

SimpleTimer positionTwoTimer(36000);
SimpleTimer demo(180000);


//Communication Pins
uint8_t input_rx_pin = 2;
uint8_t input_tx_pin = 3;

uint8_t output_rx_pin = 4;
uint8_t output_tx_pin = 5;

SoftwareSerial InputSerial(input_rx_pin, input_tx_pin);
SoftwareSerial OutputSerial(output_rx_pin, output_tx_pin);

StaticJsonDocument <1024>doc;


int bSwitch = 12, fSwitch = 11, fanOut = 10;
int motA = A0, motB =A1 ;
bool forwardMotor = true, startMotor = false, timer2Active=false, timer4Active=false;
int restingPosition = 1;
bool startTimerTwo=false, startTimerOne=false;

bool fan2status = false;


void sendData(){
    serializeJson(doc, OutputSerial);
}


void receiveData(){
    if(InputSerial.available() > 0){
        DeserializationError error =  deserializeJson(doc, InputSerial);
        Serial.println(error.c_str());
        if(error.code() == ArduinoJson6180_91::DeserializationError::Ok){
            startMotor = doc["startMotor"];
            fan2status = doc["fan2status"];
            sendData();
        }
    }

}

void setup() {
    //to be removed
    // EEPROM.write(0,1);

    pinMode(bSwitch,INPUT);
    pinMode(fSwitch,INPUT);
    pinMode(motA,OUTPUT);
    pinMode(motB,OUTPUT);
    pinMode(fanOut,OUTPUT);

    Serial.begin(115200);
    OutputSerial.begin(115200);
    InputSerial.begin(115200);

    digitalWrite(motA,LOW);
    digitalWrite(motB,LOW);
    restingPosition = EEPROM.read(0);

}

void loop() {
    // write your code here

    //TODO: codes to listen to serial monitor for instruction on motor and fans

    //if(demo.isReady()){
    //    startMotor = true;
    //    demo.reset();
    //}
    //    digitalWrite(fanOut,HIGH);

    receiveData();

    Serial.println("===================");
    Serial.println(restingPosition);
    Serial.println("===================");

    if(!startMotor){
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

        if(restingPosition==4 &&!startTimerTwo){
            startTimerTwo = true;
            positionTwoTimer.reset();

        }
    }

    if(digitalRead(bSwitch)==0){
        forwardMotor = true;
        Serial.println("Backwards pressed");

        if(restingPosition==3){
            startMotor=false;
            restingPosition=4;
            EEPROM.write(0,restingPosition);
        }

        if(restingPosition==2 &&!startTimerTwo){
            startTimerTwo = true;
            positionTwoTimer.reset();

        }
    }

    if(positionTwoTimer.isReady()&&!startTimerTwo){
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

    if(forwardMotor && startMotor){
        digitalWrite(motA,HIGH);
        digitalWrite(motB,LOW);
        Serial.println("F===========");
    }

    if(!forwardMotor && startMotor){
        digitalWrite(motA,LOW);
        digitalWrite(motB,HIGH);
        Serial.println("B===========");
    }

}