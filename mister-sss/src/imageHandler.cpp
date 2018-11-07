// imageHandler.cpp

#include "imageHandler.h"

/*********************************************************************
 * Constructor
 * 	Load the image and set some thangs up (Misspelled purposefully)
 * 	The bind spot is which texture buffer to bind to. Image will
 * 	never be unbound by this class.
 ********************************************************************/
ImageHandler :: ImageHandler(const char sheetFileName [], unsigned bindSpot) {
	texIndex = loadImage(sheetFileName, bindSpot, imgW, imgH);
}

/*********************************************************************
 * Destructor
 * 	Anti allocate the subimages that were stored, and delete the
 * 	texture from Open GL.
 ********************************************************************/
ImageHandler :: ~ImageHandler() {
	// All the pointers within Dims were dynamically allocated.
	for (unsigned i = 0; i < dims.size(); ++i) {
		delete [] dims[i];
	}

	glDeleteTextures(1, &texIndex);
}

/*********************************************************************
 * parseStrip()
 * 	Creates a bunch of separate rectagles for images within the
 * 	sprite sheet. These rectangles are stored as normalized floats,
 * 	because that is the easy way for open gl to read them.
 ********************************************************************/
void ImageHandler :: parseStrip(unsigned xOff,    unsigned yOff,
                                unsigned w,       unsigned h,
                                unsigned xRepeat, unsigned yRepeat,
                                unsigned xGap,    unsigned yGap) {
	unsigned rowJump = h + yGap;
	unsigned rowMax  = yOff + rowJump * yRepeat;

	unsigned colJump = w + xGap;
	unsigned colMax  = xOff + colJump * xRepeat;

	if (rowMax > imgH)
		throw std::runtime_error("Trying to create a strip that exceeds the image height.");
	else if (colMax > imgW)
		throw std::runtime_error("Trying to create a strip that exceeds the image width.");

	for (unsigned row = yOff; row < rowMax; row += rowJump) {
		for (unsigned col = xOff; col < colMax; col += colJump) {
			float * tmpFloat = new float[DIM_LEN];
			tmpFloat[OFFX_INDEX] = col;
			tmpFloat[OFFY_INDEX] = row;
			tmpFloat[IW_INDEX]   =  w ;
			tmpFloat[IH_INDEX]   =  h ;

			dims.push_back(tmpFloat);
		}
	}
}

/*********************************************************************
 * getDims()
 * 	Returns an array of the normalized x, y, width, and height of
 * 	the subimage parsed from the sprite sheet.
 * 	on the sprite sheet.
 ********************************************************************/
const float * const ImageHandler :: getDims(unsigned index) const {
	if (index < dims.size()) {
		return dims[index];
	} else {
		throw std::runtime_error("Trying to get a subimage that doesn't even exist!");
	}
}

/*********************************************************************
 * getSize()
 * 	Returns how many different subimages have been parsed.
 ********************************************************************/
unsigned ImageHandler :: getSize() const {
	return dims.size();
}

/*********************************************************************
 * getSheetWidth()
 * 	Returns the width of the sprite sheet loaded.
 ********************************************************************/
unsigned ImageHandler :: getSheetWidth() const {
	return imgW;
}

/*********************************************************************
 * getSheetHeight()
 * 	Returns the height of the sprite sheet loaded.
 ********************************************************************/
unsigned ImageHandler :: getSheetHeight() const {
	return imgH;
}
