#include <NMEA.h>

NMEA nmea;
char *data;
char *info;

void setup(){
  Serial1.begin(9600); // GPS module
  Serial.begin(9600); // USB
//  NMEA NMEA(Serial1);
//  NMEA.begin();
//  delay(500);
//  NMEA.process();
//  delay(200);
//  if(NMEA.isLocked())
//    Serial.write("WE LOCKED\n");
//  nmea = NMEA;
//  nmea.begin();
}

void loop(){
  Serial.write(Serial1.read());
//  nmea.process();
//  if(nmea.isLocked()){
//    Serial.write("LOCKED\n");
//    if(nmea.isUpdated()){
//      Serial.write("UPDATED\n");
//    }else{
//      Serial.write("NOT UPDATEDn");
//      return;
//    }
//  }else{
//    Serial.write("NOT LOCKED\n");
//    return;
//  }
//  
//  sprintf(info, "Satellites: %d - Time: %d/%d/%d %d:%d:%d\n", nmea.getSatellites(), nmea.getDay(), nmea.getMonth(), nmea.getYear(), nmea.getHour(), nmea.getMinute(), nmea.getSecond());
//  sprintf(data, "Lat: %d - Long: %d - Alt: %d - Speed(kn): %d - Bearing: %d\n", nmea.getLatitude(), nmea.getLongitude(), nmea.getAltitude(), nmea.getSpeed(true), nmea.getBearing());
//  Serial.write("TEST");
//  Serial.write(info);
//  Serial.write(data);
  delay(100);
}
