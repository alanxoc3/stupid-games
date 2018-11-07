#include "../constants.h"
#include "../input.h"
#include "../graphics.h"

int main(int argc, char ** argv) {
	Graphics g;
	Input input;
	
	if (g.sdl_init() || g.gl_init())
		return 1;

	bool loopFlag = false;

	while(!loopFlag) {
		input.update();
		if (input.isQuit())
			loopFlag = true;
		
		if (input.pressed(input.KEY_A))
			std::cout << "letter a was pressed" << std::endl;

		if (input.released(input.KEY_A))
			std::cout << "letter a was released" << std::endl;

		if (input.down(input.KEY_A))
			std::cout << "A ";

		//g.drawRectangle(-.5, -.5, .5, .5);
		g.pixelRectangle(10, 10, 16, 16);
		g.pixelCircle(470, 470, 10, 10);
		//g.drawCircle(0, 0, .1, 10);
		g.update();
	}

	// Destructor clears memory.
	return 0;
}
