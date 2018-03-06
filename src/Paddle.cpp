// version 1

#include "Paddle.h"
#include <SDL_image.h>
#include "ResourceManager.h"

/**
* Creates an object of Paddle class
*/
Paddle::Paddle() : GameObject(){
	width = 150;
	height = 50;

	screenWidth = 900;
	x = 0;
	y = 560;
}

/**
* Destructor for Paddle class
*/
Paddle::~Paddle() {
}

/**
* Method to initialize private variables(data) of Paddle class
* @param xpo x-coordinate of Paddle
* @param ypo y-coordinate of Paddle
* @param screenW screen width
* @param ren object of SDL_Renderer, used to render Paddle on screen
*/
void Paddle::init(int xpo,int ypo,int screenW,SDL_Renderer* ren) {
	x = xpo;
	y = ypo;
	screenWidth = screenW;

	ResourceManager r = ResourceManager::instance();
	spriteSheet = r.load("Assets/images/bat_black.png");

	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Paddle allocated at (%d,%d)", x, y);
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
	}
}

/**
* Method used to render Paddle on screen
*/
void Paddle::render(SDL_Renderer* ren) {
	
	Dest.x = x;
	Dest.y = y;
	Dest.w = width;
	Dest.h = height;

	Src.x = 25;
	Src.y = 180;
	Src.w = 470;
	Src.h = 100;

	SDL_RenderCopy(ren, texture, &Src, &Dest);
}

/**
* Method used to update position and direction of Paddle
* @param c it is used to identify direction in which we should move Paddle
*/
void Paddle::update(char c) {
	if (c == 'l')
	{
		int newX = x + l;
		int rBorder = newX;
		if (rBorder <= 0)
			x = 0;
		else
			x = newX;
	}
		
	else if (c == 'r')
	{
		int newX = x + r;
		int lBorder = newX + width;
		if (lBorder >= screenWidth)
			x = screenWidth - width;
		else
			x = newX;
	}
}

/**
* Method used to reset position of Paddle to default configurations
* @param ix change x-coordinate of Paddle to ix
* @param iy change y-coordinate of Paddle to iy
*/
void Paddle::reset(int ix, int iy) {
	x = ix;
	y = iy;
}

