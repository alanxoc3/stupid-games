// wall.cpp

#include "wall.h"

Wall :: Wall(ImageHandler * im) : Thing() {
	if (im == nullptr)
		throw std::runtime_error("Need a non-null pointer in the wall constructor.");
	setImageHandler(im);
	setSubImage(16 * 2 + 12);
	setW(70);
	setH(70);
	setZ(Z_WALL);
}

bool Wall :: interact(Rectangle * other) {
	bool intersects = willIntersect(*other);

	if (other->type() == ID_ENEMY || other->type() == ID_PLAYER) {
		if (willIntersect(*other)) {
			short curPos = other->nextRelativePosition(*this);
			if (curPos == LEFT) {
				other->setHS(getX() + getHS() - other->getX() - other->getW());
			} else if (curPos == RIGHT) {
				other->setHS(getX() + getHS() + getW() - other->getX());
			} else if (curPos == DOWN) {
				other->setVS(getY() + getVS() - other->getY() - other->getH());
			} else if (curPos == UP) {
				other->setVS(getY() + getVS() + getH() - other->getY());
			} else {
				// nextRelativePosition wont return anything else.
				assert(false);
			}
		}
	}

	return intersects;
}
