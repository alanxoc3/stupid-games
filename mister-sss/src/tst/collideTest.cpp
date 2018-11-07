#include "../constants.h"
#include "../input.h"
#include "../graphics.h"
#include "../rectangle.h"
#include "../grid.h"
#include "../view.h"
#include "../timer.h"

int main(int argc, char ** argv) {
	const float PS = 9 * 32 / FPS;
	const float RS = 8.0 / FPS;

	Graphics g;
	View v(&g);
	Input input;
	Rectangle rect(10, 10, 32, 32);
	Rectangle push(200, 200, 64, 64);
	Grid grid;
	Timer t;
	float recSpeed = RS;

	int rectSize = 7;
	Rectangle rectangles[] = {
		Rectangle(-50, -50, 32, 32),
		Rectangle(-50, 50, 32, 32),
		Rectangle(50, -50, 32, 32),
		Rectangle(50, 50, 32, 32),
		Rectangle(100, 50, 16, 32),
		Rectangle(150, 150, 16, 16),
		Rectangle(200, 150, 8, 8)
		};

	float friction = .3;
	
	if (g.sdl_init() || g.gl_init())
		return 1;

	input.mouseCapture();
	v.center(rect);

	bool loopFlag = false;

	while(!loopFlag) {
		t.reset();
		input.update();
		if (input.isQuit())
			loopFlag = true;

		grid.update(input);

		// If you have both horizontal pressed at same time, go nowhere
		if (input.down(input.KEY_A) && input.down(input.KEY_D))
			rect.setHS(rect.getHS() * friction);
		else if (input.down(input.KEY_A))
			rect.setHS(-PS);
		else if (input.down(input.KEY_D))
			rect.setHS(PS);
		else
			rect.setHS(rect.getHS() * friction);

		// Same with verticals.
		if (input.down(input.KEY_W) && input.down(input.KEY_S))
			rect.setVS(rect.getVS() * friction);
		else if (input.down(input.KEY_W))
			rect.setVS(PS);
		else if (input.down(input.KEY_S))
			rect.setVS(-PS);
		else
			rect.setVS(rect.getVS() * friction);
			
		// Invert the mouse mode.
		if (input.pressed(input.KEY_ESC)) {
			SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE);
			recSpeed *= -1;
		}

		// Get debugging info.
		if (input.pressed(input.KEY_SPA)) {
			std::cout << "X: " << rect.getX() << " | Y: " << rect.getY() << std::endl;
			std::cout << "STATE: " << (int) grid.getOverallState() << std::endl;
			for (int i = 0; i < rectSize; ++i)
			{
				std::cout << "RIGHT: " << rect.willCollideRight(rectangles[i]) << std::endl;
				std::cout << "LEFT : " << rect.willCollideLeft(rectangles[i]) << std::endl;
				std::cout << "DOWN : " << rect.willCollideDown(rectangles[i]) << std::endl;
				std::cout << "UP   : " << rect.willCollideUp(rectangles[i]) << std::endl;
				//std::cout << "COLLISION #" << i + 1 << " ? " << (rect.isIntersecting(rectangles[i]) ? "YES" : "NO") << std::endl;
				//std::cout << "TOUCHING  #" << i + 1 << " ? " << (rect.isTouching(rectangles[i]) ? "YES" : "NO") << std::endl;
				//std::cout << "CONTAINS  #" << i + 1 << " ? " << (rect.isContaining(rectangles[i]) ? "YES" : "NO") << std::endl;
			}
		}

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

		push.setHS(push.getHS() * friction);
		push.setVS(push.getVS() * friction);

		// Collision without teleporting.
		for (int i = 0; i < rectSize; ++i)
		{
			if (rect.willIntersect(rectangles[i])) {
				if (rect.willCollideRight(rectangles[i])) {
					if (rectangles[i].getHS() < 0 || rect.getHS() > rectangles[i].getHS()) {
						rect.setHS(rectangles[i].getX() + rectangles[i].getHS() - rect.getX() - rect.getW());
					}
				} else if (rect.willCollideLeft(rectangles[i])) {
					if (rectangles[i].getHS() > 0 || rect.getHS() < rectangles[i].getHS()) {
						rect.setHS(rectangles[i].getX() + rectangles[i].getHS() + rectangles[i].getW() - rect.getX());
					}
				}

				if (rect.willCollideUp(rectangles[i])) {
					if (rectangles[i].getVS() < 0 || rect.getVS() > rectangles[i].getVS()) {
						rect.setVS(rectangles[i].getY() + rectangles[i].getVS() - rect.getY() - rect.getH());
					}
				} else if (rect.willCollideDown(rectangles[i])) {
					if (rectangles[i].getVS() > 0 || rect.getVS() < rectangles[i].getVS()) {
						rect.setVS(rectangles[i].getY() + rectangles[i].getVS() + rectangles[i].getH() - rect.getY());
					}
				}
			}
		}

		// COLLISION WITH TELEPORTING
		// for (int i = 0; i < rectSize; ++i)
		// {
			// if (rect.willCollideRight(rectangles[i])) {
				// if (rectangles[i].getHS() < 0 || rect.getHS() > rectangles[i].getHS()) {
					// rect.setHS(rectangles[i].getHS());
					// rect.setX(rectangles[i].getX() - rect.getW());
				// }
			// } else if (rect.willCollideLeft(rectangles[i])) {
				// if (rectangles[i].getHS() > 0 || rect.getHS() < rectangles[i].getHS()) {
					// rect.setHS(rectangles[i].getHS());
					// rect.setX(rectangles[i].getX() + rectangles[i].getW());
				// }
			// }
			// if (rect.willCollideUp(rectangles[i])) {
				// if (rectangles[i].getVS() < 0 || rect.getVS() > rectangles[i].getVS()) {
					// rect.setVS(rectangles[i].getVS());
					// rect.setY(rectangles[i].getY() - rect.getH());
				// }
			// } else if (rect.willCollideDown(rectangles[i])) {
				// if (rectangles[i].getVS() > 0 || rect.getVS() < rectangles[i].getVS()) {
					// rect.setVS(rectangles[i].getVS());
					// rect.setY(rectangles[i].getY() + rectangles[i].getH());
				// }
			// }
		// }

		if (push.isIntersecting(rect)) {
			push.addHS(rect.getHS() * (32*3 / FPS));
			push.addVS(rect.getVS() * (32*3 / FPS));
		}

		// if (push.willCollideRight(rect)) {
			// if (rect.getHS() < 0 || push.getHS() > rect.getHS()) {
				// push.setHS(rect.getHS());
				// push.setX(rect.getX() - push.getW());
			// }
		// } else if (push.willCollideLeft(rect)) {
			// if (rect.getHS() > 0 || push.getHS() < rect.getHS()) {
				// push.setHS(rect.getHS());
				// push.setX(rect.getX() + rect.getW());
			// }
		// }
		// if (push.willCollideUp(rect)) {
			// if (rect.getVS() < 0 || push.getVS() > rect.getVS()) {
				// push.setVS(rect.getVS());
				// push.setY(rect.getY() - push.getH());
			// }
		// } else if (push.willCollideDown(rect)) {
			// if (rect.getVS() > 0 || push.getVS() < rect.getVS()) {
				// push.setVS(rect.getVS());
				// push.setY(rect.getY() + rect.getH());
			// }
		// }

		// MOVE THE RECTANGLE
		rect.move();
		push.move();

		for (int i = 0; i < rectSize; ++i)
			rectangles[i].move();

		// Update the view to the rectangle.
		v.center(rect, true);

		g.drawCircle(input.mouseX(), input.mouseY(), 2, 5);

		// Draw collision rectangles
		for (int i = 0; i < rectSize; ++i)
			v.drawHollowRectangle(rectangles[i]);
			
		v.drawRectangle(rect);
		v.drawRectangle(push);
		v.drawCircle(-10, -10, 6, 8);
		v.drawCircle(-100, 100, 6, 8);
		grid.draw(g);
		g.update();

		// Delay for fps.
		if (t.getTicks() < 1000 / FPS)
			SDL_Delay(1000 / FPS - t.getTicks());
	}

	// Destructor clears memory.
	return 0;
}
