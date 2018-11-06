/*
 * RODIO_Ai.c
 *
 *  Created on: 31 Oct 2018
 *      Author: Aidan
 *
 *
 *      payload :
 *
 *      0 = payload id (a header to indicate the contents of the payload) == 0xF0 (lidar measurement)
 *      1 = event type (what event has the lidar detected:
 *      												  - ALL CLEAR				= 0x0F
 *      	 											  - On track obstruction 	= 0x01
 *      	 											  - Track left warning 		= 0x02
 *      	 											  - Track right warning 	= 0x03
 *      	 											  - May cross left			= 0x04
 *      	 											  - May cross right			= 0x05
 *      2 = distance MSB
 *      3 = distance LSB
 *      4 = velocity
 *      5 = STOP
 */

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK
#include "RODIO_Ai.h"
enum {
	ALL_CLEAR					= 0x0F,
	OBSTRUCTION_ON_TRACK		= 0x01,
	OBSTRUCTION_TRACK_LEFT		= 0x02,
	OBSTRUCTION_TRACK_RIGHT		= 0x03,
	MAY_CROSS_LEFT				= 0x04,
	MAY_CROSS_RIGHT				= 0x05,
	BLOCKED						= 0x06,
	PAYLOAD_SIZE 				= 6,
	TRACK_LEFT 					= 80,
	TRACK_RIGHT					= 110,
	STOP_BIT					= 0x7E,
};

const uint8_t PAYLOAD_ID = 0xF0;

uint8_t lidar_payload[PAYLOAD_SIZE];
uint8_t previous_payload[PAYLOAD_SIZE];
uint8_t status;

uint8_t velocity;
uint16_t distance;

void RODIO_Analyse(uint16_t distance_input, uint8_t velocity_input);
void onTrackObstruction(void);


void RODIO_Analyse(uint16_t distance_input, uint8_t velocity_input){
	velocity = velocity_input;
	distance = distance_input;

	if(distance >= 30 && distance < 150){
		if(distance > TRACK_LEFT && distance < TRACK_RIGHT){
			onTrackObstruction();
		} else if(distance < TRACK_LEFT/* && (int8_t)velocity < -2*/){
			if((int8_t)velocity < -2){
				offLeftIncoming();
			} else {
				offLeftObstruction();
			}
		} else if(distance > TRACK_RIGHT /*&& (int8_t)velocity > 2*/){
			if((int8_t)velocity > 2){
				offRightIncoming();
			} else {
				offRightObstruction();
			}

		}
	} else if(distance < 30){
		sensorBlocked();
	} else {
		allClear();
	}

}

void onTrackObstruction(void){
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = OBSTRUCTION_ON_TRACK;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();

}

void offLeftObstruction(void){
	emberAfAppPrintln("OBSTRUCTION ON LEFT");
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = OBSTRUCTION_TRACK_LEFT;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void offRightObstruction(void){
	emberAfAppPrintln("OBSTRUCTION ON RIGHT");
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = OBSTRUCTION_TRACK_RIGHT;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void offLeftIncoming(void){
	emberAfAppPrintln("INCOMING FROM LEFT");
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = MAY_CROSS_LEFT;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void offRightIncoming(void){
	emberAfAppPrintln("INCOMING FROM RIGHT");
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = MAY_CROSS_RIGHT;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void allClear(void){
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = ALL_CLEAR;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void sensorBlocked(void){
	lidar_payload[0] = PAYLOAD_ID;
	lidar_payload[1] = BLOCKED;
	lidar_payload[2] = (distance >> 8); //msb
	lidar_payload[3] = distance; // lsb
	lidar_payload[4] = velocity;
	lidar_payload[5] = STOP_BIT;
	dataTransfer();
}

void dataTransfer(void){
//	if(memcmp(lidar_payload, previous_payload, 2)!= 0){
//		emberSendUdp(&server_ip/*server*/, 0, 0, lidar_payload, PAYLOAD_SIZE);
//		memcpy(previous_payload,lidar_payload, PAYLOAD_SIZE);
//	}
	emberSendUdp(&server_ip/*server*/, 0, 0, lidar_payload, PAYLOAD_SIZE);
}

