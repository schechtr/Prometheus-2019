#include <Adafruit_MAX31856.h>
#include "debug.h"
//#include <SoftwareSerial.h>
//#include <string>

const int NUM_CPLS = 2;
const int DATA_LEN = 5;

Adafruit_MAX31856 cpls[NUM_CPLS];

// Use software SPI: CS, DI, DO, CLK
cpls[1] = Adafruit_MAX31856(10, 11, 12, 13);
cpls[2] = Adafruit_MAX31856(6, 7, 8, 9);

// use hardware SPI, just pass in the CS pin
// Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10);

// SoftwareSerial ports
// SoftwareSerial myrio_serial(0, 1); //rx, tx

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }
    // Serial.println("MAX31856 thermocouple test");

    for (int i = 0; i < NUM_CPLS; i++) {
        cpls[i].begin();
        cpls[i].setThermocoupleType(MAX31856_TCTYPE_K);
    }

    // printCplInfo();
}

void loop() {
    // Serial.print("Cold Junction Temp: ");
    // Serial.println(maxthermo.readCJTemperature());

    // Serial.print("Temp 1: ");
    // Serial.print(thermocouple_1.readThermocoupleTemperature());
    int data[NUM_CPLS];
    char dataToSend[DATA_LEN * NUM_CPLS];

    for (int i = 0; i < NUM_CPLS; i++) {
        data[i] = cpls[i].readThermocoupleTemperature();

        for (int j = DATA_LEN - 1; j >= DATA_LEN * (i - 1); j--) {
            int digit = temp1_reading % 10;
            temp1_reading /= 10;

            dataToSend[j] = digit + '0';
        }
    }

    Serial.write(dataToSend, DATA_LEN * NUM_CPLS);

    // delay(500);

    /*
    Serial.write(arr2, 5);

    delay(500);*/

    // Serial.print(" Temp 2: ");
    // Serial.println(thermocouple_2.readThermocoupleTemperature());
    // string temp2 = "Temp 2:" + thermocouple_2.readThermocoupleTemperature();
    // Serial.write(temp2);

    // checkFaults();
}