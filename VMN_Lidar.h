/*
 * VMN_I2c.h
 *
 *  Created on: 12 Oct 2018
 *      Author: Aidan
 */

#ifndef VMN_I2C_H_
#define VMN_I2C_H_

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK


#endif /* VMN_I2C_H_ */


uint16_t LIDAR_getDistance(void);
uint8_t LIDAR_getVelocity(void);






const uint8_t check_velocity = 0x09;

// Default address of Garmin LidarLitev3
const uint8_t address = 0xC4;

// sets burst mode to 2x readings on every request.
const uint8_t setup[] = {0x11, 0x02};

// Data and register for 'acquire command' register
const uint8_t control[] = {0x00, 0x04};

// check ready state command
const uint8_t check = 0x01;

//fetch measurement when ready command. Only to be sent once "ready" bit reads 0x24
const uint8_t fetch = 0x8F;


