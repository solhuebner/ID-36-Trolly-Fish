/*
  Trolly Fish: http://www.team-arg.org/fish-manual.html

  Arduboy version 1.0:  http://www.team-arg.org/fish-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016 - GAVENO - JO3RI - JUSTIN CRY

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 36

#include "Arglib.h"
#include "bitmaps.h"
#include "physics.h"
#include "player.h"
#include "enemies.h"
#include "powerups.h"
#include "stage.h"
#include "inputs.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)
#define STATE_GAME_PLAYING       8
#define STATE_GAME_PAUSE         9
#define STATE_GAME_OVER          10

Arduboy arduboy;
SimpleButtons buttons (arduboy);
Sprites sprites(arduboy);
unsigned long scorePlayer;

unsigned char gameState = STATE_MENU_MAIN;
boolean soundYesNo;
byte counter = 0;
byte pu_current = 0;
byte bubblesFrame = 0;
boolean menuX = true;
boolean menuY = false;

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  arduboy.initRandomSeed();
  gameState = STATE_MENU_INTRO;
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  if (arduboy.everyXFrames(6))bubblesFrame++;
  if (bubblesFrame > 12) bubblesFrame = 0;
  arduboy.clearDisplay();
  switch (gameState)
  {
    case STATE_MENU_INTRO:
      arduboy.drawBitmap(0, 8, TEAMarg2, 128, 48, WHITE);
      counter++;
      if (counter > 180)
      {
        for (byte i = 0; i < 16; i++)
        {
          titleBubbles[i].resetPos(false);
        }
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_MENU_MAIN:
      // show the splash art
      arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
      for (byte k = 0; k < 2; k++)
      {
        for (byte j = 0; j < 2; j++)
        {
          sprites.drawPlusMask(73 + (j * 26), 2 + (k * 12), titleMenu_plus_mask, j + (2 * k));
        }
      }
      sprites.drawPlusMask(73 + (menuX * 26), 2 + (menuY * 12), bubbles_plus_mask, bubblesFrame);
      if (buttons.justPressed(RIGHT_BUTTON) && (!menuX)) menuX = !menuX;
      if (buttons.justPressed(LEFT_BUTTON) && (menuX)) menuX = !menuX;
      if (buttons.justPressed(DOWN_BUTTON) && (!menuY)) menuY = !menuY;
      if (buttons.justPressed(UP_BUTTON) && (menuY)) menuY = !menuY;
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = 2 + menuX + (2 * menuY);
      break;
    case STATE_MENU_HELP: // QR code
      arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_INFO: // infoscreen
      arduboy.drawBitmap(14 , 8 , trollyFishTitle, 100 , 16, WHITE);
      arduboy.drawBitmap(26 , 30 , madeBy01, 75 , 8, WHITE);
      arduboy.drawBitmap(51 , 38 , madeBy02, 30 , 8, WHITE);
      arduboy.drawBitmap(30 , 50 , madeBy03, 79 , 8, WHITE);
      drawWeed();
      drawBubbles(false);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen
      arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
      sprites.drawPlusMask(88  , 2 , soundMenu_plus_mask, 0);
      for (byte j = 0; j < 2; j++)
      {
        sprites.drawPlusMask(78 + (24 * j) , 14 , soundMenu_plus_mask, 1 + j);
      }
      sprites.drawPlusMask(76 + (soundYesNo * 22) , 14 , bubbles_plus_mask, bubblesFrame);
      if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
      if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.audio.saveOnOff();
        gameState = STATE_MENU_MAIN;
      }
      if (soundYesNo == true) arduboy.audio.on();
      else arduboy.audio.off();
      break;
    case STATE_MENU_PLAY:
      scorePlayer = 0;
      pu_shocks = 0;
      pu_bubbles = 0;
      fr = 60;
      startStarFish();
      initStarFish(0);
      initBonuses();
      powerups = 0x00;   //No starting active powerups
      pu_current = 0;
      pu_timers[PUT_STOP] = 0;        // Timer for PU_STOPFISH
      pu_timers[PUT_PROTECT] = 0;     // Timer for PU_PROTECTFISH
      pu_timers[PUT_SHOCK] = 0;       // Timer for PU_SHOCKFISH
      pu_timers[PUT_MAGNET] = 0;      // Timer for PU_MAGNETFISH
      powerUp.active = false;
      for (byte i = 0; i < MAX_ENEMIES; i++)
      {
        enemyFish[i].xSpeed = -3;
        enemyFish[i].resetPos();
        enemyFish[i].width = 14;
        enemyFish[i].height = 8;
        enemyFish[i].burst = random(10);
        enemyFish[i].burstTimer = random(10, 60);

        enemyFish[i].active = false;
        enemyFish[i].type = 0; //bad fish
      }
      for (byte i = 0; i < 12; i++)
      {
        titleBubbles[i].resetPos(true);
      }

      gameState = STATE_GAME_PLAYING;
      break;
    case STATE_GAME_PLAYING:
      checkInputs();
      spawnWave();
      updatePowerUp();
      updateStarFish();
      updateBonus();
      updateBubble();
      if (arduboy.everyXFrames(3)) updateEnemies();
      checkIfScored();
      drawTrollyFish();
      drawEnemies();
      drawScore(86, 0, 0);
      drawWeed();
      drawBubbles(true);
      drawHUDPowerUps();

      if (checkGameOver())gameState = STATE_GAME_OVER;
      break;
    case STATE_GAME_OVER:
      arduboy.drawBitmap(26, 8, gameOver, 84, 16, WHITE);
      drawWeed();
      drawScore(32, 36, 1);
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_GAME_PAUSE:
      arduboy.drawBitmap(40, 20, pause, 48, 16, WHITE);
      drawWeed();
      drawBubbles(false);
      if (buttons.justPressed(A_BUTTON))
      {
        gameState = STATE_GAME_PLAYING;
      }
      break;
  }
  arduboy.display();
}
