// The awesome main loop file.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>

#include "argparse/argparse.h"
#include "pong_header.h"

// ----------- ALLEGRO STUFF ---------------
static ALLEGRO_DISPLAY *display = NULL;

void allegro_init() {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		exit(-1);
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		exit(-1);
	}

	// In drawing.c, exits if there was an error.
	fonts_init();

	display = al_create_display(SCR_W, SCR_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		exit(-1);
	}

	audio_init();
}

// ----------- ARGUMENT STUFF ---------------
static const char *const usage[] = {
    "pong [options]",
    NULL,
};

// Could return an error.
int getArgs(int argc, const char ** argv, Arguments * args) {
	args->multiplayer = 0;
	args->theme = NULL;

	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_BOOLEAN('m', "multiplayer", &args->multiplayer, "replaces computer with player."),
		OPT_END(),
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usage, 0);
	argparse_describe(&argparse, "\nA retro pong game made in c.", "");

	argc = argparse_parse(&argparse, argc, argv);

	return 0;
}

// ------------------ MAIN -----------------
int main(int argc, const char ** argv) {
	Arguments args;
	getArgs(argc, argv, &args);

	allegro_init();

	// Give us a nice good random seed.
	srand(time(0));

	int hasComputer = !args.multiplayer;
	
	int counter = 0;
	Paddle left_pad, right_pad;
	left_pad.side = LEFT;
	right_pad.side = RIGHT;
	left_pad.ypos = right_pad.ypos = SCR_H / 2 - PADDLE_HEIGHT / 2;
	left_pad.yspd = right_pad.yspd = 0;

	Ball ball;
	ball.radius = 10;
	resetBall(&ball);

	Scores scores;
	scores.l = scores.r = 0;

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	play_music();

	while(1){
		al_clear_to_color(al_map_rgb(0,0,0));

		ALLEGRO_EVENT event;

		if(al_get_next_event(queue, &event)){
			if (!hasComputer) {
				updatePaddlesForEvent(&event, &left_pad);
			}
			
			updatePaddlesForEvent(&event, &right_pad);

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
		}

		if (hasComputer) computerPaddle(&left_pad, &ball);

		updatePaddle(&left_pad);
		updatePaddle(&right_pad);
		
		moveBall(&ball);
		updatePaddles(&left_pad, &right_pad);
		updateBallPaddleCollisions(&ball, &left_pad, &right_pad);
		updateBallWallCollisions(&ball, &scores);

		drawBoard();
		drawPaddle(&left_pad);
		drawPaddle(&right_pad);
		drawBall(&ball);

		drawScore(LEFT, scores.l);
		drawScore(RIGHT, scores.r);

		al_flip_display();

		counter++;
		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);
	audio_destroy();

	return 0;
}
