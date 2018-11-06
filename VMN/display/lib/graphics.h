/*
 * ********************************************************************************
 * @file graphics.h
 * @brief This is the header file for the graphics.c
 * @version 00.07
 * *********************************************************************************
 * @disposition this header file stores the required functions for the user.
 * *********************************************************************************
 *
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif


/* Bryce Davey* this Init the graphics dependanceys */
void graphInit(char *size);

/* Bryce Davey* this will dware a spesyfid image */
void LCD_graphicDraw(uint8_t *image);

/* Bryce Davey* This will display the custom text */
void LCD_textDraw(char *msg, uint32_t posX, uint32_t posY, char *textSize);

#ifdef __cplusplus
}
#endif

#endif /* GRAHPHICS_H */
