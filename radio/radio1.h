#define DEBUG 1
#include <Gpsneo.h>
Gpsneo gps(5, 6, 9600);

/*char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];
*/

char* timeee = "1234567890";
char statusss[3];
char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];
char speedKnots[10];
char trackAngle[8];
char date[10];
char magneticVariation[10];
char magneticVariationOrientation[3];


void  setup()
{
    Serial.begin(9600);
}
void loop()
{
    //Just simple do ge`tDataGPRMC, and the method solve everything.
    gps.getDataGPRMC(timeee,
                    statusss,
                    latitud,
                    latitudHemisphere,
                    longitud,
                    longitudMeridiano,
                    speedKnots,
                    trackAngle,
                    date,
                    magneticVariation,
                    magneticVariationOrientation);
   //Serial.println("update");
   Serial.write(timeee, 10);
   Serial.println("update");
   /*Serial.println(timeee);
   Serial.println(statusss);
   Serial.println(latitud);
   Serial.println(latitudHemisphere);
   Serial.println(longitud);
   Serial.println(longitudMeridiano);
   Serial.println(speedKnots);
   Serial.println(trackAngle);
   Serial.println(date);
   Serial.println(magneticVariation);
   Serial.println(magneticVariationOrientation);*/
}
