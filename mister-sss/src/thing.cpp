// thing.cpp

#include "thing.h"

/*********************************************************************
 * Constructor
 * 	Image handler must be passed, but it can be NULL, Though that
 * 	would limit the functionality of thing :(
 *********************************************************************/
Thing :: Thing(ImageHandler * ih) : Rectangle() {
	im.setImageHandler(ih);
}

/*********************************************************************
 * normalMode()
 * 	Sets the mode of the rectangle AND the image to normal.
 *********************************************************************/
void Thing :: normalMode() {
	Rectangle :: normalMode();
	im.normalMode();
}

/*********************************************************************
 * datamode()
 * 	Sets the mode of the rectangle and the image to data.
 *********************************************************************/
void Thing :: dataMode(ThingHandler * sss, unsigned index) {
	Rectangle :: dataMode(sss, index);
	im.dataMode(sss, index);
}
