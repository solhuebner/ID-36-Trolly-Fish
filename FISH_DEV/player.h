#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>


extern Arduboy arduboy;
extern Sprites sprites;
extern SimpleButtons buttons;

extern byte getPowerup(byte);
extern byte pu_timers[];

#define PUT_STOP    0
#define PUT_PROTECT 1
#define PUT_SHOCK   2
#define PUT_MAGNET  3

#define PU_SHOOTFISH    0
#define PU_TURNFISH     1
#define PU_POPFISH      2
#define PU_STOPFISH     3
//#define PU_SHOOTFISH    4
#define PU_PROTECTFISH  4
#define PU_LIFEFISH     5
#define PU_SHOCKFISH    6
#define PU_MAGNETFISH   7

#define SHOCK_LENGTH    8

int8_t shock_burst = 0;

byte trollyFrame = 0;

PROGMEM const unsigned char Trolly_plus_mask[] = {
// width, height
16, 16,
// frame 0
0xF0, 0xF8, 0xC0, 0xF0, 0x80, 0xE0, 0xC0, 0xE1, 0x61, 0xFF, 0x77, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 
0x9A, 0xFF, 0x28, 0xFE, 0x08, 0xFC, 0x90, 0xF8, 0xE0, 0xF0, 0xC0, 0xE0, 0x00, 0xE0, 0xC0, 0xE0, 
0x0F, 0x1F, 0x03, 0x0F, 0x01, 0xC3, 0x43, 0xFF, 0x74, 0xFF, 0x6B, 0xFF, 0x6A, 0xFF, 0x5F, 0xFF, 
0x1F, 0x7F, 0x1B, 0x3F, 0x15, 0x3F, 0x15, 0x3F, 0x0D, 0x1F, 0x0E, 0x1F, 0x0B, 0x1F, 0x01, 0x0F, 
// frame 1
0x00, 0xE0, 0xC0, 0xE0, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF1, 0x71, 0xFF, 0x7B, 0xFF, 0xFB, 0xFF, 
0xFA, 0xFF, 0x98, 0xFE, 0x28, 0xFC, 0x90, 0xF8, 0xE0, 0xF0, 0xC0, 0xE0, 0x00, 0xE0, 0xC0, 0xE0, 
0x00, 0x3F, 0x1F, 0x3F, 0x07, 0x1F, 0x01, 0xC7, 0x43, 0xFF, 0x74, 0xFF, 0x6B, 0xFF, 0x5A, 0xFF, 
0x5F, 0xFF, 0x1F, 0x7F, 0x1B, 0x3F, 0x15, 0x3F, 0x05, 0x1F, 0x0E, 0x1F, 0x0F, 0x1F, 0x01, 0x0F, 
// frame 2
0xF0, 0xF8, 0xC0, 0xF0, 0x80, 0xC0, 0xC0, 0xE1, 0x61, 0xF7, 0x77, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 
0x9A, 0xFF, 0x28, 0xFE, 0x08, 0xFC, 0x90, 0xF8, 0xE0, 0xF0, 0xC0, 0xE0, 0x00, 0xE0, 0xC0, 0xE0, 
0x0F, 0x1F, 0x03, 0x0F, 0x01, 0xC3, 0x43, 0xFF, 0x74, 0xFF, 0x6B, 0xFF, 0x6A, 0xFF, 0x5F, 0xFF, 
0x1F, 0x7F, 0x1B, 0x3F, 0x15, 0x3F, 0x15, 0x3F, 0x0D, 0x1F, 0x0E, 0x1F, 0x0B, 0x1F, 0x01, 0x0F, 
// frame 3
0xF8, 0xFC, 0xE0, 0xF8, 0x80, 0xE0, 0x60, 0xF0, 0x70, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0x9B, 0xFF, 
0x2A, 0xFF, 0x08, 0xFE, 0x98, 0xFC, 0xF0, 0xF8, 0xE0, 0xF0, 0x00, 0xE0, 0xC0, 0xE0, 0x00, 0xC0, 
0x07, 0x0F, 0x03, 0x07, 0x01, 0x07, 0x04, 0xFF, 0x6B, 0xFF, 0x6A, 0xFF, 0x5F, 0xFF, 0x5B, 0xFF, 
0x15, 0x7F, 0x15, 0x3F, 0x15, 0x3F, 0x0D, 0x1F, 0x0E, 0x1F, 0x0B, 0x1F, 0x01, 0x0F, 0x00, 0x03, 
};


PROGMEM const unsigned char bigBubble_plus_mask[] ={
// width, height
24, 24,
0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0x20, 0xF0, 0x10, 0x38, 0x08, 0x1C, 0x04, 0xCE, 0xC4, 0xEE, 0x64, 0xFE, 0x22, 0xF7, 0x02, 0x27, 0x02, 0x07, 
0x02, 0x07, 0x02, 0x07, 0x02, 0x07, 0x04, 0x0E, 0x04, 0x0E, 0x04, 0x0E, 0x08, 0x1C, 0x10, 0x38, 0x20, 0xF0, 0xC0, 0xE0, 0x00, 0xC0, 0x00, 0x00, 
0x00, 0x7E, 0x7E, 0xFF, 0x81, 0xFF, 0x00, 0x81, 0x00, 0x00, 0x00, 0x87, 0x87, 0xCF, 0x01, 0x87, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0xFF, 0x7E, 0xFF, 0x00, 0x7E, 
0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x04, 0x0F, 0x08, 0x1C, 0x10, 0x39, 0x21, 0x73, 0x23, 0x77, 0x22, 0x77, 0x40, 0xE2, 0x40, 0xE0, 0x40, 0xE0, 
0x40, 0xE0, 0x40, 0xE0, 0x40, 0xE0, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x10, 0x38, 0x08, 0x1C, 0x04, 0x0F, 0x03, 0x07, 0x00, 0x03, 0x00, 0x00, 
};

PROGMEM const unsigned char shockAura_plus_mask[] = {
// width, height
24, 24,
// frame 0
0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0xF8, 0xF8, 0x90, 0x90, 0x90, 0x90, 0xE0, 0xE0, 0x70, 0x70, 0x30, 0x30, 0x18, 0x18, 0x0F, 0x0F, 
0x0C, 0x0C, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xFC, 0xFC, 0xFA, 0xFA, 0x7C, 0x7C, 0xA6, 0xA6, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 
0x02, 0x02, 0x82, 0x82, 0x86, 0x86, 0xEF, 0xEF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC1, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x6F, 0x6F, 0x6F, 0x47, 0x47, 0x42, 0x42, 
0x80, 0x80, 0x48, 0x48, 0x24, 0x24, 0x13, 0x13, 0x0F, 0x0F, 0x06, 0x06, 0x02, 0x02, 0x3E, 0x3E, 0x0C, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 
0x10, 0x10, 0x30, 0x30, 0xF0, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x13, 0x13, 0x1F, 0x1F, 0x36, 0x36, 0x24, 0x24, 0x48, 0x48, 0x80, 0x80, 0x10, 0x10, 
// frame 1
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x20, 0x20, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x61, 0x3E, 0x3E, 0x1C, 0x1C, 0x08, 0x08, 
0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0x98, 0x98, 0xC0, 0xC0, 0x40, 0x40, 0x14, 0x14, 0x0C, 0x0C, 0x86, 0x86, 0x02, 0x02, 0x01, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0xE2, 0xE2, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0xFE, 0xFE, 0x3A, 0x3A, 0x12, 0x12, 0x10, 0x10, 
0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x10, 0x10, 0x09, 0x09, 0x0E, 0x0E, 0x46, 0x46, 0xEE, 0xEE, 0x44, 0x44, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0x10, 0x10, 0x13, 0x13, 0x1E, 0x1E, 0x04, 0x04, 0x0C, 0x0C, 0x17, 0x17, 0x21, 0x21, 0x02, 0x02, 0x02, 0x02, 
// frame 2
0x60, 0x60, 0x50, 0x50, 0xC2, 0xC2, 0x04, 0x04, 0x08, 0x08, 0x30, 0x30, 0xF0, 0xF0, 0xE0, 0xE0, 0x60, 0x60, 0x20, 0x20, 0x1B, 0x1B, 0x0C, 0x0C, 
0x08, 0x08, 0x04, 0x04, 0x03, 0x03, 0x00, 0x00, 0xE0, 0xE0, 0x13, 0x13, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x08, 0x08, 0x04, 0x04, 0x42, 0x42, 
0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x62, 0x62, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC1, 0xC1, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC2, 0xC2, 0x80, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x08, 0x08, 0x07, 0x07, 0x06, 0x06, 0x02, 0x02, 0x86, 0x86, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0x70, 0x70, 0x13, 0x13, 0x1D, 0x1D, 0x02, 0x02, 0x03, 0x03, 0x21, 0x21, 0x41, 0x41, 0x01, 0x01, 
// frame 3
0x10, 0x10, 0x20, 0x20, 0x00, 0x00, 0x08, 0x08, 0x10, 0x10, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 
0x0E, 0x0E, 0x0C, 0x0C, 0x08, 0x08, 0x08, 0x08, 0xF8, 0xF8, 0xF1, 0xF1, 0x78, 0x78, 0x24, 0x24, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 
0x08, 0x08, 0x08, 0x08, 0x18, 0x18, 0x3C, 0x3C, 0xC2, 0xC2, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x80, 0x80, 0x00, 0x00, 0xC7, 0xC7, 0xC7, 0xC7, 0x82, 0x82, 0x80, 0x80, 
0x00, 0x00, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x05, 0x05, 0x02, 0x02, 0x1E, 0x1E, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x3F, 0x3F, 0x10, 0x10, 0x21, 0x21, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
};

PROGMEM const unsigned char bubbleBullet_plus_mask[] = {
// width, height
6, 8,
0x0C, 0x0C, 0x12, 0x1E, 0x25, 0x3F, 
0x21, 0x3F, 0x12, 0x1E, 0x0C, 0x0C, 
};

struct Player
{
  public:
    uint8_t  x;
    uint8_t y;
    byte width, height;
    byte xSpeed, ySpeed;
};

Player trollyFish = {.x = 20, .y = 32, .width = 2, .height = 4, .xSpeed = 1, .ySpeed = 1};

void drawTrollyFish()
{
  if (arduboy.everyXFrames(3) && shock_burst > 0) // Manage shock bursting
    --shock_burst;
    
  byte faster = 1;
  if (buttons.pressed(UP_BUTTON) || buttons.pressed(DOWN_BUTTON)) faster = 2;
  
  if (arduboy.everyXFrames(6 / faster)) trollyFrame++;

  if (trollyFrame > 3 ) trollyFrame = 0;
  sprites.drawPlusMask(trollyFish.x - 6, trollyFish.y - 8, Trolly_plus_mask, trollyFrame);
  // Protect Powerup
  if (getPowerup(PU_PROTECTFISH) && (pu_timers[PUT_PROTECT] > 60 || pu_timers[PUT_PROTECT] % 2 == 0))
    sprites.drawPlusMask(trollyFish.x - 6 -4, trollyFish.y - 8 -4, bigBubble_plus_mask, 0);

  // Shock Powerup
  if (shock_burst > 0)
    sprites.drawPlusMask(trollyFish.x - 6 -4, trollyFish.y - 8 -4, shockAura_plus_mask, ((shock_burst * 10) / SHOCK_LENGTH * 3) / 10);
  
}

#endif
