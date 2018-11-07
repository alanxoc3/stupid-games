// image.cpp

#include "image.h"

/*********************************************************************
 * Constructor
 * 	Image handler and the subimage index may be passed optionally.
 *********************************************************************/
Image :: Image(ImageHandler * imgHndl, unsigned subImage) {
	this->imgHndl = imgHndl;
	this->subImage = subImage;
	normal = true;
	z  = 0.0f;
	ix = 0.0f;
	iy = 0.0f;
	thingHandle = nullptr;
	index = 0;
}

/*********************************************************************
 * Copy Constructor && Equals Operator
 * 	Copies one image to another the right way! The image handler is
 * 	copied by pointer, and the thing handler is NOT copied.
 *********************************************************************/
Image & Image :: operator = (const Image & copy) {
	if (this == &copy)
		return *this;

	thingHandle = nullptr;
	subImage = copy.subImage;
	index = 0;
	normal = true;
	imgHndl = copy.imgHndl;
	z  = copy.z;
	ix = copy.ix;
	iy = copy.iy;

	return *this;
}

Image :: Image(const Image & copy) {
	*this = copy;
}

/*********************************************************************
 * setIX() && setIY()
 * 	Sets the relative offset of the image. This offset is either
 * 	the x and y position of the image, or added to the x and y
 * 	position of the image.
 *********************************************************************/
void Image :: setIX(float ix) {
	if (isNormalMode()) {
		this->ix = ix;
	} else {
		assert(thingHandle);
		thingHandle->setIX(index, ix);
	}
}

void Image :: setIY(float iy) {
	if (isNormalMode()) {
		this->iy = iy;
	} else {
		assert(thingHandle);
		thingHandle->setIY(index, iy);
	}
}

/*********************************************************************
 * setZ() && setZ()
 * 	Sets and gets the Z position. Note that this position is clipped
 * 	by OPEN GL, and must be between 1 and -1.
 *********************************************************************/
void Image :: setZ(float z ) {
	if (isNormalMode()) {
		this->z = z;
	} else {
		assert(thingHandle);
		thingHandle->setZ(index, z);
	}
}

float Image :: getZ() const {
	if (isDataMode()) {
		assert(thingHandle);
		return thingHandle->getZ(index);
	} else {
		return z;
	}
}


/*********************************************************************
 * getIX() && getIY()
 * 	The X and Y position relative to another x and y position. AKA
 * 	Center X and Y.
 *********************************************************************/
float Image :: getIX() const {
	if (isDataMode()) {
		assert(thingHandle);
		return thingHandle->getIX(index);
	} else {
		return ix;
	}
}

float Image :: getIY() const {
	if (isDataMode()) {
		assert(thingHandle);
		return thingHandle->getIY(index);
	} else {
		return iy;
	}
}

/*********************************************************************
 * getOFFX() && getOFFY()
 * 	Returns the offsetX and offsetY of the image in the sprite sheet.
 * 	These are accessed from the image handler, and will throw some
 * 	thing if the image handler is not set.
 *********************************************************************/
float Image :: getOFFX   () const {
	if (!imgHndl)
		throw std::runtime_error("Trying to get offset when image handler does not exits.");

	if (imgHndl->getSize() <= subImage)
		throw std::runtime_error("Trying to access non existent sub image from image handler.");

	return imgHndl->getDims(subImage) [ImageHandler :: OFFX_INDEX];
}

float Image :: getOFFY   () const {
	if (!imgHndl)
		throw std::runtime_error("Trying to get offset when image handler does not exits.");

	if (imgHndl->getSize() <= subImage)
		throw std::runtime_error("Trying to access non existent sub image from image handler.");

	return imgHndl->getDims(subImage) [ImageHandler :: OFFY_INDEX];
}

/*********************************************************************
 * getIW() && getIH()
 * 	Returns the subImage Width/Height, based on the Image Handler.
 * 	These are accessed from the image handler, and will throw some
 * 	thing if the image handler is not set.
 *********************************************************************/
float Image :: getIW     () const {
	if (!imgHndl)
		throw std::runtime_error("Trying to get subimage width when image handler does not exits.");

	if (imgHndl->getSize() <= subImage)
		throw std::runtime_error("Trying to access non existent sub image from image handler.");

	return imgHndl->getDims(subImage) [ImageHandler :: IW_INDEX];
}

float Image :: getIH     () const {
	if (!imgHndl)
		throw std::runtime_error("Trying to get subimage height when image handler does not exits.");

	if (imgHndl->getSize() <= subImage)
		throw std::runtime_error("Trying to access non existent sub image from image handler.");

	return imgHndl->getDims(subImage) [ImageHandler :: IH_INDEX];
}

/*********************************************************************
 * getIndex()
 * 	Returns the index used by the thingHandler.
 *********************************************************************/
unsigned Image :: getIndex() const {
	if (!thingHandle)
		throw std::runtime_error("Trying to access index from non existent thing handler.\nProbably not in data mode.");

	return index;
}

/*********************************************************************
 * getThingHandler()
 * 	Returns a pointer to the thing handler used by the image. Returns
 * 	nullptr if the image is not in data mode (aka in normal mode).
 *********************************************************************/
ThingHandler * Image :: getThingHandler() {
	return thingHandle;
}

/*********************************************************************
 * normalMode()
 * 	Sets the mode of the image to normal mode. The image is
 * 	in normal mode by default. Normal mode means that the image is
 * 	not linked to the thing handler any more, but the image is not
 * 	deleted from the thing handler.
 *********************************************************************/
void Image :: normalMode() {
	if (!normal) {
		normal = true;
		setIX( thingHandle->getIX(index) );
		setIY( thingHandle->getIY(index) );
		setZ ( thingHandle->getZ(index) );

		thingHandle = nullptr;
		index = 0;
	}
}

/*********************************************************************
 * dataMode()
 * 	Sets the mode of the image to data mode. This mode stores
 * 	all the variables on the thing handler instead of private vars.
 *********************************************************************/
void Image :: dataMode(ThingHandler * sss, unsigned index) {
	if (normal && sss != nullptr) {
		thingHandle = sss;
		this->index = index;

		thingHandle->setIX  (index, getIX());
		thingHandle->setIY  (index, getIY());
		thingHandle->setZ   (index, getZ());

		if (imgHndl != nullptr) {
			thingHandle->setIW  (index, getIW());
			thingHandle->setIH  (index, getIH());
			thingHandle->setOFFX(index, getOFFX());
			thingHandle->setOFFY(index, getOFFY());
		}

		normal = false;
	}
}

/*********************************************************************
 * isNormalMode()
 * 	Returns true if the image is in normal mode.
 *********************************************************************/
bool Image :: isNormalMode() const {
	return normal;
}

/*********************************************************************
 * isDataMode()
 * 	Returns true if the image is in data mode.
 ********************************************************************/
bool Image :: isDataMode  () const {
	return !normal;
}

/*********************************************************************
 * setSubImage()
 * 	Sets the sub image index, this index is then used to access the
 * 	W, H, OFFX, and OFFY from the image handler. If data mode is on,
 * 	then this function will set the XOFF, YOFF, IW, and IH on the
 * 	thingHandler.
 *********************************************************************/
void Image :: setSubImage(unsigned subImage) {
	if (!imgHndl)
		throw std::runtime_error("You are trying to add a subimage when there is no image handler.");

	if (subImage >= imgHndl->getSize())
		throw std::runtime_error("You are trying to add a subimage that is not in the image handler!");

	if (this->subImage != subImage) {
		this->subImage = subImage;
		if (isDataMode()) {
			thingHandle->setIW  ( index, getIW()   );
			thingHandle->setIH  ( index, getIH()   );
			thingHandle->setOFFX( index, getOFFX() );
			thingHandle->setOFFY( index, getOFFY() );
		}
	}
}

/*********************************************************************
 * getSubImage()
 * 	Returns the subimage index from the image handler.
 *********************************************************************/
unsigned Image :: getSubImage() const {
	return subImage;
}

/*********************************************************************
 * getImageHandler
 * 	Returns a pointer to the Image Handler that is being used by
 * 	this image class. If it is NULL, then there is no image handler.
 *********************************************************************/
ImageHandler * Image :: getImageHandler() {
	return imgHndl;
}

/*********************************************************************
 * setImageHandler
 * 	Sets the image handler to this parameter. If you pass NULL, then
 * 	many things will probably not work.
 *********************************************************************/
void Image :: setImageHandler(ImageHandler * imgHndl) {
	this->imgHndl = imgHndl;
}
