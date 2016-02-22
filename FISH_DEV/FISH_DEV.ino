/*
 Trolly Fish: http://www.team-arg.org/fish-manual.html

 Arduboy version 0.2:  http://www.team-arg.org/fish-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

 2016 JO3RI - GAVENO

 License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game
#define GAME_ID 36

#include <SPI.h>
#include <EEPROM.h>
#include "Arglib.h"
#include "physics.h"
#include "menu.h"
#include "player.h"
#include "enemies.h"
#include "stage.h"
#include "powerups.h"
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
unsigned int scorePlayer;


unsigned char gameState = STATE_MENU_MAIN;
boolean soundYesNo;
byte counter = 0;
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
      if (counter > 180) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_MAIN:
      // show the splash art
      arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
      arduboy.drawBitmap(73, 2, titleMenu, 49, 24, WHITE);
      sprites.drawPlusMask(73 + (menuX*26), 2 + (menuY*12), bubbles_plus_mask, bubblesFrame);
      if (buttons.justPressed(RIGHT_BUTTON) && (!menuX)) menuX = !menuX;
      if (buttons.justPressed(LEFT_BUTTON) && (menuX)) menuX = !menuX;
      if (buttons.justPressed(DOWN_BUTTON) && (!menuY)) menuY = !menuY;
      if (buttons.justPressed(UP_BUTTON) && (menuY)) menuY = !menuY;
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = 2 + menuX + (2*menuY);
      break;
    case STATE_MENU_HELP: // QR code
      arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_INFO: // infoscreen
      arduboy.drawBitmap(16, 20, info_bitmap, 96, 24, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen
      arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
      arduboy.drawBitmap(81, 2, soundMenu, 33, 24, WHITE);
      sprites.drawPlusMask(78 + (soundYesNo*20) , 14 , bubbles_plus_mask, bubblesFrame);
      if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
      if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.audio.save_on_off();
        gameState = STATE_MENU_MAIN;
      }
      if (soundYesNo == true) arduboy.audio.on();
      else arduboy.audio.off();
      break;
    case STATE_MENU_PLAY:
      scorePlayer = 0;
      //starFish.resetPos();
      initStarFish(0);
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

      gameState = STATE_GAME_PLAYING;
      break;
    case STATE_GAME_PLAYING:
      checkInputs();
      spawnWave();
      updateStarFish();
      if (arduboy.everyXFrames(3)) updateEnemies();
      checkIfScored();
      drawTrollyFish();
      drawEnemies();
      drawScore(64,0,0);
      if (checkGameOver())gameState = STATE_GAME_OVER;
      break;
    case STATE_GAME_OVER:
      arduboy.drawBitmap(5, 5, gameOver, 118, 24, WHITE);
      drawScore(19,35,1);
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_GAME_PAUSE:
      if (buttons.justPressed(B_BUTTON))
      {
        gameState = STATE_GAME_PLAYING;
      }
      break;
  }
  arduboy.display();
}
