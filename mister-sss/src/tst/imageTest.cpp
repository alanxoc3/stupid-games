// imageTest.cpp - Alan Morgan

#include "../constants.h"
#include "../input.h"
#include "../graphics.h"
#include "../rectangle.h"
#include "../grid.h"
#include "../view.h"
#include "../timer.h"

int main(int argc, char ** argv) {
	// In order to have the things go the same speed no matter the
	// frame rate, divide by the frame rate. Example: if you want to
	// move 28 pixels a second and have a 14 framerate, 28 / 14 = 2.
	// Your speed would be 2, that is you're moving 2 pixels per step.
	// PS is Player Speed. RS is Rectangle Speed
	const float PS = 9 * 32 / FPS;
	const float RS = 5 * 32 / FPS;

	// The SSS game engine needs a graphics, view, and input class in
	// order to function a game. The view is automatically the size of
	// the screen, that is set in the constants header. Also the view
	// has access to the the graphics class you use the entire time,
	// that is because we want to draw some things to the view, and
	// some to the screen.
	Graphics g;
	View v(&g);
	Input input;

	// The grid handles the SSS grid system that interprets mouse
	// input for moves. The timer class helps out with regulating the
	// framerate, it can serve a simple timer in the game as well.
	Grid grid;
	Timer t;

	// We will create a bunch of testing rectangles, rect is the player.
	Rectangle rect(10, 10, 32, 32);
	Rectangle push(200, 200, 64, 64);

	// recSpeed is used when you press [SPACE] on the keyboard, it
	// is the speed for all the wall hollow rectangles.
	float recSpeed = RS;

	// These are all the wall rectangles (the hollow ones).
	int rectSize = 9;
	Rectangle rectangles[] = {
		Rectangle(-50, -50, 32, 32),
		Rectangle(10, 10, 32, 32),
		Rectangle(-50, 50, 32, 32),
		Rectangle(50, -50, 32, 32),
		Rectangle(50, 50, 32, 32),
		Rectangle(50 + 32, 50 + 32, 32 + 8, 32),
		Rectangle(50 + 32 + 32 + 8, 50, 32, 32),
		Rectangle(150, 150, 16, 16),
		Rectangle(200, 150, 8, 8)
		};

	// Everything is given this default friction. The friction is
	// applied manually.
	float friction = .3;
	
	// You must have the graphics class call the SDL and GL inits, in
	// order for a functioning game.
	if (g.sdl_init() || g.gl_init())
		return 1;

	// Let us load a texture with SDL!
	glEnable(GL_TEXTURE_2D);

	GLuint texID = 0;
	SDL_Surface * surface = IMG_Load("down_head_0.png");

	if (!surface)
		std::cerr << "HELP ME!" << std::endl;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	int mode = GL_RGB;

	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	// The mouseCapture method for input keeps the mouse withing the
	// window. The mouse cannot leave the window unless the game
	// finishes or the mouseFree method is called.
	input.mouseCapture();

	// The view will start with the rect (player) in the center of it.
	v.center(rect);

	// Loop forever.
	bool loopFlag = false;
	while(!loopFlag) {

		// Reset the timer. The timer will be checked again when we are
		// done with all our stuff.
		t.reset();
		input.update();

		// Quit if the operating system/user wants to close this game.
		if (input.isQuit())
			loopFlag = true;

		// Sync the grid with the mouse location.
		grid.update(input);

		// If you have both horizontals pressed at same time, go nowhere
		// input.down will return true if the key is being held down
		// right now. We don't want to move if both horizontal keys are
		// being pressed.
		if (input.down(input.KEY_A) && input.down(input.KEY_D))
			rect.setHS(rect.getHS() * friction);
		else if (input.down(input.KEY_A))
			rect.setHS(-PS);
		else if (input.down(input.KEY_D))
			rect.setHS(PS);
		else
			rect.setHS(rect.getHS() * friction);

		// Same concepts as above, but with vertical keys.
		if (input.down(input.KEY_W) && input.down(input.KEY_S))
			rect.setVS(rect.getVS() * friction);
		else if (input.down(input.KEY_W))
			rect.setVS(PS);
		else if (input.down(input.KEY_S))
			rect.setVS(-PS);
		else
			rect.setVS(rect.getVS() * friction);
			
		// The input.pressed will return true only for a step/instant
		// of the key first being pressed down. Here we are changing
		// whether or not the mouse is bound/captured to the screen
		// when the escape key is pressed. And we are switching the
		// direction of all the hollow wall rectangles.
		if (input.pressed(input.KEY_ESC)) {
			input.isMouseCaptured() ? input.mouseFree() : input.mouseCapture();
			recSpeed *= -1;
		}

		// If the space bar is being held down, then all the rectangles
		// have speed. Otherwise they lose their speed due to friction.
		if (input.down(input.KEY_SPA)) {
			for (int i = 0; i < rectSize; ++i) {
				rectangles[i].setHS(recSpeed);
				rectangles[i].setVS(recSpeed);
			}
		} else {
			for (int i = 0; i < rectSize; ++i) {
				rectangles[i].setHS(rectangles[i].getHS() * friction);
				rectangles[i].setVS(rectangles[i].getVS() * friction);
			}
		}

		// The push rectangle is one the player may bump into and it
		// moves. Here the friction is acting on it.
		push.setHS(push.getHS() * friction);
		push.setVS(push.getVS() * friction);

		// Collision with all the wall rectangles is taken place here.
		// If a rectangle is in the view and will be intersecting with
		// the player, then bring the speed down when the rectangle
		// gets close to bumping into the wall.
		// This is speed based collision, as opposed to teleporting
		// based collision.
		for (int i = 0; i < rectSize; ++i)
		{
			if (v.getRect().isContaining(rectangles[i]) && rect.willIntersect(rectangles[i])) {
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

		// If the pushable rectangle is being pushed, then push it more
		// in that same direction.
		if (push.isIntersecting(rect)) {
			push.addHS(rect.getHS() * (32*3 / FPS));
			push.addVS(rect.getVS() * (32*3 / FPS));
		}

		// The move function moves the rectangles according to the
		// hspeed and vspeed. It accounts for friction if the rectangle
		// is given friction. In this case, the friction is handled in
		// the testing file.
		push.move();
		rect.move();

		for (int i = 0; i < rectSize; ++i)
			rectangles[i].move();

		// Update the view to the center to the rectangle. The boolean
		// there allows you to use a box that the rectangle may freely
		// move in if it is true.
		v.center(rect, false);

		// The input also contains the mouse coordinates if haven't
		// figured that out yet. This is using the graphics class to
		// draw a filled circle where the mouse is. That 2 is the
		// radius, and the 5 is the number of sides the circle has.
		g.drawCircle(input.mouseX(), input.mouseY(), 2, 5);

		// The view can draw shapes as well as the graphics class.
		// Remember, we gave the graphics class to the view. This is
		// drawing all the hollow wall rectangles, but according
		// to the world/view instead of the screen.
		for (int i = 0; i < rectSize; ++i)
			v.drawHollowRectangle(rectangles[i]);

		// These are two random lines, to show we can draw lines. The
		// lines stretch the view and the view's "pushBox" the pushBox
		// is the rectangle in which the player may freely move without
		// moving the view.
		v.drawLine(v.getRect().getX(), v.getRect().getY(), v.getRect().getX() + v.getRect().getW(), v.getRect().getY() + v.getRect().getH());
		v.drawLine(v.getPushBox().getX(), v.getPushBox().getY() + v.getPushBox().getH(), v.getPushBox().getX() + v.getPushBox().getW(), v.getPushBox().getY());

		// Draw the pushable rectangle.
		v.drawRectangle(push);


		// Player will go through a special process to draw.
		glBindTexture(GL_TEXTURE_2D, texID);

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0); glVertex3f(.75, 0, 0);
			glTexCoord2f(1, 1); glVertex3f(.75, .75, 0);
			glTexCoord2f(0, 1); glVertex3f(0, .75, 0);
		glEnd();
		v.drawRectangle(rect);

		// Draw some random circles in the view. They just prove we can
		// draw circles.
		v.drawCircle(-10, -10, 6, 8);
		v.drawCircle(-100, 100, 6, 8);

		// The grid for the SSS game is drawn here. It looks a bit like
		// a tic tac toe board. Note that it must be drawing to the
		// screen if it is given graphics, not the view.
		grid.draw(g);

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

	// The Destructors clear the memory for the program.
	return 0;
}
