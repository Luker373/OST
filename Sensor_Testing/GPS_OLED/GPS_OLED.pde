/***********************************************************

GPS + OLED DEMO

ChipKIT UNO32 + Pmod Shield
(C)2012 Giovanni Bernardo
http://www.settorezero.com

Setup:
in "Tools" Menù -> Board
select "ChipKIT UNO32 + Pmod Shield"

Connections:
Pmod GPS on top of header JD
Pmod OLED on header JC

Notes:
Idea of buffer scanning based on the  
code of Igor Gonzalez Martin at 
http://arduino.cc/playground/Tutorials/GPS
with major modifications

***********************************************************/

#include <DSPI.h>
#include <OLED.h>

// global variables
OledClass OLED;
const char gpssentence[]="$GPRMC"; // GPS sentence to find
char rxbuffer[200]; // buffer where entire sentences are stored
unsigned char i=0; // buffer index
unsigned int commas[13]; // commas positions in the sentence

// variables used for leds
char LEDS[] {30,31,33,37}; // the 4 leds on the chipKIT Pmod Shield (with "+ Pmod Shield" board-variant!!)
char ledcounter=0; // used for led scanning
// those values are used to obtain a delay in led scanning
unsigned long ledtimer=0; // delay counter for led scanning
#define led_slow  600000 // slow delay value
#define led_fast  320000 // fast delay value
unsigned long led_target=led_slow; // delay target actual value

// buffers in which store single values from GPRMC sentence
char latitude[11]; // 9 bytes for latitude value + 1 byte for N/S indicator + 1 byte for string termination
char longitude[12]; // 10 bytes for latitude value + 1 byte for E/W indicator + 1 byte for string termination
char utc[9]; // time UTC (hh:mm:ss) // 8 bytes + termination
char dat[9]; // date (dd/mm-yy) // 8 bytes + termination
char fix; // fix status from GPS (A or V)
boolean fixed; // fix status (true or false)

void setup() 
  {
  OLED.begin(); // Pmod OLED on header JC
  Serial1.begin(9600); // UART2 - Pmod GPS on header JD
  // make led ports as output, with all leds turned off
  for (char a=0; a<4; a++)
    {
    pinMode(LEDS[a],OUTPUT);
    digitalWrite(LEDS[a],0); 
    }
  }

// function used to scan the 4 leds on Pmod Shield
void leds(void)
  {
  digitalWrite(LEDS[ledcounter],1); // turn on actual led
  if (ledcounter==0) // if actual led is the first
    {
    digitalWrite(LEDS[3],0); // turn off the last led
    }
  else // if actual led isn't the first
    {
    digitalWrite(LEDS[ledcounter-1],0); // turn off the previous led
    }
  ledcounter++; // go to next led
  if (ledcounter>3) // we've reached the last led
    {
    ledcounter=0;  
    }
  }

// function used to turn off the 4 leds on Pmod Shield
// not used in this code
void ledsoff(void)
  {
  for (char a=0; a<4; a++)
    {
    digitalWrite(LEDS[a],0); 
    }
  }

void loop() 
  {
  if (Serial1.available()) 
    {
    int rxgps=Serial1.read(); // read byte from gps
    rxbuffer[i++]=rxgps; // store in the buffer
    
    if (rxgps==0x0A) // Line Feed detected => end of a sentence
      {
      char match=0; // counter for sentence matching
      // scan the first 6 bytes in the buffer 
      // for searching the sentence $GPRMC
      for (int u=0; u<7; u++)
        {
        if (rxbuffer[u]==gpssentence[u])
          {
          match++; // 1 byte matches!
          // if 6 bytes will match, then this counter will reach value 6
          }
        }

      // Sentence found!
      if (match==6)
        {
        unsigned int co=0; // comma index counter
        // scan entire buffer for find commas
        // that separates single values of the sentence
        for (unsigned int u=0; u<300; u++)
          {
          if (rxbuffer[u]==',')
            {
            commas[co]=u;
            co++; 
            }
          else if (rxbuffer[u]=='*') // end of the buffer
            {
            commas[12]=u;
            }
          } // end scan
        
        // Now extract single elements from the buffer and 
        // store each in a separate buffer

        int a=0; // use for generic counter
        
        // FIX STATUS (contained between comma 1 and comma 2)
        // A=fixed, V=not fixed
        fix=rxbuffer[commas[1]+1];
        if (fix=='A')
          {
          fixed=true;
          led_target=led_fast; // set led scanning to fast
          }
        else
          {
          fixed=false;
          led_target=led_slow; // set led scanning to slow
          }
        
        // extract latidude/longitude only if GPS status is fixed
        if (fixed)
          {
          // LATITUDE (contained between comma 2 and comma 3)
          for (int u=commas[2]+1; u<commas[3]; u++)
            {
            latitude[a]=rxbuffer[u];
            a++;  
            }
          latitude[a]=rxbuffer[commas[3]+1]; // N/S, between comma 3 and comma 4
          latitude[a+1]='\0'; // terminate buffer
          
          // LONGITUDE (contained between comma 4 and comma 5)
          a=0;
          for (int u=commas[4]+1; u<commas[5]; u++)
            {
            longitude[a]=rxbuffer[u];
            a++;  
            }
          longitude[a]=rxbuffer[commas[5]+1]; // E/W, between comma 5 and comma 6
          longitude[a+1]='\0'; // terminate buffer
          } // end of is-fixed
        
        // TIME UTC (contained between comma 0 and comma 1)
        utc[0]=rxbuffer[commas[0]+1]; // HH
        utc[1]=rxbuffer[commas[0]+2];
        utc[2]=':';
        utc[3]=rxbuffer[commas[0]+3]; // mm
        utc[4]=rxbuffer[commas[0]+4];
        utc[5]=':';
        utc[6]=rxbuffer[commas[0]+5]; // ss
        utc[7]=rxbuffer[commas[0]+6];
        
        // DATE UTC (contained between comma 8 and comma 9)
        dat[0]=rxbuffer[commas[8]+1]; // DD        
        dat[1]=rxbuffer[commas[8]+2];
        dat[2]='/';
        dat[3]=rxbuffer[commas[8]+3]; // MM
        dat[4]=rxbuffer[commas[8]+4];
        dat[5]='/';
        dat[6]=rxbuffer[commas[8]+5]; // YY
        dat[7]=rxbuffer[commas[8]+6];
              
        // now print values on the OLED LCD  
        OLED.setCursor(0,0); // column 0, row 0
        OLED.putString("LAT:");
        OLED.putString(latitude);
        
        OLED.setCursor(0,1); // column 0, row 1
        OLED.putString("LON:");
        OLED.putString(longitude);
        
        OLED.setCursor(0,2); // column 0, row 2
        OLED.putString("UTC:");
        OLED.putString(utc);
        
        OLED.setCursor(4,3); // column 4, row 3
        OLED.putString(dat);
        
        OLED.setCursor(14,3); // column 14, row 3
        if (fixed)
          {
          OLED.putString("OK"); // fixed
          }
        else
          {
          OLED.putString("NO"); // not fixed
          }
        } // end sentence match

       i=0; // reset buffer index
    
       } // end line feed detected
     } // end serial.available
    
    // led scanning     
    ledtimer++; // counter used for delay
    if (ledtimer==led_target)
     {
     leds();
     ledtimer=0;
     }
  } // loop
 
