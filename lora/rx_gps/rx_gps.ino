// Feather9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_TX

#include <RH_RF95.h>
#include <SPI.h>

// for Feather32u4 RFM9x
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

/* for Feather m0 RFM9x
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
*/

#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Blinky on receipt
#define LED 13

// IMPORTANT: MUST CHANGE THESE VALUES BEFORE LAUNCH!!
#define LAT 34
#define LNG -118

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

int packet_num = 0;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    Serial.begin(115200);
    while (!Serial) {
        delay(1);
    }
    delay(100);

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
}

void loop() {
    if (rf95.available()) {
        // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        if (rf95.recv(buf, &len)) {
            packet_num++;
            digitalWrite(LED, HIGH);

            // gps reading
            memcpy(&coord, buf, sizeof(coord));
            Serial.print("Got: ");
            Serial.print(LAT);
            Serial.print(".");
            printFormatted(coord.lat);  // Receives 2 bytes, then rounds down
            Serial.print(", ");
            Serial.print(LNG);
            Serial.print(".");
            printFormatted(coord.lng);  // Receives 2 bytes, then rounds down

            Serial.println("Packet: ");
            Serial.print(packet_num);

            /*Serial.print(", Packet Num: ");
            Serial.println(coord.packet_num);*/

            // rssi
            Serial.print("RSSI: ");
            Serial.println(rf95.lastRssi(), DEC);
        } else {
            Serial.println("Receive failed");
        }
    }
}
