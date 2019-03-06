/* 
 * File:   DS1DataCollectionMain.c
 * Author: RARogers
 *
 * Created on March 2, 2019, 4:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "LSM9DS1.h"
#include "LSM9DS1_func.h"
#include "BOARD.h"
#include "AD.h"
#include "I2C.h"
#include "serial.h"
#include "timers.h"


/*
 * 
 */
int main(void) {

    BOARD_Init();
    TIMERS_Init();
    
    LSM9DS1_Init();
    
    //set i2c pins as inputs
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB14 = 1;
    
    int delay = 20;
    
    for(;;){
        
        if(TIMERS_GetMilliSeconds() == delay){
            
            float AXData = LSM9DS1_ReadAccelX()*0.732;
            printf("%f, ", AXData);
        
            float AYData = LSM9DS1_ReadAccelY()*0.732;
            printf("%f, ", AYData);
        
            //float AZData = ((LSM9DS1_ReadAccelZ())-(-17.5))*-0.732;
            float AZData = ((LSM9DS1_ReadAccelZ())*0.732);
            //float AZData = ((LSM9DS1_ReadAccelZ())-(-17.5))*-0.438931357; // scale factor for 9.81
            //if((AZData >= 0.9) && (AZData <= 1.2)){
            //printf("%d, ", AZData);
                printf("%f\r\n", AZData);
            //}
            
            //int MXData = LSM9DS1_ReadMagX();
            //printf("%d, ", MXData);
            
            //int MYData = LSM9DS1_ReadMagY();
            //printf("%d\r\n", MYData);
            //printf("%d\r\n", MYData);
            
            //int MZData = LSM9DS1_ReadMagZ();
            //printf("%d\r\n", MZData);
            
            //int GXData = LSM9DS1_ReadGyroX();
            //printf("%d, ", GXData);
            
            //int GYData = LSM9DS1_ReadGyroY();
            //printf("%d, ", GYData);
            
            //int GZData = LSM9DS1_ReadGyroZ();
            //printf("%d\r\n", GZData);
            //printf("%d\r\n%d\r\n%d\r\n", MagXData,MagYData,MagZData);
            
            delay = delay + 20;
            
            //printf("Fucqboi\r\n");
            
        }
    }
    
}

