// image.h

#ifndef _IMAGE_H
#define _IMAGE_H

#include "constants.h"
#include "thingHandler.h"
#include "imageHandler.h"

class Image {
	public:
		Image(ImageHandler * ih = nullptr, unsigned subImage = 0u);
		Image(const Image & copy);
		Image & operator = (const Image & copy);

		void setZ    (float z );
		void setIX   (float ix);
		void setIY   (float iy);

		float getZ      () const;
		float getIX     () const;
		float getIY     () const;
		float getOFFX   () const;
		float getOFFY   () const;
		float getIW     () const;
		float getIH     () const;

		// Thing Handler Stuff
		unsigned getIndex() const;
		ThingHandler * getThingHandler();
		void normalMode();
		void dataMode(ThingHandler * sss, unsigned index);
		bool isNormalMode() const;
		bool isDataMode  () const;

		void setSubImage(unsigned index);
		unsigned getSubImage() const;
		virtual ImageHandler * getImageHandler();
		virtual void setImageHandler(ImageHandler * ih);

	private:
		float z, ix, iy;
		ImageHandler * imgHndl;
		ThingHandler * thingHandle;
		unsigned subImage, index;
		bool normal;
};

#endif //_IMAGE_H
