/*
 * VMN_Lidar.c
 *
 *  Created on: 12 Oct 2018
 *      Author: Aidan
 *
 *      - When a measurement is requested from the lidar, the lidar takes multiple
 *        readings until a peak is found in its readings.
 *
 *      - Once a peak is found the LSB of the ready register reading will go low.
 *
 *      - measurements can be extracted without the ready bit going low but will have a reduced accuracy.
 *
 *      - velocity is a measurement of the difference between the last two measurement readings. (I.E multiple
 *        readings must be taken for velocity readings to be possible.)
 *
 */

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK

#include <VMN_Lidar.h>
#include "C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.4\hardware\kit\common\drivers\i2cspm.h"

static boolean i2c_init;
int measurement_count;

// Placeholder for incoming velocity data
uint8_t velocity;

// Lidar ready bit placeholder
uint8_t ready = 0x01;

// placeholder for incoming measurement data
uint8_t data[2];

void requestMeasurement(void);
uint8_t checkReady(void);
uint16_t readMeasurement(void);
uint8_t readVelocity(void);


// initialises hardware I2C and sends setup data to the lidar;
void lidarInitialize(void){
		if(!i2c_init){
		halI2cInitialize();
		//setup data to enable double burst readings
		halI2cWriteBytes(address, &setup,2);
		i2c_init = true;
	}
}

/**Aidan*
 *
 * - fetches velocity data from lidar in signed 8 bit integer.
 * - Data is stored and transfered as unsigned 8 bit integer until final decoding for ease of communication.
 * - A measurement request is made as p[art of the velocity request so that the velocity can be read at any time standalone.
 *
 */
uint8_t LIDAR_getVelocity(void){
	lidarInitialize();
	requestMeasurement();
	readVelocity();
	return velocity;
}

/**Aidan*
 *
 * reads velocity data from lidar
 *
 */
uint8_t readVelocity(void){
	halI2cWriteBytes(address, &check_velocity, 1);
	halI2cReadBytes(address, &velocity, 1);
	return velocity;
}

/**Aidan*
 *
 * Gets distance measurement from lidar,
 *
 * - Initialises lidar if required
 * - Writes to the take measurement bus
 * - Checks the status register for the ready state (check takes place, nothing implemented with data currently)
 * - Fetches measurement from data bus as pair of 8 bit integers (MSB and LSB)
 * - Clears the ready status
 * - Returns a 16bit unsigned value from the 8 bit LSB and MSB received from the lidar
 *
 */
uint16_t LIDAR_getDistance(void){

	lidarInitialize();
	requestMeasurement();
	checkReady();
	readMeasurement();
	ready = 0x01;
	return data[0]<<8 | data[1];

}

/**Aidan*
 *
 * Tells the Lidar to take a measurement
 *
 */
void requestMeasurement(void){
	halI2cWriteBytes(address, &control, 2);
	//halCommonDelayMicroseconds(2600);
}


/**Aidan*
 *
 * Checks the ready bit of the staus register. When the LSB goes low, the measurement is ready.
 *
 */
uint8_t checkReady(void){
	halI2cWriteBytes(address, &check,1);
	halI2cReadBytes(address, &ready,1);
}

/*Aidan*
 *
 * Reads measurement data from lidar
 *
 */

uint16_t readMeasurement(){
	halI2cWriteBytes(address, &fetch, 1);
	halI2cReadBytes(address, &data, 2);
	return data[0]<<8 | data[1];
}

/*Aidan*
 *
 * Currently Unused
 *
 */
//static void waitState(){
//	halI2cWriteBytes(address, &check, 1);
//	halI2cReadBytes(address, &ready, 1);
//	checkState();
//}
