//
// Created by Master Tony on 6/25/2021.
//

#ifndef MOTORCONTROLLER_MOTORCONTROLLER_H
#define MOTORCONTROLLER_MOTORCONTROLLER_H

#endif //MOTORCONTROLLER_MOTORCONTROLLER_H


//void sendWifiData() {
//    Serial.println("+++++++++++++++++++++++++++++");
//    DynamicJsonDocument doc(128);
//    doc["temperature"] = temp;
//    doc["humidity"] = hum;
//    doc["incubationStatus"] = incubationActive;
//    doc["outsideFanStatus"] = fan2status
//    doc["powerPriority"] = powerPriority;
//    doc["birdType"] = birdTypeNo;
//    doc["incubationDays"] = incubationDays;
//    doc["hatchingDays"] = hatchingDays;
//    doc["numberOfDaysElapsed"] = day;
//    serializeJson(doc, WiFiSerial);
//
////    serializeJson(doc, json);
////    Serial.println(WiFiSerial.read());
//
//    serializeJson(doc, Serial);
//    if (WiFiSerial.availableForWrite() > 0) {
//        serializeJson(doc, WiFiSerial);
//    }
//    String status = "";
//    status = WiFiSerial.readStringUntil('0');
//    if (status.length() > 0) {
//        Serial.println("Data sent successfully");
//    } else {
//        Serial.println("Data not sent");
//    }
//    Serial.println("=========================================");
//    delay(10000);
//}