// version 1

#include "Ball.h"
#include <SDL_image.h>
#include "ResourceManager.h"

/**
* Creates an object of Ball class
*/
Ball::Ball() : GameObject() {
	x = 0;
	y = 0;
	width = 24;
	height = 24;

	dirX = 0;
	dirY = -1;
}

/**
* Destructor for Ball class
*/
Ball::~Ball() {

}

/**
* Method to initialize private variables(data) of Ball class
* @param xpo x-coordinate of ball
* @param ypo y-coordinate of ball
* @param vx1 velocity of ball along x-axis
* @param vy1 velocity of ball along y-axis
* @param screenW scrren width
* @param ren object of SDL_Renderer, used to render ball on screen
*/
void Ball::init(int xpo,int ypo,int vx1,int vy1, int screenW, SDL_Renderer* ren) {
	x = xpo;
	y = ypo;
	vx = vx1;
	vy = vy1;
	screenWidth = screenW;

	ResourceManager r = ResourceManager::instance();
	spriteSheet = r.load("Assets/images/ball_red.png");

	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Ball allocated at (%d,%d)", x, y);
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
	}
	setDirection(0, -1);
}

/**
* Method used to render ball on screen
*/
void Ball::render(SDL_Renderer* ren) {
	
	Dest.x = x;
	Dest.y = y;
	Dest.w = width;
	Dest.h = height;

	Src.x = 72;
	Src.y = 72;
	Src.w = 372;
	Src.h = 372;

	SDL_RenderCopy(ren, texture, 0, &Dest);
}

/**
* Method used to update position and direction of ball
* @param key it is used to identify direction in which we should move ball when its stationary
*/
void Ball::update(char key) 
{
	if (key == ' ')
	{
		ballStationary = false;
		updatePos();
	}
	if (ballStationary) {
		if (key == 'l')
		{
			int newX = x + l;
			int rBorder = newX;
			if (rBorder <= 0)
				x = 0;
			else
				x = newX;
		}
		else if (key == 'r')
		{
			int newX = x + r;
			int lBorder = newX + width;
			if (lBorder >= screenWidth)
				x = screenWidth - width;
			else
				x = newX;
		}
	}
	else if (!ballStationary) {
		updatePos();
	}

	/*
	if ((key == 'l' || key == 'r') && ballStationary) {
		ballStationary = false;
		updatePos();
	}
	*/

}

/**
* Method used to update position of ball based on its direction and velocity
*/
void Ball::updatePos() {
	x = x + (dirX * vx);
	y = y + (dirY * vy);
}

/**
* Method used to set direction of ball
* @param dx direction of ball along x-axis
* @param dy direction of ball along y-axis
*/
void Ball::setDirection(int dx,int dy) {
	dirX = dx;
	dirY = dy;
}

/**
* Method used to flip movement of ball along y-axis
*/
void Ball::flipYDirection() {
	dirY = -dirY;
}

/**
* Method used to flip movement of ball along x-axis
*/
void Ball::flipXDirection() {
	dirX = -dirX;
}

/**
* Method used to check whether ball is stationary or not
* @return True if ball is stationary
*/
bool Ball::isBallStationary() {
	return ballStationary;
}

/**
* Method used to update velocity of ball along x-axis
* @param newVx new velocity of ball along x-axis
*/
void Ball::changeVelocityX(int newVx) {
	vx = newVx;
}

/**
* Method used to update velocity of ball along y-axis
* @param newVy new velocity of ball along y-axis
*/
void Ball::changeVelocityY(int newVy) {
	vy = newVy;
}

/**
* Method used to reset position of ball to default configurations
* @param ix change x-coordinate of ball to ix
* @param iy change y-coordinate of ball to iy
*/
void Ball::reset(int ix, int iy) {
	x = ix;
	y = iy;
	dirX = 0;
	dirY = -1;
	ballStationary = true;
}