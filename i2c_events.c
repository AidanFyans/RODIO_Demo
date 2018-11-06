/*
 * i2c_events.c
 *
 *  Created on: 30 Oct 2018
 *      Author: Aidan
 */


#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK
#include EMBER_AF_API_HAL
#include EMBER_AF_API_COMMAND_INTERPRETER2
#ifdef EMBER_AF_API_DEBUG_PRINT
  #include EMBER_AF_API_DEBUG_PRINT
#endif



enum {
	INITIAL					= 0,
	REQUEST_MEASUREMENT		= 1,
	CHECK_READY				= 2,
	FETCH_MEASUREMENT		= 3,
	ANALYSE					= 4,
};

static uint8_t i2cState = INITIAL;

int8_t current_velocity;
int8_t previous_velocity;
uint16_t current_distance;
uint16_t previous_distance;

EmberEventControl i2cEventControl;
static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs);
#define setNextState(nextState)			setNextStateWithDelay((nextState), 0)
#define repeatState()					setNextStateWithDelay(i2cState, 0)
#define repeatStateWithDelay(delayMs)	setNextStateWithDelay(i2cState, (delayMs))

void i2cEventLoopStart(void);
void displayData(void);
void dataBackup(void);



void i2cEventHandler(void){
	emberEventControlSetInactive(i2cEventControl);

	switch(i2cState) {
	  case INITIAL:
		setNextState(REQUEST_MEASUREMENT);
		break;

	  case REQUEST_MEASUREMENT:
		lidarInitialize();
	  	requestMeasurement();
	  	setNextState(CHECK_READY);
		break;

	  case CHECK_READY:
		if(checkReady()%2 == 0){
			setNextState(FETCH_MEASUREMENT);
		} else {
			repeatStateWithDelay(10);
		}
	  	break;

	  case FETCH_MEASUREMENT:
		dataBackup();
		current_distance = readMeasurement();
	  	current_velocity = readVelocity();
	  	setNextState(ANALYSE);
	  	break;

	  case ANALYSE:
		  RODIO_Analyse(current_distance, current_velocity);
		  /* build AI data analysis class
		   *
		   * - detect movement on or off track
		   * - use velocity to detect objects moving towards or away from the tracks.
		   * - predict position of moving objects onto tracks.
		   *
		  */
//		  if(abs(current_distance - previous_distance) > 10){
//			  emberAfAppPrintln("LIDAR EVENT TRIGGER");
//			  emberAfAppPrintln("Distance = %4d", (long)current_distance);
//			  displayData();
//		  }
		  displayData();
		  setNextStateWithDelay(INITIAL,100);
	}
}


void i2cEventLoopStart(void){
	setNextState(INITIAL);
}

void dataBackup(void){
	previous_velocity = current_velocity;
	previous_distance = current_distance;
}

void displayData(void){
	char char_data[6];
	LCD_textDraw("      ",80,60,2);
	LCD_textDraw("      ",80,75,2);
	LCD_textDraw(itoa(current_distance, char_data,10),80,60,2);
	LCD_textDraw(itoa(current_velocity, char_data,10),80,75,2);
}

static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs)
{
  i2cState = nextState;
  emberEventControlSetDelayMS(i2cEventControl, delayMs);
}
