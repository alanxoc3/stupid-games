#include "pong_header.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GREEN al_map_rgb(0, 100, 0)
#define GRAY al_map_rgb(150, 150, 200)

#define FONT_FILE "res/invasion2000.ttf"

// Local to only drawing things.
static ALLEGRO_FONT *font = NULL;

void fonts_init() {
	// Addons needed for cool fonts.
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font(FONT_FILE, 72, 0);

	if (!font){
		fprintf(stderr, "Could not load cool font.\n");
		exit(-1);
	}
}

void drawBoard() {
	const float x = SCR_W / 2;
	const float y = SCR_H / 2;
	const float rad = SCR_H / 8;

	al_draw_line(x, 0, x, y-rad, GREEN, 5);
	al_draw_line(x, y+rad, x, SCR_H, GREEN, 5);
	al_draw_circle(x, y, rad, GREEN, 5);
}

void drawBall(const Ball * const ball) {
	al_draw_filled_circle(ball->xpos, ball->ypos, ball->radius, GREEN);
	al_draw_circle(ball->xpos, ball->ypos, ball->radius, GRAY, 5);
}

void drawPaddle(const Paddle * const pad) {
	int x1 = 0, x2 = 0;

	if(pad->side == LEFT){
		x1 = 0;
	} else {
		x1 = SCR_W - PADDLE_WIDTH;
	}

	x2 = x1 + PADDLE_WIDTH;

	al_draw_filled_rectangle(x1, pad->ypos, x2, pad->ypos + PADDLE_HEIGHT, GRAY);
}

void drawScore(enum Side side, const int score) {
	int xpos = SCR_W / 2; //side == LEFT ? 0 : SCR_W;

	char str[20]; // more than big enough string buffer.
	sprintf(str, "%d", score);

	if (side == LEFT) {
		xpos -= 10; // Buffer for the line
		al_draw_text(font, GRAY, xpos, 0, ALLEGRO_ALIGN_RIGHT, str);
	} else {
		xpos += 10; // Buffer for the line
		al_draw_text(font, GRAY, xpos, 0, ALLEGRO_ALIGN_LEFT, str);
	}
}
