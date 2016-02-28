#ifndef SCORE_H
#define SCORE_H

#include <Arduino.h>

#define MAX_ENEMIES             9

extern Arduboy arduboy;
extern unsigned int scorePlayer;
extern Physics physics;
//extern Player trollyFish;

#define MAX_STARS   8
#define TOTAL_TYPES 4
#define STAR_HEIGHT 10

#define GAME_LEFT       3

#define PU_TURNFISH     0
#define PU_STOPFISH     1
#define PU_SHOOTFISH    2
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
// power-up 0
0x80, 0xD3, 0x12, 0xBF, 0x34, 0xFE, 0xF0, 0xFC, 0xF8, 0xFE, 0xFE, 0xFF, 
0xF8, 0xFE, 0xF0, 0xFC, 0x34, 0xFE, 0x12, 0xBF, 0x80, 0xD3, 0x00, 0x80, 
0x00, 0x01, 0x00, 0x07, 0x03, 0x07, 0x03, 0x07, 0x01, 0x0F, 0x0C, 0x0F, 
0x01, 0x0F, 0x03, 0x07, 0x03, 0x07, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 
// power-up 1
0xF8, 0xFF, 0x06, 0xFF, 0x02, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x3D, 0xFF, 
0x41, 0xFF, 0x81, 0xFF, 0x02, 0xFF, 0x06, 0xFF, 0xF8, 0xFE, 0x00, 0xF8, 
0x0C, 0x0F, 0x0B, 0x0F, 0x02, 0x0F, 0x04, 0x0F, 0x04, 0x0F, 0x04, 0x0F, 
0x04, 0x0F, 0x04, 0x0F, 0x02, 0x0F, 0x0B, 0x0F, 0x0C, 0x0F, 0x00, 0x0C, 
// power-up 2
0x20, 0x73, 0x22, 0x77, 0x04, 0xAE, 0x00, 0x8C, 0x00, 0x03, 0x03, 0x07, 
0x00, 0x03, 0x00, 0x8C, 0x04, 0xAE, 0x22, 0x77, 0x20, 0x73, 0x00, 0x70, 
0x00, 0x06, 0x02, 0x07, 0x01, 0x03, 0x00, 0x01, 0x00, 0x0E, 0x06, 0x0F, 
0x00, 0x0E, 0x00, 0x01, 0x01, 0x03, 0x02, 0x07, 0x00, 0x06, 0x00, 0x00, 
// power-up 3
0xE0, 0xF0, 0x30, 0xF8, 0x10, 0xF8, 0x10, 0xF8, 0xE0, 0xFC, 0x1C, 0xFE, 
0x22, 0xFF, 0x4D, 0xFF, 0x45, 0xFF, 0x41, 0xFF, 0x22, 0x7F, 0x1C, 0x3E, 
0x00, 0x01, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x00, 0x07, 0x06, 0x0F, 
0x09, 0x0F, 0x09, 0x0F, 0x06, 0x0F, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 
// power-up 4
0xF0, 0xFC, 0x0C, 0xFE, 0x42, 0xFF, 0x1A, 0x7F, 0x1D, 0x3F, 0x0D, 0x1F, 
0x01, 0x0F, 0x01, 0x83, 0x82, 0xC7, 0x02, 0x8F, 0x0C, 0xFE, 0xF0, 0xFC, 
0x00, 0x03, 0x03, 0x07, 0x04, 0x0F, 0x04, 0x0E, 0x08, 0x0C, 0x08, 0x0C, 
0x08, 0x0D, 0x09, 0x0F, 0x05, 0x0F, 0x04, 0x0F, 0x03, 0x07, 0x00, 0x03, 
// power-up 5
0x3C, 0x7E, 0x46, 0xFF, 0xBA, 0xFF, 0x7A, 0xFF, 0xF4, 0xFE, 0xE8, 0xFC, 
0xF4, 0xFE, 0x7A, 0xFF, 0xBA, 0xFF, 0x46, 0xFF, 0x3C, 0x7E, 0x00, 0x3C, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x07, 0x05, 0x0F, 
0x02, 0x07, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// power-up 6
0x00, 0xC0, 0x40, 0xF0, 0x70, 0xFC, 0x7C, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 
0xF7, 0xFF, 0xF3, 0xFF, 0x71, 0xFB, 0x30, 0x79, 0x10, 0x38, 0x00, 0x18, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0E, 0x06, 0x0F, 0x03, 0x07, 
0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// power-up 7
0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFE, 0x3A, 0xFF, 0x11, 0xBF, 
0x8A, 0xDF, 0xC4, 0xEE, 0xA0, 0xF4, 0x10, 0xF8, 0xA0, 0xF0, 0x40, 0xE0, 
0x03, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 
0x0F, 0x0F, 0x07, 0x0F, 0x03, 0x07, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 
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
    case PU_SHOOTFISH: arduboy.tunes.tone(300, 50);
      break;
    case PU_TURNFISH: arduboy.tunes.tone(300, 50);
      for (byte i = 0; i < MAX_ENEMIES; ++i)
      {
        if (enemyFish[i].active && enemyFish[i].x < 135)
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
        if (enemyFish[i].active && enemyFish[i].x < 135)
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
          // Y magnet
          if (starFish[i].y < trollyFish.y) starFish[i].y++;
          if (starFish[i].y > trollyFish.y) starFish[i].y--;

          // X magnet
          if (starFish[i].x < trollyFish.x) starFish[i].x++;
          if (starFish[i].x > trollyFish.x) starFish[i].x--;
        }
        if (arduboy.everyXFrames(2) && abs(trollyFish.x - starFish[i].x) < 42)
        {
          // Y magnet further out
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
