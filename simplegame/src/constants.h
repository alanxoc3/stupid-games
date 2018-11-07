#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define FPS 30
#define PIECE_WIDTH  16
#define PIECE_HEIGHT 16 
#define ROOM_WIDTH   15*16
#define ROOM_HEIGHT  15*16
#define FONT_SIZE    16
#define PLAYER_SPEED 8
#define ENEMY_SPAWN_GAP 4
#define ENEMY_POWERUP_GAP 10

#ifndef HOME_DIR
#define HOME_DIR ""
#endif

#define FNAME_PLAYER HOME_DIR "res/craft.png"
#define FNAME_COIN   HOME_DIR "res/coin.png"
#define FNAME_BADOT  HOME_DIR "res/greyCoin.png"
#define FNAME_BKGD   HOME_DIR "res/bkgd.png"
#define FNAME_FONT   HOME_DIR "res/babyBlocks.ttf"
#define FNAME_BUTTON HOME_DIR "res/startButton.png"
#define FNAME_SCORE  HOME_DIR "res/score.txt"

// These ones are for the player.
#define R  0
#define DR 1
#define D  2
#define DL 3
#define L  4
#define UL 5
#define U  6
#define UR 7

// For player facings.
#define LL 0
#define UU 1
#define RR 2
#define DD 3

// TYPES
#define TYPE_SPRITE 0
#define TYPE_COIN   23
#define TYPE_PLAYER 32
#define TYPE_ENEMY  88

#endif
