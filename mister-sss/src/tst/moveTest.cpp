#include "../constants.h"
#include "../input.h"
#include "../graphics.h"
#include "../rectangle.h"

int main(int argc, char ** argv) {
	Graphics g;
	Input input;
	Rectangle rect(10, 10, 32, 32);
	float radius = 0;
	float friction = .3;
	
	if (g.sdl_init() || g.gl_init())
		return 1;

	bool loopFlag = false;

	while(!loopFlag) {
		input.update();
		if (input.isQuit())
			loopFlag = true;

		if (input.down(input.KEY_SPA))
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
			
		// MOVE THE RECTANGLE
		rect.move();

		//g.drawRectangle(-.5, -.5, .5, .5);
		g.pixelRectangle(rect);
		g.pixelCircle(10, 10, radius, radius * .8);
		//g.drawCircle(0, 0, .1, 10);
		g.update();
	}

	// Destructor clears memory.
	return 0;
}
