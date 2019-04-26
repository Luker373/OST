#ifndef DS1
#define DS1

#include <LSM9DS1_func.h>
#include <LSM9DS1.h>
#include <I2C.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function LSM9DS1_Init(Rate)

 * @return 0 if error, 1 if succeeded
 * @brief  Initializes the MPU 9250 for usage. This will set all sensors to approximately 100HZ
 * and Accel: 2g,Gyro:  250dps and Mag: 16-bit for the sensors
 * @author SailTrim Team */
char LSM9DS1_Init(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelX(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelY(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadAccelZ(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroX(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroY(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadGyroZ(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagX(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagY(void);

/**
 * @Function LSM9DS1_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author SailTrim Team*/
int LSM9DS1_ReadMagZ(void);

#endif