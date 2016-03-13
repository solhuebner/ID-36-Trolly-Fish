#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

#define GAME_TOP                8
#define GAME_BOTTOM             60
#define GAME_LEFT               3
#define GAME_RIGHT              112
#define STATE_GAME_PAUSE        9


const byte bottom_border = GAME_BOTTOM - trollyFish.height + 2;

extern Arduboy arduboy;
extern SimpleButtons buttons;
extern unsigned char gameState;
extern void shootBubble();


void checkInputs()
{
  if (buttons.pressed(UP_BUTTON) && (trollyFish.y > GAME_TOP))
  {
    trollyFish.y -= trollyFish.ySpeed;
  }
  
  if (buttons.pressed(DOWN_BUTTON) && (trollyFish.y < bottom_border))
  {
    trollyFish.y += trollyFish.ySpeed;
  }
  if (buttons.justPressed(A_BUTTON))
  {
    gameState = STATE_GAME_PAUSE;
  }
  
  if (buttons.justPressed(B_BUTTON))
  {
    if (pu_shocks > 0 && shock_burst == 0)
    {
      --pu_shocks;
      shock_burst = SHOCK_LENGTH;
    }

    if (pu_bubbles > 0)
      shootBubble();
  }
}


#endif
