#include "../constants.h"
#include "../input.h"
#include "../graphics.h"
#include "../rectangle.h"
#include "../grid.h"
#include "../view.h"

int main(int argc, char ** argv) {
	Graphics g;
	View v(&g);
	Input input;
	Rectangle rect(10, 10, 32, 32);
	Grid grid;

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
		input.update();
		if (input.isQuit())
			loopFlag = true;

		grid.update(input);

		// If you have both horizontal pressed at same time, go nowhere
		if (input.down(input.KEY_A) && input.down(input.KEY_D))
			rect.setHS(0);
		else if (input.down(input.KEY_A))
			rect.addHS(-1);
		else if (input.down(input.KEY_D))
			rect.addHS(1);
		else
			rect.setHS(rect.getHS() * friction);

		// Same with verticals.
		if (input.down(input.KEY_W) && input.down(input.KEY_S))
			rect.setVS(0);
		else if (input.down(input.KEY_W))
			rect.addVS(1);
		else if (input.down(input.KEY_S))
			rect.addVS(-1);
		else
			rect.setVS(rect.getVS() * friction);
			
		// Invert the mouse mode.
		if (input.pressed(input.KEY_ESC))
			SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE);

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

		for (int i = 0; i < rectSize; ++i)
		{
			if (rect.getHS() > 0 && rect.willCollideRight(rectangles[i])) {
				rect.setHS(0);
				rect.setX(rectangles[i].getX() - rect.getW());
			} else if (rect.getHS() < 0 && rect.willCollideLeft(rectangles[i])) {
				rect.setHS(0);
				rect.setX(rectangles[i].getX() + rectangles[i].getW());
			}

			if (rect.getVS() > 0 && rect.willCollideUp(rectangles[i])) {
				rect.setVS(0);
				rect.setY(rectangles[i].getY() - rect.getH());
			} else if (rect.getVS() < 0 && rect.willCollideDown(rectangles[i])) {
				rect.setVS(0);
				rect.setY(rectangles[i].getY() + rectangles[i].getH());
			}
		}

		// MOVE THE RECTANGLE
		rect.move();

		// Update the view to the rectangle.
		v.center(rect, true);

		g.drawCircle(input.mouseX(), input.mouseY(), 2, 5);

		// Draw collision rectangles
		for (int i = 0; i < rectSize; ++i)
			v.drawHollowRectangle(rectangles[i]);
			
		v.drawRectangle(rect);
		v.drawCircle(-10, -10, 6, 8);
		v.drawCircle(-100, 100, 6, 8);
		grid.draw(g);
		g.update();
	}

	// Destructor clears memory.
	return 0;
}
