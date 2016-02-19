#ifndef SCORE_H
#define SCORE_H

#include <Arduino.h>

extern Arduboy arduboy;

#define MAX_STARS   4

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
      //x = 12  * random(12, 20);
      //y = 10 * random(1, 6);
      x += 128;
    }

};

GameObject starFish[MAX_STARS]; // = {.x = 128, .y = 32, .width = 7, .height = 7, .xSpeed = -2, .ySpeed = 0};

void initStarFish()
{
  for (byte i = 0; i < MAX_STARS; ++i)
  {
    starFish[i].x = ((16 * i) + (32 * (i % 2))) % 128;
    starFish[i].y = ((64 / (MAX_STARS / 2)) * (i + 1)) % 64;
    starFish[i].y += 8;
    starFish[i].width = 8;
    starFish[i].height = 8;
    starFish[i].xSpeed = -2;
    starFish[i].ySpeed = 0;
  }
}

void updateStarFish()
{
  for (byte i = 0; i < MAX_STARS; ++i)
  {
    starFish[i].x += starFish[i].xSpeed;
    if (starFish[i].x < GAME_LEFT) starFish[i].resetPos();
  
    arduboy.drawSprite(starFish[i].x, starFish[i].y, starMask_bitmaps, 7, 8, 0, BLACK);
    arduboy.drawSprite(starFish[i].x, starFish[i].y + 4, star_bitmaps, 7, 8, 0, WHITE);
  }
}

void checkIfScored() {
  Rect playerRect = {.x = trollyFish.x, .y = trollyFish.y, .width = trollyFish.width, .height = trollyFish.height};

  for (byte i = 0; i < MAX_STARS; ++i)
  {
    Rect starFishPoint = {.x = starFish[i].x, .y = starFish[i].y, .width = starFish[i].width, starFish[i].height};
  
    if (physics.collide(starFishPoint, playerRect)) {
      arduboy.tunes.tone(300, 200);
      scorePlayer++;
      starFish[i].resetPos();
    }
  }
}

#endif
