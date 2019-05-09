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

#define DEBUG 1

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

TinyGPSPlus gps;

// curently 10 bytes, but we can reduce that if needed. Packet Num is unecesary.
// Just needed for testing.
struct gpsCoordinate {
    uint16_t lat;
    uint16_t lng;
} coord;

uint8_t tx_buf[sizeof(coord)];

void setup() {
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    Serial.begin(115200);

    // wait for usb serial, remove this line when not connected to pc
    while (!Serial) {
        delay(1);
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
        Serial.println("LoRa radio init failed");
        while (1)
            ;
    }
    Serial.println("LoRa radio init OK!");

    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ)) {
        Serial.println("setFrequency failed");
        while (1)
            ;
    }
    Serial.print("Set Freq to: ");
    Serial.println(RF95_FREQ);

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf =
    // 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST
    // transmitter pin, then you can set transmitter powers from 5 to 23 dBm:
    rf95.setTxPower(23, false);

    // coord.packet_num = 0;
}

void loop() {
    //Serial.print("loop");
    if (gpsSerial.available()) {
        //Serial.print("loop");
        gps.encode(gpsSerial.read());
        if (gps.location.isUpdated()) {
            //Serial.println("loop");

            coord.lat = (uint16_t)(gps.location.rawLat().billionths >> 16);
            coord.lng = (uint16_t)(gps.location.rawLng().billionths >> 16);
            // coord.packet_num += 1;

            memcpy(tx_buf, &coord, sizeof(coord));
            uint8_t tx_buf_len = sizeof(coord);

            if (DEBUG) {
                //Serial.print("loop");
                Serial.println(gps.location.rawLat().billionths);
                Serial.println(gps.location.rawLng().billionths);
                Serial.print(coord.lat);
                Serial.print(", ");
                Serial.print(coord.lng);
                // Serial.print(", Packet Num: ");
                // Serial.println(coord.packet_num);

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
