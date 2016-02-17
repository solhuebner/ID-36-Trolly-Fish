#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>

#define MAX_ENEMIES             8
#define GAME_LEFT               3

extern Arduboy arduboy;


byte fishFrame = 0;


const unsigned char PROGMEM enemieFish_bitmaps[] =
{
  //
  //     ###
  //   ## #######   #
  //  #    # # # # ##
  // # #    # # # ###
  // #   #       # ##
  //  ###########   #
  //    ##
  //
  //     ###
  //   ## #######  #
  //  #    # # # # #
  // #  #   # # # ##
  // ##   #      # #
  //  ###########  #
  //   # ##
  //
  //     ###
  //   ## #######   #
  //  #    # # # # ##
  // # #    # # # ###
  // #   #       # ##
  //  ###########   #
  //    ##
  //
  //     ###
  //   ## #######  #
  //  #    # # # # #
  // #      # # # ##
  // #  #        # #
  //  ###########  #
  //   ##
  0x30, 0x48, 0x54, 0xC4, 0xE2, 0x46, 0x4E, 0x54, 0x4C, 0x54, 0x4C, 0x54, 0x28, 0x10, 0x38, 0x7C,
  0x30, 0x68, 0xC4, 0x54, 0xC2, 0xE6, 0x4E, 0x54, 0x4C, 0x54, 0x4C, 0x54, 0x28, 0x10, 0x7C, 0x00,
  0x30, 0x48, 0x54, 0xC4, 0xE2, 0x46, 0x4E, 0x54, 0x4C, 0x54, 0x4C, 0x54, 0x28, 0x10, 0x38, 0x7C,
  0x30, 0x48, 0xC4, 0xE4, 0x42, 0x46, 0x4E, 0x54, 0x4C, 0x54, 0x4C, 0x54, 0x28, 0x10, 0x7C, 0x00,
};

const unsigned char PROGMEM enemieFishMask_bitmaps[] =
{
  //
  //     ###
  //   ##########   #
  //  ############ ##
  // ################
  // ############# ##
  //  ###########   #
  //    ##
  //
  //     ###
  //   ##########  #
  //  ############ #
  // ###############
  // ############# #
  //  ###########  #
  //   # ##
  //
  //     ###
  //   ##########   #
  //  ############ ##
  // ################
  // ############# ##
  //  ###########   #
  //    ##
  //
  //     ###
  //   ##########  #
  //  ############ #
  // ###############
  // ############# #
  //  ###########  #
  //   ##
  0x30, 0x78, 0x7C, 0xFC, 0xFE, 0x7E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x38, 0x10, 0x38, 0x7C,
  0x30, 0x78, 0xFC, 0x7C, 0xFE, 0xFE, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x38, 0x10, 0x7C, 0x00,
  0x30, 0x78, 0x7C, 0xFC, 0xFE, 0x7E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x38, 0x10, 0x38, 0x7C,
  0x30, 0x78, 0xFC, 0xFC, 0x7E, 0x7E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x38, 0x10, 0x7C, 0x00,
};

struct Enemies
{
  public:
    uint8_t  x;
    uint8_t y;
    byte width, height;
    byte xSpeed, ySpeed;

    void resetPos()
    {
      x = 12  * random(12, 20);
      y = 10 * random(1, 6);
    }

};

Enemies enemyFish[MAX_ENEMIES];

void updateEnemies()
{
  if (arduboy.everyXFrames(3))
  {
    for (byte i = 0; i < MAX_ENEMIES; i++)
    {
      enemyFish[i].x +=  enemyFish[i].xSpeed;
      if ( enemyFish[i].x < GAME_LEFT)  enemyFish[i].resetPos();
    }
  }
}

void drawEnemies()
{
  if (arduboy.everyXFrames(6)) fishFrame++;
  if (fishFrame > 3) fishFrame = 0;
  for (byte i = 0; i < MAX_ENEMIES; i++)
  {
    arduboy.drawSprite(enemyFish[i].x, enemyFish[i].y, enemieFishMask_bitmaps, 16, 8, fishFrame, BLACK);
    arduboy.drawSprite(enemyFish[i].x, enemyFish[i].y, enemieFish_bitmaps, 16, 8, fishFrame, WHITE);
  }
}


#endif
