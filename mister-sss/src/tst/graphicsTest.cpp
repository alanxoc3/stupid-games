// graphicsTest.cpp - Alan Morgan

// Next, separate shader for health in thing handler.
// Then player. Then sword stuff.

#include "../constants.h"
#include "../graphics.h"
#include "../input.h"
#include "../timer.h"
#include "../sssThingHandler.h"
#include "../helperGL.h"
#include "../view.h"
#include "../grid.h"
#include "../imageHandler.h"
#include "../image.h"
#include "../background.h"
#include "../thing.h"
#include "../living.h"

void runProgram(Graphics & g) {
	Input input;
	View v;
	// Not this yet
	Grid grid;
	Timer t;
	ImageHandler im (SPRITE_SHEET, 0);
	Background bg;
	im.parseStrip(0, 0, 70, 70, 6, 1, 0, 0);

	// Test sss thing handler - 20 capacity
	SSS_ThingHandler sss(20);
	// Friction
	float friction = .3;
	// Player and Rectangle Speed based on FPS
	const float PS = 9 * 16 / FPS;
	const float RS = 5 * 16 / FPS;
	// used for wall speed;
	float recSpeed = RS;

	// We will create a bunch of testing rectangles, rect is the player.
	//Rectangle rect(10, 10, 16, 16);
	Living rect;
	rect.setImageHandler(&im);
	rect.setXYWH(10.0f, 10.0f, 16.0f, 16.0f);
	rect.setSubImage(2);
	rect.setMaxHP(100);
	rect.heal();

	Rectangle push(200, 200, 64, 64);

	GLuint rectIndex = sss.addThing();

	//Image rectImg(&im, 2);
	//rectImg.dataMode(&sss, rectIndex);
	rect.dataMode(&sss, rectIndex);
	push.dataMode(&sss, sss.addThing());

	rect.setIX(-70 / 2 + 16 / 2);
	rect.setIY(-70 / 2 + 16 / 2);

	printf("X: %f, Y: %f, W: %f, H: %f\n",
		sss.getOFFX(rectIndex), sss.getOFFY(rectIndex), sss.getIW(rectIndex), sss.getIH(rectIndex));

	// These are all the wall rectangles (the hollow ones).
	unsigned rectSize = 9;
	Rectangle rectangles[] = {
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle(),
		Rectangle()
	};

	// Set rectangles to datamode
	for (unsigned i = 0; i < rectSize; ++i) {
		rectangles[i].setXYWH(-50, i * 90, 70, 70),
		rectangles[i].dataMode(&sss, sss.addThing());
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

		// ASDW Keys
		if (input.down(input.KEY_A)) {
			rect.setHS(-PS);
			rect.setSubImage(5);
		} else if (input.down(input.KEY_D)) {
			rect.setHS(PS);
			rect.setSubImage(4);
		} else {
			rect.setHS(rect.getHS() * friction);
			rect.setSubImage(3);
		}

		if (input.down(input.KEY_W)) {
			rect.setVS(PS);
		} else if (input.down(input.KEY_S)) {
			rect.setVS(-PS);
		} else {
			rect.setVS(rect.getVS() * friction);
		}
	
		if (input.down(input.KEY_A) && input.down(input.KEY_D) &&
			input.down(input.KEY_W) && input.down(input.KEY_S)) {
			rect.setHS(0.0f);
			rect.setVS(0.0f);
		} else if (input.down(input.KEY_A) && input.down(input.KEY_D)) {
			rect.setHS(0.0f);
		} else if (input.down(input.KEY_W) && input.down(input.KEY_S)) {
			rect.setVS(0.0f);
		} else if (input.down(input.KEY_W) && input.down(input.KEY_A)) {
			rect.setDegSpeed(135.0f, PS);
		} else if (input.down(input.KEY_W) && input.down(input.KEY_D)) {
			rect.setDegSpeed(45.0f, PS);
		} else if (input.down(input.KEY_D) && input.down(input.KEY_S)) {
			rect.setDegSpeed(-45.0f, PS);
		} else if (input.down(input.KEY_A) && input.down(input.KEY_S)) {
			rect.setDegSpeed(-135.0f, PS);
		}

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

		// Collision player with walls.
		for (unsigned i = 0; i < rectSize; ++i)
		{
			if ( rect.willIntersect(rectangles[i])) {
				short curPos = rect.nextRelativePosition(rectangles[i]);

				if (curPos == rect.LEFT) {
					rect.setHS(rectangles[i].getX() + rectangles[i].getHS() - rect.getX() - rect.getW());
				} else if (curPos == rect.RIGHT) {
					rect.setHS(rectangles[i].getX() + rectangles[i].getHS() + rectangles[i].getW() - rect.getX());
				} else if (curPos == rect.DOWN) {
					rect.setVS(rectangles[i].getY() + rectangles[i].getVS() - rect.getY() - rect.getH());
				} else if (curPos == rect.UP) {
					rect.setVS(rectangles[i].getY() + rectangles[i].getVS() + rectangles[i].getH() - rect.getY());
				} else {
					// nextRelativePosition wont return anything else.
					assert(false);
				}
			}
		}

		// Collision player with push
		if (push.isIntersecting(rect)) {
			rect.hurt(1);
			push.addHS(rect.getHS() * (32*4 / FPS));
			push.addVS(rect.getVS() * (32*4 / FPS));
		}

		push.addHS(-push.getHS() * friction);
		push.addVS(-push.getVS() * friction);

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
