#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

#define GAME_TOP                3
#define GAME_BOTTOM             54
#define GAME_LEFT               3
#define GAME_RIGHT              112
#define STATE_GAME_PAUSE        9


extern Arduboy arduboy;
extern SimpleButtons buttons;
extern unsigned char gameState;


void checkInputs()
{
  if (buttons.justPressed(RIGHT_BUTTON))
  {
    
  }
  
  if (buttons.justPressed(LEFT_BUTTON))
  {
    
  }
  
  if (buttons.pressed(UP_BUTTON) && (trollyFish.y > GAME_TOP))
  {
    trollyFish.y -= trollyFish.ySpeed;
  }
  
  if (buttons.pressed(DOWN_BUTTON) && (trollyFish.y < GAME_BOTTOM - trollyFish.height))
  {
    trollyFish.y += trollyFish.ySpeed;
  }

  if (buttons.pressed(LEFT_BUTTON) && (trollyFish.x > GAME_LEFT))
  {
    trollyFish.x -= trollyFish.xSpeed;
  }
  
  if (buttons.pressed(RIGHT_BUTTON) && (trollyFish.x < GAME_RIGHT))
  {
    trollyFish.x += trollyFish.xSpeed;
  }
  
  if (buttons.justPressed(A_BUTTON))
  {
    
  }
  
  if (buttons.justPressed(B_BUTTON))
  {
    gameState = STATE_GAME_PAUSE;
  }
}


#endif
