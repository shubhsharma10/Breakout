#include "SDL.h"

/**
* Brick Dimension constants
*/
#define BRICK_WIDTH 75
#define BRICK_HEIGHT 50

/**
* Screen Dimension constants
*/
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

/**
*  Base class for all objects inside Game
*/
class GameObject {
public:
	/**
	*  Creates an object of GameObject class
	*/
	GameObject();

	/**
	*  Destructor for GameObject class
	*/
	virtual ~GameObject();

	/**
	* Public variables for x and y coordinate and height and width.
	*/
	int x, y, width, height;

	/**
	* Renders object of GameObject class
	*/
	virtual void render(SDL_Renderer* ren);

	/**
	* Method to detect whether current object and object passed
	* as argument collide.
	* @param other object with which collision detection will be done
	* @return True if objects collides.
	*/
	bool Collides(GameObject* other);
};

/**
*  Struct for representing a Point on surface
*/
struct Point {
	/**
	* x coordinate of the point
	*/
	float x;

	/**
	* y coordinate of the point
	*/
	float y;
};

#endif
