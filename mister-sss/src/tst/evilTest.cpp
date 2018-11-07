// evilTest.cpp - Alan Morgan

// Advanced collision.
// Have enemy/player auto remove index.
// Create bump back bonus

// Acceleration
// Create Enemy spawner. Don't spawn near walls!
// Create Menu.
// Add Music.
// Remove TBO

#include "../constants.h"
#include "../graphics.h"
#include "../input.h"
#include "../timer.h"
#include "../thingHandler.h"
#include "../helperGL.h"
#include "../view.h"
#include "../grid.h"
#include "../imageHandler.h"
#include "../image.h"
#include "../background.h"
#include "../thing.h"
#include "../living.h"
#include "../player.h"
#include "../enemy.h"
#include "../wall.h"

// Separated from main, so that destructors may get called before ending GL/SDL.
void runProgram(Graphics & g) {
	Input input;
	View v;
	// Not this yet
	Grid grid;
	Timer t;
	ImageHandler im (SPRITE_SHEET, 0);
	Background bg;
	im.parseStrip(0, 0, 70, 70, 16, 8, 0, 0);

	// Test sss thing handler - 20 capacity
	ThingHandler sss(27);
	// Friction
	float friction = .3;
	// Player and Rectangle Speed based on FPS
	const float RS = 10 * 16 / FPS;
	// used for wall speed;
	float recSpeed = RS;

	// We will create a bunch of testing rectangles, rect is the player.
	//Rectangle rect(10, 10, 16, 16);
	Player rect;
	rect.setXY(20, 5);
	rect.setImageHandler(&im);

	Enemy push;
	push.setImageHandler(&im);
	push.setIX(-70 / 2 + 16 / 2);
	push.setIY(-70 / 2 + 16 / 2);

	GLuint rectIndex = sss.addThing();

	//Image rectImg(&im, 2);
	//rectImg.dataMode(&sss, rectIndex);
	rect.dataMode(&sss, rectIndex);
	push.dataMode(&sss, sss.addThing());

	rect.setIX(-70 / 2 + 16 / 2);
	rect.setIY(-70 / 2 + 16 / 2);

	// These are all the wall rectangles (the hollow ones).
	unsigned rectSize = 9;
	std::vector<Wall> rectangles(rectSize, Wall(&im));

	// Set rectangles to datamode
	for (unsigned i = 0; i < rectSize; ++i) {
		rectangles[i].dataMode(&sss, sss.addThing());
		rectangles[i].setXY(-50, i * 90);
	}

	// Keep the mouse within the window.
	input.mouseCapture();

	// Loop forever.
	bool loopFlag = false;
	while(!loopFlag) {
		t.reset();
		input.update();
		loopFlag = input.isQuit();

		// Sync the grid with the mouse location.
		grid.update(input);
		rect.input(input);

		// ESC Key
		if (input.pressed(input.KEY_ESC)) {
			input.isMouseCaptured() ? input.mouseFree() : input.mouseCapture();
			recSpeed *= -1;
		}

		// SPACE Key
		if (input.down(input.KEY_SPA)) {
			for (unsigned i = 0; i < rectSize; ++i) {
				rectangles[i].setHS(recSpeed);
				rectangles[i].setVS(recSpeed);
			}
		} else {
			for (unsigned i = 0; i < rectSize; ++i) {
				rectangles[i].setHS(rectangles[i].getHS() * friction);
				rectangles[i].setVS(rectangles[i].getVS() * friction);
			}
		}

		push.moveTowards(&rect);

		// Point of view of enemy.
		// I push player, wall pushes player, player pushes me.
		if ( rect.interact(&push) ) {
			for (unsigned i = 0; i < rectSize; ++i) {
				if ( rectangles[i].interact(&rect) )
					rect.interact(&push);

				if ( rectangles[i].interact(&push) )
					push.interact(&rect);
					
				//if ( rect.interact(&push) )
			}

		} else {
			// Collision player with walls.
			for (unsigned i = 0; i < rectSize; ++i) {
				if ( rectangles[i].interact(&rect) )
					rect.interact(&push);

				rectangles[i].interact(&push);
			}
		}

		// COLLISIONS

		// END COLLISIONS
		rect.updateHand(grid);
		push.updateHand();
		push.update();

		// Move EVERYTHING hehe
		sss.updatePositions();

		// Center View
		v.center(rect, true);
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bg.drawBackground(&v);
		g.beginFrameBuffer();

		//glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sss.drawThings(v.getViewMatrix(), 0, im.getSheetWidth(), im.getSheetHeight());
		g.endFrameBuffer();

		// Draw the grid. And mouse.
		grid.draw();

		// This is what puts those above drawings into action.
		g.update();

		// Timer stuff! The sleep method sleeps the thread. We want to
		// sleep in order for us to have exactly the frame rate if this
		// is 30 frames per second, then 1 second / 30 is how much time
		// each frame should take. Subtract that by the amount of time
		// this loop took and you know how much time to sleep. Pausing
		// your program can help out your cpu, but remember that the
		// lower framerates can be choppy, and the higher ones may be
		// too hard for your computer to handle.
		if (t.getTicks() < 1000 / FPS)
			g.sleep(1000 / FPS - t.getTicks());
	}
}

int main(int argc, char ** argv) {
	// Program starts here.
	Graphics g;
	if (g.init())
		return 1;

	g.createFrameBuffer(VS_FRAMEBUFFER, FS_FRAMEBUFFER);

	runProgram(g);

	g.deleteFrameBuffer();

	g.endit();
	return 0;
}
