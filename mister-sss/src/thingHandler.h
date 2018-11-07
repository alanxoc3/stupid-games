/********************************************************************
 * sssThingHandler.h
 * 	The class here stores thing object data in a large array that
 * 	gets sent to the GPU via Open GL. Thing objects call this
 * 	object to get a reference number, then they can store their
 * 	data on the GPU and many trivial calculations will be accelrated
 * 	by the GPU. Attribs are: Exist, X, Y, W, H, HS, VS, IX, IY,
 * 	IMage, HitPoints, Max Hitpoints
 * 	All the objects in the game go through this process in order to
 * 	speed up the game. Note that the size to this array is static.
 * 	Once declared in the constructor, it cannot be changed unless
 * 	you call reset. Careful though, many thing objects may be
 * 	pointing to data you deleted with reset.
 ********************************************************************/

#ifndef _THING_HANDLER_H
#define _THING_HANDLER_H

#include "constants.h"
#include <queue>

class ThingHandler {
	public:
		ThingHandler(GLuint capacity);
		~ThingHandler();
		// Note, copying is disabled!
		inline ThingHandler(const ThingHandler & copy) {};
		inline ThingHandler & operator = (const ThingHandler & copy) { return *this; };

		GLuint addThing(
			const GLfloat & x  = 0.0f, //  1
			const GLfloat & y  = 0.0f, //  2
			const GLfloat & z  = 0.0f, //  3
			const GLfloat & w  = 0.0f, //  4
			const GLfloat & h  = 0.0f, //  5
			const GLfloat & hs = 0.0f, //  6
			const GLfloat & vs = 0.0f, //  7
			const GLfloat & ix = 0.0f, //  8
			const GLfloat & iy = 0.0f, //  9
			const GLfloat & iw = 0.0f, // 10
			const GLfloat & ih = 0.0f, // 11
			const GLfloat & ox = 0.0f, // 12
			const GLfloat & oy = 0.0f, // 13
			const GLfloat & hp = 0.0f, // 14
			const GLfloat & mh = 0.0f  // 15
		);

		void updatePositions();
		void drawThings(const float * viewMatrix, unsigned activeTexture, unsigned width, unsigned height);

		void removeThing(const GLuint & index);

		inline GLuint getCapacity() const { return capacity; };
		void reset(GLuint capacity);
		
		// GETTERS & SETTERS
		const GLfloat & getX   (const GLuint & index) const; //  1
		const GLfloat & getY   (const GLuint & index) const; //  2
		const GLfloat & getZ   (const GLuint & index) const; //  3
		const GLfloat & getW   (const GLuint & index) const; //  4
		const GLfloat & getH   (const GLuint & index) const; //  5
		const GLfloat & getHS  (const GLuint & index) const; //  6
		const GLfloat & getVS  (const GLuint & index) const; //  7
                                                           
		const GLfloat & getIX  (const GLuint & index) const; //  8
		const GLfloat & getIY  (const GLuint & index) const; //  9
		const GLfloat & getIW  (const GLuint & index) const; // 10
		const GLfloat & getIH  (const GLuint & index) const; // 11
		const GLfloat & getOFFX(const GLuint & index) const; // 12
		const GLfloat & getOFFY(const GLuint & index) const; // 13
                                                           
		const GLfloat & getHP  (const GLuint & index) const; // 14
		const GLfloat & getMH  (const GLuint & index) const; // 15

		const GLboolean isHPEnabled(const GLuint & index) const;

		void setX   (const GLuint & index, const GLfloat & val); //  1
		void setY   (const GLuint & index, const GLfloat & val); //  2
		void setZ   (const GLuint & index, const GLfloat & val); //  3
		void setW   (const GLuint & index, const GLfloat & val); //  4
		void setH   (const GLuint & index, const GLfloat & val); //  5
		void setHS  (const GLuint & index, const GLfloat & val); //  6
		void setVS  (const GLuint & index, const GLfloat & val); //  7
                                                               
		void setIX  (const GLuint & index, const GLfloat & val); //  8
		void setIY  (const GLuint & index, const GLfloat & val); //  9
		void setIW  (const GLuint & index, const GLfloat & val); // 10
		void setIH  (const GLuint & index, const GLfloat & val); // 11
		void setOFFX(const GLuint & index, const GLfloat & val); // 12
		void setOFFY(const GLuint & index, const GLfloat & val); // 13
                                                               
		void setHP  (const GLuint & index, const GLfloat & val); // 14
		void setMH  (const GLuint & index, const GLfloat & val); // 15

		void enableHP(const GLuint & index);
		void disableHP(const GLuint & index);

	private:
		// Helper functions.
		const GLfloat & getPosOff(const GLuint & index, const GLuint & offset) const;
		void setPosOff(const GLuint & index, const GLuint & offset, const GLfloat & val);
		void initTBO();
		void enditTBO();
		void initDraw();
		void enditDraw();
		void unbind();

		GLuint capacity;
		// The first slot (visible) is used to check if the thing will be drawn or not.
		GLfloat * thingGrid;
		GLfloat * feedData;

		// How many different inputs there are.
		static const GLuint LINE_SIZE = 16;
		// How many inputs into the TBO
		static const GLuint TBO_LINE_SIZE = 2;
		std::queue<GLuint> availableSpots;
		GLuint tbprogram, thandle, tbo, tvao, vbo, query, dprogram, dVShader, dFShader, dGShader, dvao;
};

#endif //_THING_HANDLER_H
