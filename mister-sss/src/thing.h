// thing.h

#ifndef _THING_H
#define _THING_H

#include "rectangle.h"
#include "imageHandler.h"
#include "image.h"
#include "thingHandler.h"

/*********************************************************************
 * Thing
 * 	This class is a thing. Things are rectangles that have some sort
 * 	of graphic associated with it such as a pillar. Things are the
 * 	basis for ALL objects in the game, therefore, everything has a
 * 	unique type to test if one thing is a pillar, a player, or an
 * 	enemy... Since C++ does not have a good system for determining
 * 	if an object is a type, the type method here and the isOfType
 * 	function figure out if an object is a specific thing. Yes, one
 * 	can have a thing.
 ********************************************************************/
class Thing : public Rectangle {
	public:
		Thing(ImageHandler * ih = nullptr);

		// Returns an integer that should be specified in the constants.h file.
		virtual int type() const { return ID_THING; };

		// Wrapper for image methods.
		void  setZ (float z) { im.setZ(z);       };
		float getZ () const  { return im.getZ(); };

		void  setIX   (float ix) { im.setIX(ix);        };
		void  setIY   (float iy) { im.setIY(iy);        };
		float getIX     () const { return im.getIX();   };
		float getIY     () const { return im.getIY();   };
		float getOFFX   () const { return im.getOFFX(); };
		float getOFFY   () const { return im.getOFFY(); };
		float getIW     () const { return im.getIW();   };
		float getIH     () const { return im.getIH();   };

		void setSubImage(unsigned index)        { im.setSubImage(index);       };
		unsigned getSubImage() const            { return im.getSubImage();     };
		ImageHandler * getImageHandler()        { return im.getImageHandler(); };
		void setImageHandler(ImageHandler * ih) { im.setImageHandler(ih);      };

		virtual void normalMode();
		virtual void dataMode(ThingHandler * sss, unsigned index);
	private:
		Image im;
};

#endif
