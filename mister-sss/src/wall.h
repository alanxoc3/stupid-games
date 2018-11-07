// wall.h

#ifndef _WALL_H
#define _WALL_H

#include "thing.h"
#include "imageHandler.h"
#include "constants.h"

class Wall : public Thing {
	public:
		Wall(ImageHandler * im);
		virtual int type() const { return ID_WALL; };
		virtual bool interact(Rectangle * other);
};

#endif // _WALL_H
