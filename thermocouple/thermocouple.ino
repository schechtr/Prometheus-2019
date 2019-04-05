#include <Adafruit_MAX31856.h>
//#include <SoftwareSerial.h>
//#include <string>


// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 thermocouple_1 = Adafruit_MAX31856(10, 11, 12, 13);

Adafruit_MAX31856 thermocouple_2 = Adafruit_MAX31856(6, 7, 8, 9);

// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10);


//SoftwareSerial ports
//SoftwareSerial myrio_serial(0, 1); //rx, tx

void setup() {
  Serial.begin(9600);
  while (!Serial)
  {
      
  }
  //Serial.println("MAX31856 thermocouple test");

 thermocouple_1.begin();
 thermocouple_2.begin();

  thermocouple_1.setThermocoupleType(MAX31856_TCTYPE_K);
  thermocouple_2.setThermocoupleType(MAX31856_TCTYPE_K);

/*
  Serial.print("Thermocouple type: ");
  switch (maxthermo.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }
*/

  //myrio_serial.begin(115200);
  
} 

void loop() {
  //Serial.print("Cold Junction Temp: "); 
  //Serial.println(maxthermo.readCJTemperature());

  //Serial.print("Temp 1: "); 
  //Serial.print(thermocouple_1.readThermocoupleTemperature());
  
  //string temp1 = thermocouple_1.readThermocoupleTemperature();
 // Serial.write(temp1);

  char arr[] = "hello jack";
  char arr2[] = "123  ";
  //String send = "123";

 
    Serial.write(arr, 20);
  
    delay(500);
  
  
    Serial.write(arr2, 10);
  
    delay(500);


  

  //Serial.print(" Temp 2: ");
  //Serial.println(thermocouple_2.readThermocoupleTemperature());
  //string temp2 = "Temp 2:" + thermocouple_2.readThermocoupleTemperature();
  //Serial.write(temp2);



  /*
  // Check and print any faults
  uint8_t fault = maxthermo.readFault();
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range Fault");
    if (fault & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range Fault");
    if (fault & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High Fault");
    if (fault & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low Fault");
    if (fault & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High Fault");
    if (fault & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low Fault");
    if (fault & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage Fault");
    if (fault & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open Fault");
  }
  */

  
}
