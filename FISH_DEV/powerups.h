#ifndef SCORE_H
#define SCORE_H

#include <Arduino.h>

extern Arduboy arduboy;

#define MAX_STARS   8
#define TOTAL_TYPES 4
#define STAR_HEIGHT 10

#define PU_STARFISH     0
#define PU_TURNFISH     1
#define PU_STOPFISH     2
#define PU_POPFISH      3
//#define PU_SHOOTFISH    4
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


// Total of 8 powerups, 1 byte of flags
byte powerups = 0x00;   //Active powerups
byte pu_timers[4];

//pu_timers[PUT_STOP] = 255;        // Timer for PU_STOPFISH
//pu_timers[PUT_PROTECT] = 255;     // Timer for PU_PROTECTFISH
//pu_timers[PUT_SHOCK] = 255;       // Timer for PU_SHOCKFISH
//pu_timers[PUT_MAGNET] = 255;      // Timer for PU_MAGNETFISH

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
  powerUp.y = random(4, 60);
  powerUp.type = type;
}

// Event when collision with powerup
void triggerPowerUp(byte type)
{
  switch (type)
  {
    case PU_STARFISH: arduboy.tunes.tone(300, 40);
      break;
    case PU_TURNFISH: arduboy.tunes.tone(300, 40);
      break;
    case PU_STOPFISH: arduboy.tunes.tone(300, 40);
      setPowerup(type, PU_ON);
      pu_timers[PUT_STOP] = 255;
      break;
    case PU_POPFISH: arduboy.tunes.tone(300, 40);
      break;
    case PU_PROTECTFISH: arduboy.tunes.tone(300, 40);
      setPowerup(type, PU_ON);
      pu_timers[PUT_PROTECT] = 255;
      break;
    case PU_LIFEFISH: arduboy.tunes.tone(300, 40);
      break;
    case PU_SHOCKFISH: arduboy.tunes.tone(300, 40);
      setPowerup(type, PU_ON);
      pu_timers[PUT_SHOCK] = 255;
      break;
    case PU_MAGNETFISH: arduboy.tunes.tone(300, 40);
      setPowerup(type, PU_ON);
      pu_timers[PUT_MAGNET] = 255;
      break;
  }
}

void updatePowerUp()
{
  // Decrement timers
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

  // Update position, draw, collide
  if (powerUp.active)
  {
    powerUp.x += powerUp.xSpeed;
    if (powerUp.x < GAME_LEFT) powerUp.active = false;
    sprites.drawPlusMask(powerUp.x, powerUp.y - 1, starFish_plus_mask, 0);

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
      // random cluster
      for (byte i = 0; i < MAX_STARS; ++i)
      {
        starFish[i].x = 120 + random(24);
        starFish[i].y = random(20, 44);
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
