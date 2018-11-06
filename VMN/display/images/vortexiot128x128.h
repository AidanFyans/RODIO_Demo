#include <string.h>
#include <stdio.h>

#include "VMN/display/lib/bg_types.h"
#include "VMN/display/lib/em_types.h"



static uint8_t vortexiotQR[2048] = {
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x00, 0xe0, 0xc1, 0x03, 0x00, 0x1e, 0xf8, 0xff, 0xff, 0xff, 0x07,
   0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xe0, 0xc1, 0x03, 0x00, 0x1e, 0xfc,
   0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xe0, 0xc1,
   0x03, 0x00, 0x1e, 0xf8, 0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x00, 0xe0, 0xc1, 0x03, 0x00, 0x1e, 0xfc, 0xff, 0xff, 0xff, 0x07,
   0xe0, 0x93, 0x24, 0x49, 0x3e, 0x00, 0xe0, 0x41, 0x02, 0x00, 0x12, 0x78,
   0x49, 0x92, 0xa4, 0x07, 0xe0, 0x01, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x01,
   0x78, 0xf0, 0x00, 0x7c, 0x00, 0x00, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00,
   0x3c, 0x78, 0xe0, 0x01, 0x78, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x80, 0x07,
   0xe0, 0x03, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x01, 0x78, 0xf0, 0x01, 0x7c,
   0x00, 0x00, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x01,
   0x78, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00,
   0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x80, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x00, 0x00, 0xc0, 0x87, 0x0f, 0x1e, 0x78,
   0xf0, 0xff, 0x83, 0x07, 0xe0, 0x83, 0xff, 0x0f, 0x3c, 0x00, 0x00, 0xc0,
   0x03, 0x0f, 0x1e, 0x7c, 0xf0, 0xff, 0x83, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0x00, 0x00, 0xc0, 0x03, 0x0f, 0x1e, 0x78, 0xf0, 0xff, 0x83, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x00, 0x00, 0xc0, 0x83, 0x0f, 0x1e, 0x7c,
   0xf0, 0xff, 0x81, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0xa8, 0xaa, 0xc0,
   0x97, 0x0f, 0x00, 0x78, 0xf0, 0xff, 0x83, 0x07, 0xe0, 0x83, 0xff, 0x0f,
   0x3c, 0xf8, 0xff, 0xc1, 0xff, 0x0f, 0x00, 0x7c, 0xf0, 0xff, 0x81, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0xf8, 0xff, 0xc1, 0xff, 0x0f, 0x00, 0x78,
   0xf0, 0xff, 0x83, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0xf8, 0xff, 0xc1,
   0xff, 0x0f, 0x00, 0x7c, 0xf0, 0xff, 0x83, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0xd8, 0xdf, 0x81, 0xff, 0x0e, 0x00, 0x78, 0xf0, 0xff, 0x83, 0x07,
   0xe0, 0x83, 0xff, 0x0f, 0x3c, 0x00, 0x0f, 0x00, 0x78, 0x00, 0x00, 0x7c,
   0xf0, 0xff, 0x81, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x00, 0x0f, 0x00,
   0x78, 0x00, 0x00, 0x78, 0xf0, 0xff, 0x83, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0x00, 0x0f, 0x00, 0x78, 0x00, 0x00, 0x7c, 0xf0, 0xff, 0x81, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x00, 0x0f, 0x00, 0x78, 0x00, 0x00, 0x78,
   0xf0, 0xff, 0x83, 0x07, 0xe0, 0x03, 0x42, 0x08, 0x3c, 0x00, 0x0f, 0x00,
   0x78, 0x00, 0x00, 0x7c, 0x80, 0x80, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00,
   0x3c, 0xf8, 0x0f, 0xfe, 0xff, 0xff, 0x00, 0x78, 0x00, 0x00, 0x80, 0x07,
   0xe0, 0x01, 0x00, 0x00, 0x3c, 0xf8, 0x0f, 0xfe, 0xff, 0xff, 0x01, 0x7c,
   0x00, 0x00, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00, 0x3c, 0xf8, 0x0f, 0xfe,
   0xff, 0xff, 0x00, 0x78, 0x00, 0x00, 0x80, 0x07, 0xe0, 0x03, 0x00, 0x00,
   0x3c, 0xf8, 0x0f, 0xfe, 0xff, 0xff, 0x01, 0x7c, 0x00, 0x00, 0x80, 0x07,
   0xe0, 0x03, 0x00, 0x00, 0x3e, 0xf8, 0x00, 0xc0, 0x03, 0x0f, 0x00, 0x78,
   0x00, 0x00, 0x80, 0x07, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xf0, 0xc1,
   0x83, 0x0f, 0x1e, 0xfc, 0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x78, 0xe0, 0xc1, 0x03, 0x0f, 0x1e, 0xf8, 0xff, 0xff, 0xff, 0x07,
   0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xe0, 0xc1, 0x03, 0x0f, 0x1e, 0xfc,
   0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xe0, 0xc1,
   0x03, 0x0f, 0x1e, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf5, 0x15, 0x80, 0x5f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x1f, 0x00, 0xff, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3f,
   0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xff, 0x1f, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x3f, 0x80, 0xff, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x0f, 0xfc, 0xff, 0x0f, 0x1e,
   0xf8, 0xff, 0xff, 0x83, 0x07, 0x1e, 0x3c, 0x00, 0xe0, 0xff, 0xff, 0x0f,
   0xfc, 0xff, 0x0f, 0x3e, 0xf8, 0xff, 0xff, 0x83, 0x07, 0x1e, 0x3c, 0x00,
   0xe0, 0xff, 0xff, 0x0f, 0xfc, 0xff, 0x0f, 0x1c, 0xf8, 0xff, 0xff, 0x83,
   0x07, 0x1e, 0x3c, 0x00, 0xe0, 0xff, 0xff, 0x0f, 0xfc, 0xff, 0x0f, 0x3e,
   0xf8, 0xff, 0xff, 0x83, 0x07, 0x1e, 0x3c, 0x00, 0xe0, 0x03, 0x00, 0x04,
   0xc0, 0x07, 0x00, 0x00, 0xf8, 0x00, 0xfe, 0x83, 0x07, 0x00, 0x3c, 0x00,
   0xe0, 0x01, 0x00, 0x00, 0x80, 0x07, 0xf0, 0xc1, 0x7f, 0x00, 0xfe, 0x83,
   0x07, 0x00, 0x3c, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x80, 0x07, 0xe0, 0xc1,
   0x7f, 0x00, 0xfe, 0x83, 0x07, 0x00, 0x3c, 0x00, 0xe0, 0x01, 0x00, 0x00,
   0xc0, 0x03, 0xe0, 0xc1, 0x7f, 0x00, 0xfe, 0x83, 0x07, 0x00, 0x3c, 0x00,
   0xe0, 0x01, 0x00, 0x00, 0x80, 0x07, 0xe0, 0xc1, 0x7f, 0x00, 0xfe, 0x83,
   0x07, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xe0, 0x01,
   0x00, 0x00, 0x1f, 0x80, 0x0f, 0x00, 0x7c, 0x00, 0x00, 0x3c, 0xf8, 0x00,
   0x3c, 0x78, 0xe0, 0x01, 0x80, 0xff, 0x1f, 0xfc, 0xff, 0x1f, 0xfc, 0x07,
   0x00, 0x3c, 0xf0, 0x00, 0x3c, 0x78, 0xe0, 0x01, 0x00, 0xff, 0x1f, 0xf8,
   0xff, 0x1f, 0xfc, 0x07, 0x00, 0x3c, 0xf0, 0x00, 0x3c, 0x78, 0xe0, 0x01,
   0x00, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xfc, 0x07, 0x00, 0x3c, 0x78, 0x00,
   0x3c, 0x78, 0xe0, 0x01, 0x80, 0xff, 0x1f, 0xfc, 0xff, 0x1f, 0xfc, 0x07,
   0x00, 0x80, 0x05, 0xdb, 0x81, 0x7e, 0x00, 0x40, 0x03, 0x0f, 0x1e, 0x80,
   0xff, 0x00, 0x80, 0x07, 0x00, 0x80, 0x07, 0xff, 0xc1, 0x7f, 0x00, 0xc0,
   0x03, 0x0f, 0x1e, 0x80, 0xff, 0x00, 0x80, 0x07, 0x00, 0x80, 0x07, 0xff,
   0x81, 0x7f, 0x00, 0xc0, 0x03, 0x0f, 0x1e, 0x80, 0xff, 0x00, 0x80, 0x07,
   0x00, 0x80, 0x07, 0xff, 0xc1, 0x7f, 0x00, 0xc0, 0x83, 0x0f, 0x1e, 0x80,
   0xff, 0x00, 0x80, 0x07, 0x00, 0x80, 0x07, 0xff, 0x81, 0x57, 0x00, 0xc0,
   0x03, 0x05, 0x14, 0x80, 0xfa, 0x00, 0x80, 0x07, 0xe0, 0x81, 0x07, 0xff,
   0xff, 0x03, 0xff, 0xc1, 0x7f, 0x00, 0xc0, 0x7f, 0xf0, 0xc0, 0xff, 0x07,
   0xe0, 0x81, 0x07, 0xff, 0xff, 0x07, 0xff, 0xc1, 0x7f, 0x00, 0xc0, 0x7f,
   0xf0, 0xc0, 0xff, 0x07, 0xe0, 0x83, 0x07, 0xff, 0xff, 0x03, 0xff, 0xc1,
   0x7f, 0x00, 0xc0, 0x7f, 0xf0, 0xe0, 0xff, 0x07, 0xe0, 0x81, 0x07, 0xff,
   0xff, 0x07, 0xff, 0xc1, 0x7f, 0x00, 0xc0, 0x7f, 0xf0, 0xc0, 0xff, 0x07,
   0xe0, 0x01, 0x00, 0xff, 0x01, 0x00, 0x0f, 0x00, 0x7c, 0x00, 0xe0, 0x03,
   0x00, 0x40, 0x7c, 0x00, 0xe0, 0x01, 0x00, 0xff, 0x03, 0xf8, 0x0f, 0x00,
   0x78, 0x00, 0xfe, 0x83, 0x0f, 0x1e, 0x3c, 0x00, 0xe0, 0x03, 0x00, 0xff,
   0x01, 0xf8, 0x0f, 0x00, 0x78, 0x00, 0xfe, 0x83, 0x07, 0x1f, 0x3c, 0x00,
   0xe0, 0x01, 0x00, 0xff, 0x01, 0xf8, 0x0f, 0x00, 0x78, 0x00, 0xfe, 0x83,
   0x07, 0x1e, 0x3c, 0x00, 0xe0, 0x01, 0x00, 0xff, 0x01, 0xf8, 0x0f, 0x00,
   0x78, 0x00, 0xfe, 0x83, 0x0f, 0x1e, 0x3c, 0x00, 0xe0, 0x01, 0x00, 0xe0,
   0x4b, 0x02, 0x5f, 0x92, 0xfc, 0x92, 0xfe, 0x27, 0x40, 0x1f, 0x7c, 0x02,
   0xe0, 0x03, 0x00, 0xe0, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
   0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x01, 0x00, 0xe0, 0xff, 0x03, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x7f, 0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x01, 0x00, 0xe0,
   0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xf0, 0x1f, 0xfc, 0x07,
   0xe0, 0x01, 0x00, 0xe0, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
   0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x03, 0x00, 0xff, 0x01, 0x00, 0x00, 0x1e,
   0x00, 0xff, 0x00, 0xf8, 0x07, 0x1e, 0x80, 0x07, 0xe0, 0x01, 0x00, 0xff,
   0x01, 0x00, 0x00, 0x3e, 0x00, 0xff, 0x00, 0xf8, 0x07, 0x1e, 0x80, 0x07,
   0xe0, 0x01, 0x00, 0xff, 0x01, 0x00, 0x00, 0x1e, 0x80, 0xff, 0x01, 0xfc,
   0x07, 0x1e, 0x80, 0x07, 0xe0, 0x01, 0x00, 0xff, 0x01, 0x00, 0x00, 0x1c,
   0x00, 0xff, 0x00, 0xf8, 0x07, 0x1e, 0x80, 0x07, 0xe0, 0x03, 0x00, 0xea,
   0x01, 0x00, 0x00, 0x3e, 0x00, 0x55, 0x01, 0xfc, 0x0f, 0x0a, 0x80, 0x02,
   0xe0, 0x81, 0xff, 0xe0, 0xff, 0x07, 0xe0, 0x1f, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0xe0, 0x03, 0x00, 0xe0, 0x81, 0xff, 0xe0, 0xff, 0x03, 0xe0, 0x3f,
   0x00, 0x00, 0xfe, 0xff, 0xff, 0xc0, 0x01, 0x00, 0xe0, 0x81, 0xff, 0xe0,
   0xff, 0x07, 0xe0, 0x1f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xc0, 0x03, 0x00,
   0xe0, 0x83, 0x7f, 0xe0, 0xff, 0x03, 0xe0, 0x3f, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0x01,
   0x00, 0x00, 0x3e, 0x00, 0xf0, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xc1, 0x7f, 0xf0, 0x1f, 0x00, 0xf0, 0xff, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc1, 0x7f, 0xf0, 0x1f, 0x00,
   0xf0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc1,
   0x7f, 0xf0, 0x1f, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xc1, 0x7f, 0xf0, 0x1f, 0x00, 0xf0, 0xff, 0x03, 0x00,
   0x40, 0x55, 0x55, 0x55, 0x15, 0x78, 0x00, 0x00, 0xf8, 0x0a, 0x1e, 0x28,
   0xf0, 0xff, 0xab, 0x02, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0x00, 0x00,
   0xf8, 0x0f, 0x1e, 0x78, 0xf0, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x78, 0x00, 0x00, 0xf8, 0x0f, 0x1e, 0x7c, 0xf0, 0xff, 0xff, 0x07,
   0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0x00, 0x00, 0xf8, 0x0f, 0x1e, 0x78,
   0xf0, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0x00, 0x00,
   0xf8, 0x0f, 0x1e, 0x7c, 0xf0, 0xff, 0xff, 0x07, 0xe0, 0x01, 0x00, 0x00,
   0x3c, 0x00, 0xff, 0xc1, 0x7f, 0x00, 0x1e, 0x00, 0xf0, 0x1f, 0xfc, 0x07,
   0xe0, 0x01, 0x00, 0x00, 0x3c, 0x00, 0xff, 0xc1, 0x7f, 0x00, 0x1e, 0x00,
   0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x01, 0x00, 0x00, 0x3c, 0x00, 0xff, 0xc1,
   0x7f, 0x00, 0x1e, 0x00, 0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x03, 0x00, 0x00,
   0x3c, 0x00, 0xff, 0xc1, 0x7f, 0x00, 0x1e, 0x00, 0xf0, 0x1f, 0xfc, 0x07,
   0xe0, 0x01, 0x00, 0x00, 0x3c, 0x00, 0xf2, 0xc1, 0x27, 0x00, 0x1e, 0x00,
   0xf0, 0x1f, 0xfc, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0xe0, 0xc1,
   0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0x78, 0xe0, 0xc1, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07,
   0xe0, 0x83, 0xff, 0x0f, 0x3c, 0x78, 0xe0, 0xc1, 0x03, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0xe0, 0xc1,
   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0x78, 0x00, 0x00, 0x00, 0xf0, 0xc1, 0xff, 0xff, 0xe0, 0xff, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0x00, 0x00, 0xf0, 0xc0, 0xff,
   0xff, 0xc0, 0xff, 0x07, 0xe0, 0x83, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0x00,
   0x00, 0xf0, 0xc1, 0xff, 0xff, 0xe0, 0xff, 0x07, 0xe0, 0x81, 0xff, 0x0f,
   0x3c, 0x78, 0x00, 0x00, 0x00, 0xf0, 0xc0, 0xff, 0xff, 0xc0, 0xff, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0x00, 0x00, 0xf0, 0xc1, 0xff,
   0xff, 0xe0, 0xff, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0xa8,
   0x02, 0xf0, 0x15, 0x80, 0x07, 0xc0, 0x83, 0x07, 0xe0, 0x83, 0xff, 0x0f,
   0x3c, 0x78, 0x00, 0xfe, 0x03, 0xf0, 0x1f, 0x80, 0x07, 0xe0, 0x81, 0x07,
   0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0xfe, 0x03, 0xf0, 0x1f, 0x80,
   0x07, 0xc0, 0x83, 0x07, 0xe0, 0x81, 0xff, 0x0f, 0x3c, 0x78, 0x00, 0xfe,
   0x03, 0xf0, 0x1f, 0x80, 0x07, 0xe0, 0x83, 0x07, 0xe0, 0x01, 0xdb, 0x0e,
   0x3c, 0x78, 0x00, 0x7c, 0x03, 0x60, 0x1f, 0x80, 0x07, 0x40, 0x81, 0x07,
   0xe0, 0x03, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x1f, 0x00, 0x0f, 0xfe, 0xff,
   0xff, 0x1f, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x1f,
   0x00, 0x0f, 0xfe, 0xff, 0xff, 0x1f, 0x80, 0x07, 0xe0, 0x01, 0x00, 0x00,
   0x3c, 0x78, 0xe0, 0x3f, 0x80, 0x0f, 0xfe, 0xff, 0xff, 0x1f, 0x80, 0x07,
   0xe0, 0x01, 0x00, 0x00, 0x3c, 0x78, 0xe0, 0x1f, 0x00, 0x0f, 0xfe, 0xff,
   0xff, 0x1f, 0x80, 0x07, 0xe0, 0x03, 0x00, 0x00, 0x3e, 0x78, 0xe0, 0x3f,
   0x00, 0x00, 0xe0, 0xff, 0xff, 0x1f, 0x80, 0x07, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x78, 0xe0, 0x1f, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07,
   0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xe0, 0x3f, 0x00, 0x00, 0xc0, 0xff,
   0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xe0, 0x1f,
   0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff,
   0x3f, 0x78, 0xe0, 0x3f, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
