/*********************************************************************
 * constants.h
 * 	This file contains needed constants for the mister-sss game.  * 	The ID constants are used for determining if a thing or living
 * 	thing is of a specific ID. The values of these constants do not
 * 	matter as long as they are different. There should be a type ID
 * 	for class that inherits a thing. Also each individual
 * 	instantiation will have its own id. Most files include this
 * 	one for the mister sss game.
*********************************************************************/

#ifndef _CONSTANTS_H
#define _CONSTANTS_H
// Includes GL/gl.h
#define GLEW_STATIC
#include <GL/glew.h>
// Open GL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// For the window
#include <SDL2/SDL.h>
// For image loading
#include <SOIL/SOIL.h>
// Basic std libs
#include <cassert>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>

const float SCREEN_WIDTH  = 16 * 9 * 2;
const float SCREEN_HEIGHT = 16 * 9 * 2;
const float RENDER_WIDTH  = 16 * 9;
const float RENDER_HEIGHT = 16 * 9;
// Oddly, can't be const char *
const char  SSS_TITLE[]   = "MISTER-SSS";

const short ID_RECTANGLE = 0;
const short ID_THING  = 1;
const short ID_LIVING = 2;
const short ID_PLAYER = 3;
const short ID_WALL   = 4;

const short ID_ENEMY = 10;
const short ID_SIMPLE_ENEMY = 11;
const short ID_MEDIUM_ENEMY = 12;
const short ID_BOSS = 13;

const float PI = 3.14159265;

const float FPS = 30;
// Texture files
const char BACKGROUND     [] = "res/sss_tile.png";
const char SPRITE_SHEET   [] = "res/spriteSheet.png";
// Shader files
const char VS_BKGD        [] = "back.vs";
const char FS_BKGD        [] = "back.fs";
const char VS_TRANS_FDBK  [] = "thandle.vs";
const char VS_THING_DRAW  [] = "thingDraw.vs";
const char FS_THING_DRAW  [] = "thingDraw.fs";
const char GS_THING_DRAW  [] = "thingDraw.gs";
const char VS_FRAMEBUFFER [] = "frameBuffer.vs";
const char FS_FRAMEBUFFER [] = "frameBuffer.fs";
const char VS_GRID        [] = "grid.vs";
const char FS_GRID        [] = "grid.fs";
const char VS_MOUSE       [] = "mouse.vs";
const char FS_MOUSE       [] = "mouse.fs";
// Texture binding spots
const unsigned BSPOT_BKGD = 2;

// Z POSITIONS
const float Z_GREEN  = -.9f; // Health left
const float Z_RED    = -.8f; // Health bkgd
const float Z_ENEMY  = -.7f;
const float Z_PLAYER = -.5f;
const float Z_WALL   = -.4f;

const float DEF_X = 0.0f;
const float DEF_Y = 0.0f;
const float DEF_FRICTION = .3f;
const float DEF_MAXSPEED = 10 * 16 / FPS;
const unsigned DEF_MAXHP  = 10;
const unsigned DEF_ATTACK = 1;

const unsigned PLAYER_MAXHP = 20;
const float PLAYER_DIM = 16;
const float PLAYER_MAXSPEED = 9 * PLAYER_DIM / FPS;
const float PLAYER_HAND_DIM = 12;
const float PLAYER_HAND1_GAP = 4;
const float PLAYER_HAND2_GAP = 20;
const float PLAYER_HAND1_SPEED = 5 * PLAYER_MAXSPEED;
const float PLAYER_HAND2_SPEED = 5 * PLAYER_MAXSPEED;

const float ENEMY_DIM = 16.0f;
const float ENEMY_HAND_DIM = 9.0f;
const unsigned ENEMY_MAXHP = 5;
const float ENEMY_MAXSPEED = 5 * PLAYER_DIM / FPS;
const float ENEMY_ACCEL = PLAYER_DIM / FPS;

const unsigned ENEMY_DAMAGE = 1;
const unsigned PLAYER_DAMAGE = 1;

#endif // _CONSTANTS_H
