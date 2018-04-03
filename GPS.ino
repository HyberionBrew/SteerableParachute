#include <NMEAGPS.h>
#include <EEPROM.h>

//======================================================================
//  Program: NMEAsimple.ino
//
//  Description:  This program shows simple usage of NeoGPS
//
//  Prerequisites:
//     1) NMEA.ino works with your device (correct TX/RX pins and baud rate)
//     2) At least one of the RMC, GGA or GLL sentences have been enabled in NMEAGPS_cfg.h.
//     3) Your device at least one of those sentences (use NMEAorder.ino to confirm).
//     4) LAST_SENTENCE_IN_INTERVAL has been set to one of those sentences in NMEAGPS_cfg.h (use NMEAorder.ino).
//     5) LOCATION and ALTITUDE have been enabled in GPSfix_cfg.h
//
//  'Serial' is for debug output to the Serial Monitor window.
//
//  License:
//    Copyright (C) 2014-2017, SlashDevin
//
//    This file is part of NeoGPS
//
//    NeoGPS is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    NeoGPS is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with NeoGPS.  If not, see <http://www.gnu.org/licenses/>.
//
//======================================================================

#include <GPSport.h>
//RX to TX
//TX to RX
NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

int storeAltitude = 0;
void savetoEEPROM(unsigned long latitude, unsigned long longitude,unsigned timeElapsed, int altitude, int ReceiverValue);
void setupGPS() {
  while (!Serial)
    ;
  DEBUG_PORT.print( F("NMEAsimple.INO: started\n") );

  gpsPort.begin(9600);
}

//--------------------------

void loopGPS()
{
  while (gps.available( gpsPort )) {
    fix = gps.read();

    DEBUG_PORT.print( F("Location: ") );
    if (fix.valid.location) {
      
      unsigned long storeLatitude = (unsigned long) (fix.latitude() * 1000000);
      unsigned long storeLongitude = (unsigned long) (fix.longitude() * 1000000);
      DEBUG_PORT.println( storeLatitude );
      DEBUG_PORT.println( storeLongitude );
      if (fix.valid.altitude) {
        storeAltitude = (int) (fix.altitude());
      }
      else {
        storeAltitude = 0;
      }
      if (addrEEPROM + 16 < EEPROM.length()) {
        unsigned long timeElapsed = millis();
        savetoEEPROM(storeLatitude, storeLongitude,timeElapsed, storeAltitude, ReceiverValue);
      //  DEBUG_PORT.println();
      }
      else{
         EEPROM.write(0, 1);
        }
    }
  }

}


