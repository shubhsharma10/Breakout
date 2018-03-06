#include "GameObject.h"

/**
*  Creates an object of GameObject class
*/
GameObject::GameObject() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

/**
*  Destructor for GameObject class
*/
GameObject::~GameObject() {
}

/**
* Renders object of GameObject class
*/
void GameObject::render(SDL_Renderer* ren) {
}

/**
* Method to detect whether current object and object passed
* as argument collide.
* @param other object with which collision detection will be done
* @return True if objects collides.
*/
bool GameObject::Collides(GameObject* other) {
	if (x + width >= other->x &&
		x <= other->x + other->width &&
		y + height >= other->y &&
		y <= other->y + other->height) {
		return true;
	}
	return false;
}
