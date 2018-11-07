#include "pong_header.h"
#include <stdio.h>

void updatePaddlesForEvent(const ALLEGRO_EVENT * const event, Paddle *left_pad){

		// right side		
		int UP_KEY = ALLEGRO_KEY_UP;
		int DOWN_KEY = ALLEGRO_KEY_DOWN;

		// if left side
		if(left_pad->side == LEFT){
			UP_KEY = ALLEGRO_KEY_W;
			DOWN_KEY = ALLEGRO_KEY_S;
		}

		if( event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == UP_KEY){
				left_pad->yspd = -PADDLE_SPEED;
			} else if(event->keyboard.keycode == DOWN_KEY){
				left_pad->yspd = PADDLE_SPEED;
			}
		} else if(event->type == ALLEGRO_EVENT_KEY_UP){
			if((event->keyboard.keycode == UP_KEY && left_pad->yspd < 0) || (event->keyboard.keycode == DOWN_KEY && left_pad->yspd > 0)){	
				left_pad->yspd = 0;
				ALLEGRO_KEYBOARD_STATE key_state;
				al_get_keyboard_state(&key_state);
				if(al_key_down(&key_state, UP_KEY)){
					left_pad->yspd = -PADDLE_SPEED;	
				} else if(al_key_down(&key_state,DOWN_KEY)){
					left_pad->yspd = PADDLE_SPEED;
				}
			}
		}
}

void updatePaddle(Paddle * const left_pad){

		if(left_pad->yspd != 0){

			left_pad->ypos += left_pad->yspd;

			if(left_pad->ypos < 0){
				left_pad->ypos = 0;
			} else if(left_pad->ypos > SCR_H - PADDLE_HEIGHT){
				left_pad->ypos = SCR_H - PADDLE_HEIGHT;
			}
		}
}

void updatePaddles(Paddle * const  left_pad, Paddle * const right_pad){
	updatePaddle(left_pad);
	updatePaddle(right_pad);
}

void moveBall(Ball * const ball) {	
	ball->xpos += ball->xspd;
	ball->ypos += ball->yspd;
	if (ball->lifespan % (FPS * 5) == 0 && ball->lifespan > 0) {
		ball->speed *= 1.1;

		float ang = atan(ball->yspd / ball->xspd);
		int xsgn = (ball->xspd > 0) ? 1 : 0;
		int ysgn = (ball->yspd > 0) ? 1 : 0;


		printf("SPEED: %.2f\n", ball->speed);

		ball->xspd = ball->speed * cos(ang);
		if ((ball->xspd > 0 && !xsgn) || (ball->xspd < 0 && xsgn))
			ball->xspd *= -1;

		ball->yspd = ball->speed * sin(ang);
		if ((ball->yspd > 0 && !ysgn) || (ball->yspd < 0 && ysgn))
			ball->yspd *= -1;
	}

	ball->lifespan++;
}

void resetBall(Ball * const ball){
	// reset ball
	ball->speed = BALL_SPEED;
	printf("SPEED: %.2f\n", ball->speed);

	ball->xpos = SCR_W / 2;
	ball->ypos = SCR_H / 2;
	ball->lifespan = 0;

	// Degrees
	float randNum  = (float) (rand() % 60);
	int multiplier = rand() % 4;

	// Add 15 degrees
	float ang = M_PI * (randNum + 15.0 + 90.0 * multiplier) / 180.0;
	ball->xspd = cos(ang) * BALL_SPEED;
	ball->yspd = sin(ang) * BALL_SPEED;
}

void updateBallWallCollisions(Ball * const ball, Scores * const scores){
	if (ball->ypos < 0 + ball->radius) {
		ball->yspd = -ball->yspd;
	} else if (ball->ypos > SCR_H - ball->radius) {
		ball->yspd = -ball->yspd;
	}

	if (ball->xpos < 0 + ball->radius){
		scores->r++;
		resetBall(ball);
	} else if(ball->xpos > SCR_W - ball->radius) {
		scores->l++;
		resetBall(ball);
	}

}

void updateBallPaddleCollision(Ball * const ball, Paddle * const pad, enum Side side) {

	if(side == LEFT){
		//printf("left\n");
	} else {
		//printf("right\n");
	}
	
	bool x_touch = false;
	bool heading = false;

	if(side == LEFT){
		x_touch = ball->xpos - ball->radius <= PADDLE_WIDTH;
		heading = ball->xspd < 0;
	} else {
		x_touch = ball->xpos + ball->radius  >= (SCR_W - PADDLE_WIDTH);
		heading = ball->xspd > 0;
	}

	bool y_touch = ball->ypos >= pad->ypos && ball->ypos <= (pad->ypos + PADDLE_HEIGHT);
	if(heading && x_touch && y_touch){
		//printf("HIT PADDLE \n");

		if(pad->yspd == 0){
			ball->xspd *= -1;
		} else {
			// pad moving up, makes ball move downwards
			// increase yspd, decrease xspd
			ball -> yspd -= (1/8.0) * pad->yspd;
			float dy = pow(ball->yspd, 2);
			ball -> xspd = sqrt(fabs((ball->speed * ball->speed) - dy));
			if(side == LEFT){
				ball -> xspd = fabs(ball -> xspd);
			} else {
				ball -> xspd = -fabs(ball -> xspd);
			}
			//printf("ball speed: %f\n", BALL_SPEED);
			//printf("DY: %f\n", dy);
			//printf("x: %f\n", ball->xspd);
			//printf("y: %f\n", ball->yspd);
		}

		//ball->xspd = -ball->xspd;
		//ball->yspd = -ball->yspd;

		ball->xpos += 2 * ball->xspd;

	}
}

// check if ball is touching paddle, and heading towards paddle
// if so, update ball trajectory
void updateBallPaddleCollisions(Ball * const ball, Paddle * const lp, Paddle * const rp){
	updateBallPaddleCollision(ball, lp, LEFT);
	updateBallPaddleCollision(ball, rp, RIGHT);
}


// Needs the ball, so it can make cool predictions.
void computerPaddle(Paddle * const pad, Ball * const ball) {
	// The buffer is the area the paddle can stop at.
	const float mid = PADDLE_HEIGHT / 2;
	const float third = PADDLE_HEIGHT / 3;
	float pad_center = pad->ypos + mid;
	const float dist_away_to_hit = 23;
	const float mid_buffer = PADDLE_HEIGHT / 3;

	float offset_mid = pad->ypos - SCR_H / 2;

	// Only move to ball if the ball is going to computer.
	if (ball->xspd < 0) {
		// if ball is going down then go down
		if (ball->xpos < dist_away_to_hit) {
			pad->yspd = (ball->yspd > 0) ? -PADDLE_SPEED : PADDLE_SPEED;
		} else if (ball->yspd > 0) {
			if (pad_center - third < ball->ypos) {
				pad->yspd = PADDLE_SPEED;
			} else {
				pad->yspd = 0;
			}
		} else {
			if (pad_center + third > ball->ypos) {
				pad->yspd = -PADDLE_SPEED;
			} else {
				pad->yspd = 0;
			}

		}
	} else if (fabs(offset_mid) > mid_buffer) {
		if (offset_mid > 0) pad->yspd = -PADDLE_SPEED;
		else pad->yspd = PADDLE_SPEED;
	} else {
		pad->yspd = 0;
	}
}

