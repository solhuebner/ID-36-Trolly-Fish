#ifndef SCORE_H
#define SCORE_H

#include <Arduino.h>

#define MAX_ENEMIES             8

extern Arduboy arduboy;
extern unsigned int scorePlayer;
extern Physics physics;
//extern Player trollyFish;

#define MAX_STARS   8
#define TOTAL_TYPES 4
#define STAR_HEIGHT 10

#define GAME_LEFT               3

#define PU_SHOOTFISH    0
#define PU_TURNFISH     1
#define PU_STOPFISH     2
#define PU_POPFISH      3
#define PU_PROTECTFISH  4
#define PU_LIFEFISH     5
#define PU_SHOCKFISH    6
#define PU_MAGNETFISH   7

#define PUT_STOP    0
#define PUT_PROTECT 1
#define PUT_SHOCK   2
#define PUT_MAGNET  3

#define MAX_POWERUPS    1
#define PU_ON           1
#define PU_OFF          0

PROGMEM const unsigned char starFish_plus_mask[] = {
// width, height
7, 8,
0x0C, 0x0C, 0xD8, 0xD8, 0x78, 0x78, 0x2E, 
0x3E, 0x3B, 0x3B, 0x68, 0x68, 0x44, 0x44, 
};

PROGMEM const unsigned char powerUps_plus_mask[] = {
// width, height
12, 16,
// power-up 1
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x05, 0xFF, 
0x05, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 2
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x25, 0xFF, 0xA5, 0xFF, 
0xA5, 0xFF, 0x85, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 3
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xBD, 0xFF, 0xE5, 0xFF, 0xA5, 0xFF, 
0xA5, 0xFF, 0x05, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 4
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x85, 0xFF, 0x85, 0xFF, 
0xBD, 0xFF, 0x05, 0xFF, 0x05, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 
0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 5
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x85, 0xFF, 0xA5, 0xFF, 
0xA5, 0xFF, 0x25, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 6
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x05, 0xFF, 0x05, 0xFF, 
0xA5, 0xFF, 0x25, 0xFF, 0x25, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
// power-up 7
0xFE, 0xFE, 0x02, 0xFE, 0x02, 0xFE, 0x7A, 0xFE, 0x4A, 0xFE, 0x4A, 0xFE, 
0xCA, 0xFE, 0x0A, 0xFE, 0x0A, 0xFE, 0xFA, 0xFE, 0x02, 0xFE, 0xFE, 0xFE, 
0x3F, 0x3F, 0x20, 0x3F, 0x20, 0x3F, 0x20, 0x3F, 0x20, 0x3F, 0x20, 0x3F, 
0x2F, 0x3F, 0x28, 0x3F, 0x28, 0x3F, 0x2F, 0x3F, 0x20, 0x3F, 0x3F, 0x3F, 
// power-up 8
0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFD, 0xFF, 0x05, 0xFF, 0x05, 0xFF, 
0xA5, 0xFF, 0x05, 0xFF, 0x05, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 
0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x17, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 
0x14, 0x1F, 0x14, 0x1F, 0x14, 0x1F, 0x17, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 
};


// Total of 8 powerups, 1 byte of flags
byte powerups = 0x00;   //Active powerups
byte pu_timers[4];

// Set the value of a powerup flag
void setPowerup(byte index, byte state)
{
  powerups = (state) ? powerups | _BV(index) : powerups & ~_BV(index);
}

// Get the value of a powerup flag
byte getPowerup(byte index)
{
  return (powerups & _BV(index));
}

struct PowerUp
{
  public:
    uint8_t x;
    uint8_t y;
    byte width, height;
    int8_t xSpeed, ySpeed;
    bool active;
    byte type;
};

PowerUp powerUp = {
  .x = 128, .y = 32, .width = 14,
  .height = 14, .xSpeed = -2, .ySpeed = 0,
  .active = false, .type = 0
};

void createPowerUp(byte type)
{
  if (powerUp.active) // already a powerup spawned
    return;
    
  // No duplicates on timed or consumed powerups
  while (getPowerup(type))
  {
    type = (++type) % 8;
  }

  powerUp.active = true;
  powerUp.x = 128;
  powerUp.y = random(4, 50);
  powerUp.type = type;
}

// Event when collision with powerup
void triggerPowerUp(byte type)
{
  switch (type)
  {
    case PU_STARFISH: arduboy.tunes.tone(300, 50);
      break;
    case PU_TURNFISH: arduboy.tunes.tone(300, 50);
      for (byte i = 0; i < MAX_ENEMIES; ++i)
      {
        if (enemyFish[i].active && enemyFish[i].x < 128)
        {
          if (enemyFish[i].type == ENEMY_JELLY) numJellys--;
          if (enemyFish[i].type == ENEMY_EEL) numEels--;
          enemyFish[i].type = ENEMY_STAR;
        }
      }
      break;
    case PU_STOPFISH: arduboy.tunes.tone(300, 50);
      setPowerup(type, PU_ON);
      pu_timers[PUT_STOP] = 153;
      break;
    case PU_POPFISH: arduboy.tunes.tone(300, 50);
      for (byte i = 0; i < MAX_ENEMIES; ++i)
      {
        if (enemyFish[i].active && enemyFish[i].x < 128)
        {
          if (enemyFish[i].type == ENEMY_JELLY) numJellys--;
          if (enemyFish[i].type == ENEMY_EEL) numEels--;
          enemyFish[i].type = ENEMY_BUBBLE;
        }
      }
      break;
    case PU_PROTECTFISH: arduboy.tunes.tone(350, 50);
      setPowerup(type, PU_ON);
      pu_timers[PUT_PROTECT] = 255;
      break;
    case PU_LIFEFISH: arduboy.tunes.tone(280, 50);
      setPowerup(type, PU_ON);
      break;
    case PU_SHOCKFISH: arduboy.tunes.tone(300, 50);
      setPowerup(type, PU_ON);
      pu_timers[PUT_SHOCK] = 255;
      break;
    case PU_MAGNETFISH: arduboy.tunes.tone(380, 50);
      setPowerup(type, PU_ON);
      pu_timers[PUT_MAGNET] = 255;
      break;
  }
}

void updatePowerUp()
{
  // Decrement timers
  if (arduboy.everyXFrames(3))
  {
    for (byte i = 0; i < 4; ++i)
    {
      if (pu_timers[i] > 0)
      {
        --pu_timers[i];
        if (pu_timers[i] == 0)
        {
          switch (i)
          {
            case PUT_STOP: setPowerup(PU_STOPFISH, PU_OFF);
              break;
            case PUT_SHOCK: setPowerup(PU_SHOCKFISH, PU_OFF);
              break;
            case PUT_PROTECT: setPowerup(PU_PROTECTFISH, PU_OFF);
              break;
            case PUT_MAGNET: setPowerup(PU_MAGNETFISH, PU_OFF);
              break;
          }
        }
      }
    }
  }

  // Update position, draw, collide
  if (powerUp.active)
  {
    powerUp.x += powerUp.xSpeed;
    if (powerUp.x < GAME_LEFT) powerUp.active = false;
    sprites.drawPlusMask(powerUp.x, powerUp.y - 1, powerUps_plus_mask, powerUp.type);

    Rect playerRect = {.x = trollyFish.x, .y = trollyFish.y, .width = trollyFish.width, .height = trollyFish.height};

    Rect powerupRect = {.x = powerUp.x, .y = powerUp.y, .width = powerUp.width, powerUp.height};
  
    if (physics.collide(powerupRect, playerRect))
    {
      // Trigger powerup effect
      triggerPowerUp(powerUp.type);

      // Reset powerup
      powerUp.active = false;
      powerUp.x += 128;
    }
  }
}

const byte SIN_Y[] = {
  23, 32, 41, 48,
  54, 48, 41, 32,
};



void initStarFish(byte type);

byte cycles = 3;

struct GameObject
{
  public:
    uint8_t x;
    uint8_t y;
    byte width, height;
    byte xSpeed, ySpeed;
    bool active;

    void resetPos();

};

GameObject starFish[MAX_STARS]; // = {.x = 128, .y = 32, .width = 7, .height = 7, .xSpeed = -2, .ySpeed = 0};

void GameObject::resetPos()
{
  //x = 12  * random(12, 20);
  //y = 10 * random(1, 6);
  x += 128;
  
  if (cycles > 0)
    --cycles;
  else
    active = false;

  bool done = true;
  for (byte i = 0; i < MAX_STARS; ++i)
  {
    if (starFish[i].active)
      done = false;
  }

  if (done)
  {
    initStarFish(random(TOTAL_TYPES));
  }
}

void initStarFish(byte type)
{
  switch (type)
  {
    case 0:
    {
      // Big sin wave
      for (byte i = 0; i < MAX_STARS; ++i)
      {
        starFish[i].x = 120 + (128 / MAX_STARS * i);
        starFish[i].y = SIN_Y[i] - 12;
        starFish[i].width = 8;
        starFish[i].height = STAR_HEIGHT;
        starFish[i].xSpeed = -2;
        starFish[i].ySpeed = 0;
        starFish[i].active = true;
        cycles = 3 * MAX_STARS;
      }
    }
    break;
    case 1:
    {
      byte y = random(5, 48);
      // Small sin wave
      for (byte i = 0; i < MAX_STARS; ++i)
      {
        starFish[i].x = 120 + (128 / MAX_STARS * i);
        starFish[i].y = (SIN_Y[i] / 3) - 12 + y;
        starFish[i].width = 8;
        starFish[i].height = STAR_HEIGHT;
        starFish[i].xSpeed = -2;
        starFish[i].ySpeed = 0;
        starFish[i].active = true;
        cycles = 3 * MAX_STARS;
      }
    }
    break;
    case 2:
    {
      // Straight line
      byte y = random(10, 54);
      for (byte i = 0; i < MAX_STARS; ++i)
      {
        starFish[i].x = 120 + (128 / MAX_STARS * i);
        starFish[i].y = y;
        starFish[i].width = 8;
        starFish[i].height = STAR_HEIGHT;
        starFish[i].xSpeed = -2;
        starFish[i].ySpeed = 0;
        starFish[i].active = true;
        cycles = 1 * MAX_STARS;
      }
    }
    break;
    case 3:
    {
      // square cluster
      byte y = random(10, 40);
      for (byte i = 0; i < MAX_STARS; ++i)
      {
        starFish[i].x = 120 + ((i % 4) * 8);
        starFish[i].y = y + ((i / 4) * 8);
        starFish[i].width = 8;
        starFish[i].height = STAR_HEIGHT;
        starFish[i].xSpeed = -2;
        starFish[i].ySpeed = 0;
        starFish[i].active = true;
        cycles = 0 * MAX_STARS;
      }
    }
    break;
  }
}

void updateStarFish()
{
  for (byte i = 0; i < MAX_STARS; ++i)
  {
    if (starFish[i].active)
    {
      if (getPowerup(PU_MAGNETFISH))
      {
        if (arduboy.everyXFrames(2) && abs(trollyFish.x - starFish[i].x) < 32)
        {
          if (starFish[i].y < trollyFish.y) starFish[i].y++;
          if (starFish[i].y > trollyFish.y) starFish[i].y--;
        }
      }
      
      starFish[i].x += starFish[i].xSpeed;
      if (starFish[i].x < GAME_LEFT) starFish[i].resetPos();
      sprites.drawPlusMask(starFish[i].x, starFish[i].y - 1, starFish_plus_mask, 0);
    }
  }
}

void checkIfScored() {
  Rect playerRect = {.x = trollyFish.x, .y = trollyFish.y, .width = trollyFish.width, .height = trollyFish.height};

  for (byte i = 0; i < MAX_STARS; ++i)
  {
    Rect starFishPoint = {.x = starFish[i].x, .y = starFish[i].y, .width = starFish[i].width, starFish[i].height};
  
    if (physics.collide(starFishPoint, playerRect)) {
      arduboy.tunes.tone(300, 40);
      scorePlayer++;
      starFish[i].resetPos();
    }
  }
}

#endif
