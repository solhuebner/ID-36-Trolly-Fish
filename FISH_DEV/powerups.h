#ifndef SCORE_H
#define SCORE_H

#include <Arduino.h>

extern Arduboy arduboy;

const unsigned char PROGMEM star_bitmaps[] =
{
  //     #  
  //    ##  
  // #  #  #
  // ###### 
  //  ## #  
  //   #### 
  //  ##  ##
  //  #     
  0x0C, 0xD8, 0x78, 0x2E, 0x3B, 0x68, 0x44, 
};

const unsigned char PROGMEM starMask_bitmaps[] =
{
  //     #  
  //    ##  
  // #  #  #
  // ###### 
  //  ####  
  //   #### 
  //  ##  ##
  //  #     
  0x0C, 0xD8, 0x78, 0x3E, 0x3B, 0x68, 0x44, 
};

struct GameObject
{
  public:
    uint8_t x;
    uint8_t y;
    byte width, height;
    byte xSpeed, ySpeed;

    void resetPos()
    {
      x = 12  * random(12, 20);
      y = 10 * random(1, 6);
    }

};

GameObject starFish = {.x = 128, .y = 32, .width = 7, .height = 7, .xSpeed = -2, .ySpeed = 0};

void updateStarFish()
{
  starFish.x += starFish.xSpeed;
  if (starFish.x < GAME_LEFT) starFish.resetPos();

  arduboy.drawSprite(starFish.x, starFish.y, starMask_bitmaps, 7, 8, 0, BLACK);
  arduboy.drawSprite(starFish.x, starFish.y, star_bitmaps, 7, 8, 0, WHITE);
}

void checkIfScored() {
  Rect playerRect = {.x = trollyFish.x, .y = trollyFish.y, .width = trollyFish.width, .height = trollyFish.height};
  Rect starFishPoint = {.x = starFish.x, .y = starFish.y, .width = starFish.width, starFish.height};

  if (physics.collide(starFishPoint, playerRect)) {
    arduboy.tunes.tone(300, 200);
    scorePlayer++;
    starFish.resetPos();
  }
}

#endif
