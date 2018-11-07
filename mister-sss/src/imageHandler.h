// imageHandler.h

#ifndef _IMAGE_HANDLER_H
#define _IMAGE_HANDLER_H

#include "constants.h"
#include <vector>
#include "helperGL.h"

/*********************************************************************
 * ImageHandler
 * 	Basically, this class loads in an image, must be PNG, can have
 * 	Alpha. The image is then parsed based on parseStrip. You may
 * 	call parse strip multiple times and have many dimensions stored.
 ********************************************************************/
class ImageHandler {
	public:
		ImageHandler(const char sheetFileName [], unsigned bindSpot = 0);
		~ImageHandler();
		// Returns the highest sprite position.
		void parseStrip(unsigned xOff,    unsigned yOff,
		                unsigned w,       unsigned h,
                      unsigned xRepeat, unsigned yRepeat,
                      unsigned xGap,    unsigned yGap);

		// Returns 4 length vector, offx, offy, iw, ih
		const float * const getDims(unsigned index) const;
		unsigned getSize() const;

		unsigned getSheetWidth() const;
		unsigned getSheetHeight() const;

		static const unsigned OFFX_INDEX = 0;
		static const unsigned OFFY_INDEX = 1;
		static const unsigned IW_INDEX   = 2;
		static const unsigned IH_INDEX   = 3;
		
	private:
		GLuint texIndex, imgW, imgH;
		std::vector<float *> dims;
		// Copying is DISALLOWED!
		ImageHandler(const ImageHandler &);
		ImageHandler & operator = (const ImageHandler &);
		static const unsigned DIM_LEN = 4;
		
};

#endif //_IMAGE_HANDLER_H
