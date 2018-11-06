/*
 * ********************************************************************************
 * @file graphics.c
 * @brief this will allow interaction with the display
 * @version 00.07
 * *********************************************************************************
 * @disposition
 *
 * This files allows the user to print custom images and text to the display.
 * The init is called before anything elsse is done, this is hendled in-house.
 *
 * @usage
 *
 * -images if you would like to print an image call;
 *
 * LCD_graphicDraw(myImage);
 *
 *
 * -text if you would like to display custom text call;
 *
 * char * myText = "My text";
 *
 * LCD_textDraw(myText,10,11,1);
 *
 * the format for this is  LCD_textDraw(text string, xpos , ypos , textSize);
 *
 * note textSize will only work for as 1 or 2 for letter how ever number cal also use 3
 *
 * *********************************************************************************
 * @Created by Bryce Davey
 * *********************************************************************************
 * @Modified by.... and when 09/10/2018
 *
 * -Bryce Davey @ 24/10/2018
 *
 */

/* standard headers */
#include <string.h>
#include <stdio.h>

#include "bg_types.h"
#include "em_types.h"
#include "glib.h"
#include "dmd.h"
#include "display.h"

/* Own header */
#include "graphics.h"

/* Error Images */

#include "VMN/display/images/imageWrongSize128x128.c"

/***************************************************************************************************
   Local Variables
 **************************************************************************************************/

/* Global glib context */
static GLIB_Context_t glibContext;


/* this is to hold the size of the passed through image*/
uint8_t imageSize;

/* This holds the init staus for the display */
uint8_t doneInit = 0;

/* *Bryce* holds the last size request */

char oldTextSize;

void graphInit(char *size)
{


  DISPLAY_Init(); //Init the display Lib

  DMD_init(0); //Calls the DMD Lib

  GLIB_contextInit(&glibContext); //Calls the Glib lib

 /* Bryce Davey* This is to detemin the text size */

  if (size == 0){
  	 /* *Bryce* do nuthing for now */

   }else if (size == 1){
  	 GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);

   }else if (size == 2){
  	 GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);

   }else if (size == 3){
  	 GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNumber16x20);
   }
  
  doneInit = 1;

  }

/***************************************************************************//**
 * @brief This will draw the images
 *
 * @detail a string conmtaing the bitmap data will be passed through to display the image
 *
 * @param takes in a string of the bitmap images
 *
 * @return NULL
 *
 *  ******************************************************************************
 *
 */

void LCD_graphicDraw(uint8_t *image)//Void for Printing the image
{

	GLIB_clear(&glibContext); //This clears the display
	/* Bryce Davey* if the init hasnt been dont it will fist call the graphInit function */
	if (doneInit != 1){

		graphInit(0);

		
	}
	



	if (image == 0 ){

		GLIB_clear(&glibContext); //This clears the display


	}

	else{

		GLIB_drawBitmap(&glibContext,0,0,128,128,image); //Sets up the display

		DMD_updateDisplay(); //Updates the display with the new data

	}

}

/***************************************************************************//**
 * @brief this will display the text on the LCD
 *
 * @detail this will take in the text to be displayed with the x and y posstion on the screen, the size of the text is also speceyfide
 *
 * @param
 *
 * -msg is a string (char) and contains the text
 *
 * -posx is the x posstion
 *
 * -posy is the y posstion
 *
 * -textSize is the text size (1,2&3)
 *
 * @return NULL
 *
 *  ******************************************************************************
 *
 */


void LCD_textDraw(char *msg, uint32_t posX, uint32_t posY, char *textSize)//Void for Printing the image
{

	if (doneInit != 1 || textSize != oldTextSize){
		graphInit(textSize);


	}

	if (msg == 0 ){

			GLIB_clear(&glibContext); //This clears the display


		}

		else{

			GLIB_drawString(&glibContext, msg, strlen(msg), posX, posY, true);

			DMD_updateDisplay(); //Updates the display with the new data

		}

	oldTextSize = textSize;



}

