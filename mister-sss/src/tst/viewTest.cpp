#include "../constants.h"
#include "../input.h"
#include "../graphics.h"
#include "../rectangle.h"
#include "../grid.h"

int main(int argc, char ** argv) {
	Graphics g;
	Input input;
	Rectangle rect(10, 10, 32, 32);
	Grid grid;

	float radius = 0;
	float friction = .3;
	
	if (g.sdl_init() || g.gl_init())
		return 1;

	input.mouseCapture();

	bool loopFlag = false;

	while(!loopFlag) {
		input.update();
		if (input.isQuit())
			loopFlag = true;

		// Does nothing right now.
		grid.update(input);

		if (input.mouseDown())
			radius += 1;
		
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

		// MOVE THE RECTANGLE
		rect.move();

		float centerX = SCREEN_WIDTH/2  - rect.getX() - rect.getW()/2;
		float centerY = SCREEN_HEIGHT/2 - rect.getY() - rect.getH()/2;
		g.drawRectangle(rect.getX() + centerX, rect.getY() + centerY, rect.getW(), rect.getH());
		g.drawCircle(input.mouseX(), input.mouseY(), 2, 5);
		g.drawCircle(10   + centerX, 10  + centerY, 6, 8);
		g.drawCircle(-10  + centerX, -10 + centerY, 6, 8);
		g.drawCircle(-100 + centerX, 100 + centerY, 6, 8);
		grid.draw(g);
		g.update();
	}

	// Destructor clears memory.
	return 0;
}
