/*
 * RODIO_Client_Implementation.c
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
#include "VMN\display\images\VortexIoTLogo128x128.c"
#include "VMN\display\images\Connected128x128.c"

enum {
	INITIAL					= 0,
	CONNECTING				= 1,
	CONNECTED				= 2,
	OPERATING				= 3,
};

static uint8_t mode = INITIAL;
static char line_clear[] = "             ";

EmberEventControl userEventData;

static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs);
#define setNextState(nextState)			setNextStateWithDelay((nextState), 0)
#define repeatStateWithDelay(delayMs)	setNextStateWithDelay(mode, (delayMs))

void setMode(void);
void initialiseScreen(void);

void setMode(void){
	setNextState(CONNECTED);
	mode = CONNECTED;
}

void userEventHandler(void)
{
  emberEventControlSetInactive(userEventData);

  	switch(mode) {
  	  case INITIAL:
  		  initialiseScreen();
  		  break;

  	  case CONNECTING:
  		  setConnectingScreen();
  		  break;

  	  case CONNECTED:
  		  //setConnectedScreen();
  		  break;

  	  case OPERATING:
  		  setOperatingScreen();
  		  break;
  	}
}

void initialiseScreen(void){
	emberResetNetworkState();
	mode = INITIAL;
	LCD_graphicDraw(vortexIoTLogo);
	LCD_textDraw("Press any", 10, 50,2);
	LCD_textDraw("button to", 10, 60,2);
	LCD_textDraw("join the", 10, 70,2);
	LCD_textDraw("network", 10, 80,2);
}

void setConnectingScreen(void){
	LCD_graphicDraw(vortexIoTLogo);
	LCD_textDraw("Connecting", 10,50,2);
	emberAfAppPrintln("Connecting screen");
}

void setFailScreen(void){
	LCD_graphicDraw(vortexIoTLogo);
	LCD_textDraw("Connection", 10,50,2);
	LCD_textDraw("Failed", 10,60,2);
//	LCD_textDraw("press button", 10,90,2);
//	LCD_textDraw("to reconnect", 10,100,2);
	setNextStateWithDelay(INITIAL, 2000);
}

void setConnectedScreen(void){
	LCD_graphicDraw(connected);
	setNextStateWithDelay(OPERATING, 2000);
}

void setOperatingScreen(void){
	LCD_graphicDraw(vortexIoTLogo);
	LCD_textDraw("Distance", 3,60,'2');
	LCD_textDraw("Velocity", 3,75,2);
	LCD_textDraw(" Mode || Events",2,120,2);
	i2cEventLoopStart();
}


void halButtonIsr(uint8_t button, uint8_t state) {

	if(mode == INITIAL){
		if (emberNetworkStatus() == EMBER_NO_NETWORK) {
			mode = CONNECTING;
			setNextState(CONNECTING);
			setConnectingScreen();
			joinCommand();
		}

	}
}

static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs)
{
  mode = nextState;
  emberEventControlSetDelayMS(userEventData, delayMs);
}

