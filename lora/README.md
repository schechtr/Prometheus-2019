### frequency can be specified here:
	-// Change to 434.0 or other frequency, must match RX's freq!
	#define RF95_FREQ 915.0

### when not tethered to a computer remove the while(!serial) line in the setup function

### output power level can be specified here:
  -// you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

### recieved signal strength RSSI:
 - It also prints out the RSSI which is the receiver signal strength indicator. This number will range from about -15 to 	about -100. The larger the number (-15 being the highest you'll likely see) the stronger the signal.

