
// Feather9x_TX
// -*- mode: C++ -*-

#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>

// for feather32u4 RFM9x
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

#define RF95_FREQ 915.0
#define gpsSerial Serial1

#define DEBUG 0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

TinyGPSPlus gps;

// curently 10 bytes, but we can reduce that if needed. Packet Num is unecesary.
// Just needed for testing.
struct gpsCoordinate {
    uint16_t lat;
    uint16_t lng;
} coord;

void printFormatted(uint16_t coordVal) {  // Prints decimal value
    uint32_t adjustedVal = (uint32_t)coordVal << 16;
    char toPrint[10];
    sprintf(toPrint, "%09lu", adjustedVal);  // Pad with zeroes
    toPrint[5] = '\0';                       // Truncate to 5 sigfigs
    Serial.print(toPrint);
}

uint8_t tx_buf[sizeof(coord)];

void setup() {
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    if (DEBUG) {
    Serial.begin(115200);

    
    // wait for usb serial, remove this line when not connected to pc
    while (!Serial) {
      delay(1);
    }

    }

    delay(100);

    gpsSerial.begin(9600);

    // manual reset
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    // initialize radio
    while (!rf95.init()) {
        if (DEBUG) { Serial.println("LoRa radio init failed"); }
        while (1)
            ;
    }
    Serial.println("LoRa radio init OK!");

    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ)) {
        if (DEBUG) { Serial.println("setFrequency failed"); }
        while (1)
            ;
    }

    if (DEBUG) {
    Serial.print("Set Freq to: ");
    Serial.println(RF95_FREQ);
    }

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf =
    // 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST
    // transmitter pin, then you can set transmitter powers from 5 to 23 dBm:
    rf95.setTxPower(23, false);

    // coord.packet_num = 0;
}

void loop() {
    int m;
    uint32_t lat, lng;
    // Serial.print("loop");
    if (gpsSerial.available()) {
      //Serial.write(gpsSerial.read());
        //Serial.print('\n');
        //return;
        gps.encode(gpsSerial.read());
        if (gps.location.isUpdated()) {
            // Serial.println("loop");

            lat = gps.location.rawLat().billionths;
            lng = gps.location.rawLng().billionths;

            lat += ((lat & 0x00008000) << 1);     // Rounding
            lng += ((lng & 0x00008000) << 1);

            coord.lat = (uint16_t)(lat >> 16);
            coord.lng = (uint16_t)(lng >> 16);
            // coord.packet_num += 1;

            memcpy(tx_buf, &coord, sizeof(coord));
            uint8_t tx_buf_len = sizeof(coord);

            char buf[50];
            
            if (DEBUG) {
                //Serial.println((gps.location.rawLng().billionths) / 1000);
                printFormatted(coord.lat);
                Serial.print(", ");
                printFormatted(coord.lng);
                Serial.println("");
                Serial.println(tx_buf_len);
                Serial.println("Sending...");
            }

            delay(10);
            rf95.send((uint8_t *)tx_buf, tx_buf_len);
            delay(10);
            rf95.waitPacketSent();

            delay(1000);
        }
    }
}
