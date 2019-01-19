/*
  This program  reads the angles and heading from the accelerometer, gyroscope
   and compass on a BerryIMU connected to an Arduino.
  

    Both the BerryIMUv1 and BerryIMUv2 are supported.
    Feel free to do whatever you like with this code
    Distributed as-is; no warranty is given.
    http://ozzmaker.com/
*/

#include <Wire.h>
#include "LSM9DS0.h"
#include "LSM9DS1.h"

#define DT  0.02          // Loop time
#define AA  0.97         // complementary filter constant
#define G_GAIN 0.070    // [deg/s/LSB]


byte buff[6];
int accRaw[3];
int magRaw[3];
int gyrRaw[3];
float rate_gyr_y = 0.0;   // [deg/s]
float rate_gyr_x = 0.0;    // [deg/s]
float rate_gyr_z = 0.0;     // [deg/s]
float gyroXangle = 0.0;
float gyroYangle = 0.0;
float gyroZangle = 0.0;
float AccYangle = 0.0;
float AccXangle = 0.0;
float CFangleX = 0.0;
float CFangleY = 0.0;
int LSM9DS0 = 0;
int LSM9DS1 = 0;

typedef unsigned char byte;

unsigned long startTime;


void setup() {
         // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for outputF
  detectIMU();
  enableIMU();

}

void loop() {
 startTime = millis();
  //Read the measurements from  sensors
  readACC(buff);
  accRaw[0] = (int)(buff[0] | (buff[1] << 8));   
  accRaw[1] = (int)(buff[2] | (buff[3] << 8));
  accRaw[2] = (int)(buff[4] | (buff[5] << 8));

  readMAG(buff);
  magRaw[0] = (int)(buff[0] | (buff[1] << 8));   
  magRaw[1] = (int)(buff[2] | (buff[3] << 8));
  magRaw[2] = (int)(buff[4] | (buff[5] << 8));


  readGYR(buff);
  gyrRaw[0] = (int)(buff[0] | (buff[1] << 8));   
  gyrRaw[1] = (int)(buff[2] | (buff[3] << 8));
  gyrRaw[2] = (int)(buff[4] | (buff[5] << 8));

  
  //Convert Gyro raw to degrees per second
  rate_gyr_x = (float) gyrRaw[0] * G_GAIN;
  rate_gyr_y = (float) gyrRaw[1]  * G_GAIN;
  rate_gyr_z = (float) gyrRaw[2]  * G_GAIN;

  //Calculate the angles from the gyro
  gyroXangle+=rate_gyr_x*DT;
  gyroYangle+=rate_gyr_y*DT;
  gyroZangle+=rate_gyr_z*DT;

  //Convert Accelerometer values to degrees
  AccXangle = (float) (atan2(accRaw[1],accRaw[2])+M_PI)*RAD_TO_DEG;
  AccYangle = (float) (atan2(accRaw[2],accRaw[0])+M_PI)*RAD_TO_DEG;


  //If IMU is up the correct way, use these lines
  AccXangle -= (float)180.0;
  if (AccYangle > 90)
          AccYangle -= (float)270;
  else
    AccYangle += (float)90;


  //Complementary filter used to combine the accelerometer and gyro values.
  CFangleX=AA*(CFangleX+rate_gyr_x*DT) +(1 - AA) * AccXangle;
  CFangleY=AA*(CFangleY+rate_gyr_y*DT) +(1 - AA) * AccYangle;


  //Compute heading  
  float heading = 180 * atan2(magRaw[1],magRaw[0])/M_PI;
  
  //Convert heading to 0 - 360
          if(heading < 0)
            heading += 360;
            
  Serial.print("#AccX\t");
  Serial.print(AccXangle);
  Serial.print("\t###  AccY  ");
  Serial.print(AccYangle);
  
  Serial.print("  ###  GyrX\t");
  Serial.print(gyroXangle);
  Serial.print("  ###  GyrY  \t");
  Serial.print(gyroYangle);
  Serial.print("   ###  GyrZ\t");
  Serial.print(gyroZangle);
  Serial.print("     ######    CFangleX\t");
  Serial.print(CFangleX);
  Serial.print("   ######  CFangleY   \t");
  Serial.print(CFangleY);
  Serial.print("   ######  heading   \t");
  Serial.print(heading); 
  Serial.print("    --Loop Time--\t");

  //Each loop should be at least 20ms.
  while(millis() - startTime < (DT*1000)){
    delay(1);
  }
  Serial.println( millis()- startTime);
 


}


void writeTo(int device, byte address, byte val) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   Wire.write(val);        // send value to write
   Wire.endTransmission(); //end transmission
}
void readFrom(int device, byte address, int num, byte buff[]) {
  Wire.beginTransmission(device); //start transmission to device 
  Wire.write(address);        //sends address to read from
  Wire.endTransmission(); //end transmission
  Wire.beginTransmission(device); //start transmission to device (initiate again)
  Wire.requestFrom(device, num);    // request 6 bytes from device
  
  int i = 0;
  while(Wire.available())    //device may send less than requested (abnormal)
  { 
    buff[i] = Wire.read(); // receive a byte
    i++;
  }
  Wire.endTransmission(); //end transmission
}

void detectIMU(){
  Wire.begin(); 
  byte LSM9DS0_WHO_AM_I_G_response;
  byte LSM9DS0_WHO_AM_I_XM_response;
  byte LSM9DS1_WHO_M_response;
  byte LSM9DS1_WHO_XG_response;
  
  byte WHOresponse[2];
  Serial.println("1");
  //Detect if BerryIMUv1 (Which uses a LSM9DS0) is connected
  readFrom(LSM9DS0_GYR_ADDRESS, LSM9DS0_WHO_AM_I_G,1,WHOresponse);
  LSM9DS0_WHO_AM_I_G_response = WHOresponse[0];
  Serial.println("1.5");
  readFrom(LSM9DS1_ACC_ADDRESS, LSM9DS0_WHO_AM_I_XM,1,WHOresponse);
  LSM9DS0_WHO_AM_I_XM_response = WHOresponse[0];
  Serial.println("1.7");
  if (LSM9DS0_WHO_AM_I_G_response == 0xD4 && LSM9DS0_WHO_AM_I_XM_response == 0x49){
    LSM9DS0 = 1;
  }

  Serial.println("2");
  //Detect if BerryIMUv2 (Which uses a LSM9DS1) is connected
  readFrom(LSM9DS1_MAG_ADDRESS, LSM9DS1_WHO_AM_I_M,1,WHOresponse);
  LSM9DS1_WHO_M_response = WHOresponse[0];
  
  readFrom(LSM9DS1_GYR_ADDRESS, LSM9DS1_WHO_AM_I_XG,1,WHOresponse);
  LSM9DS1_WHO_XG_response = WHOresponse[0];

  if (LSM9DS1_WHO_XG_response == 0x68 && LSM9DS1_WHO_M_response == 0x3D){
    LSM9DS1 = 1;
  }
  Serial.println("3");
    
  delay(1000);
  
  
  
  


  }


void enableIMU(){

 // if(LSM9DS1){//For BerryIMUv2  
        // Enable the gyroscope
      writeTo(LSM9DS1_GYR_ADDRESS,LSM9DS1_CTRL_REG4,0b00111000);      // z, y, x axis enabled for gyro
      writeTo(LSM9DS1_GYR_ADDRESS,LSM9DS1_CTRL_REG1_G,0b10111000);    // Gyro ODR = 476Hz, 2000 dps
      writeTo(LSM9DS1_GYR_ADDRESS,LSM9DS1_ORIENT_CFG_G,0b10111000);   // Swap orientation 
  
      // Enable the accelerometer
      writeTo(LSM9DS1_ACC_ADDRESS,LSM9DS1_CTRL_REG5_XL,0b00111000);   // z, y, x axis enabled for accelerometer
      writeTo(LSM9DS1_ACC_ADDRESS,LSM9DS1_CTRL_REG6_XL,0b00101000);   // +/- 16g
  
      //Enable the magnetometer
      writeTo(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG1_M, 0b10011100);   // Temp compensation enabled,Low power mode mode,80Hz ODR
      writeTo(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG2_M, 0b01000000);   // +/-12gauss
      writeTo(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG3_M, 0b00000000);   // continuos update
      writeTo(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG4_M, 0b00000000);   // lower power mode for Z axis   
//  }else{
//    Serial.println("ENABLE FAILED");
//  }
}

void readACC(byte buff[]){ 
   readFrom(LSM9DS1_ACC_ADDRESS, 0x80 | LSM9DS1_OUT_X_L_XL, 6, buff);
} 
 
void readMAG(byte buff[]){
   readFrom(LSM9DS1_MAG_ADDRESS, 0x80 | LSM9DS1_OUT_X_L_M, 6, buff);
}

void readGYR(byte buff[]){
  readFrom(LSM9DS1_GYR_ADDRESS, 0x80 | LSM9DS1_OUT_X_L_G, 6, buff);
}

