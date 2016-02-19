#ifndef STAGE_H
#define STAGE_H

#include <Arduino.h>


#define MAX_ENEMIES             8

extern Physics physics;
extern unsigned int scorePlayer;

void spawnWave()
{
  unsigned int usedScore = scorePlayer >> 3;
  usedScore = (usedScore == 0) ? 1 : usedScore;

  if (arduboy.everyXFrames(1000 + (500 / usedScore)))
  {
    createEnemy(ENEMY_JELLY);
    createEnemy(ENEMY_EEL);
    createEnemy(ENEMY_BAD);
  }
}

boolean checkGameOver()
{
  Rect player = {.x = trollyFish.x, .y = trollyFish.y, .width = trollyFish.width, .height = trollyFish.height};
  Rect enemy;
  for (byte i = 0; i < MAX_ENEMIES; i++)
  {
    enemy.x = enemyFish[i].x + 3;
    enemy.y = enemyFish[i].y + 4;
    enemy.width = enemyFish[i].width - 4;
    enemy.height = enemyFish[i].height - 8;
    if (physics.collide(enemy, player))
    {
      arduboy.tunes.tone(90, 300);
      delay(400);
      arduboy.tunes.tone(100, 100);
      delay(300);
      arduboy.tunes.tone(150, 100);
      delay(300);
      arduboy.tunes.tone(90, 100);
      delay(300);
      arduboy.tunes.tone(300, 200);
      delay(400);
      return true;
    }
  }
  return false;
};



#endif
