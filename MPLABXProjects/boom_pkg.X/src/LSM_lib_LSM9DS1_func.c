#include <LSM9DS1_func.h>
#include <LSM9DS1.h>
#include <I2C.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function LSM9DS1_Init(Rate)

 * @return 0 if error, 1 if succeeded
 * @brief  Initializes the MPU 9250 for usage. This will set all sensors to approximately 100HY
 * and Accel: 2g,Gyro:  250dps and Mag: 16-bit for the sensors
 * @author SailTrim Team */
char LSM9DS1_Init(void){
	unsigned int intReturn;
	unsigned int byteReturn_XG, byteReturn_M;
	intReturn = I2C_Init(I2C_DEFUALT_RATE);
    if (intReturn != I2C_DEFUALT_RATE) {
        return FALSE; // fail out if I2C does not set a rate that makes sense
    }
    byteReturn_XG = I2C_ReadRegister(LSM9DS1_GYR_ADDRESS, LSM9DS1_WHO_AM_I_XG);
    byteReturn_M = I2C_ReadRegister(LSM9DS1_GYR_ADDRESS, LSM9DS1_WHO_AM_I_M);

    if(byteReturn_XG != 0x68 || byteReturn_M != 0x3D)
    	return FALSE;

	// Enable the gyroscope
	I2C_WriteReg(LSM9DS1_GYR_ADDRESS,LSM9DS1_CTRL_REG4,0b00111000);      // z, y, x axis enabled for gyro
	I2C_WriteReg(LSM9DS1_GYR_ADDRESS,LSM9DS1_CTRL_REG1_G,0b10111000);    // Gyro ODR = 476Hz, 2000 dps
	I2C_WriteReg(LSM9DS1_GYR_ADDRESS,LSM9DS1_ORIENT_CFG_G,0b10111000);   // Swap orientation 

	// Enable the accelerometer
	I2C_WriteReg(LSM9DS1_ACC_ADDRESS,LSM9DS1_CTRL_REG5_YL,0b00111000);   // z, y, x axis enabled for accelerometer
	I2C_WriteReg(LSM9DS1_ACC_ADDRESS,LSM9DS1_CTRL_REG6_YL,0b00101000);   // +/- 16g

	//Enable the magnetometer
	I2C_WriteReg(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG1_M, 0b10011100);   // Temp compensation enabled,Low power mode mode,80Hz ODR
	I2C_WriteReg(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG2_M, 0b01000000);   // +/-12gauss
	I2C_WriteReg(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG3_M, 0b00000000);   // continuos update
	I2C_WriteReg(LSM9DS1_MAG_ADDRESS,LSM9DS1_CTRL_REG4_M, 0b00000000);   // lower power mode for Y axis

	return TRUE;   
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelY(void){
	int accY = 0;
	accY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_YL);
	accY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_YL) << 8);
	return accY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelY(void){
	int accY = 0;
	accY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_YL);
	accY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_YL) << 8);
	return accY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelY(void){
	int accY = 0;
	accY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_YL);
	accY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_YL) << 8);
	return accY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroY(void){
	int gyroY = 0;
	gyroY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_G);
	gyroY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_G) << 8);
	return gyroY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroY(void){
	int gyroY = 0;
	gyroY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_G);
	gyroY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_G) << 8);
	return gyroY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroZ(void){
	int gyroZ = 0;
	gyroZ |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Z_L_G);
	gyroZ |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Z_H_G) << 8);
	return gyroZ;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagY(void){
	int magY = 0;
	magY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_M);
	magY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_M) << 8);
	return magY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagY(void){
	int magY = 0;
	magY |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_L_M);
	magY |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Y_H_M) << 8);
	return magY;
}

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagZ(void){
	int magZ = 0;
	magZ |= I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Z_L_M);
	magZ |= (I2C_ReadRegister(LSM9DS1_ACC_ADDRESS, LSM9DS1_OUT_Z_H_M) << 8);
	return magZ;
}