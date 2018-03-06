#include "Brick.h"
#include <SDL_image.h>
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include "ResourceManager.h"

/**
* Creates an object of Brick class
*/
Brick::Brick() : GameObject(){
	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

/**
* Destructor for Brick class
*/
Brick::~Brick() {

}

/**
* Method to initialize a brick by loading it's image
* @param xpo x-coordinate of top left most corner of the brick
* @param ypo y-coordinate of top left most corner of the brick
* @param ren object of SDL_Renderer, used to render brick on screen
*/
void Brick::init(int xpo,int ypo,SDL_Renderer* ren) {
	x = xpo;
	y = ypo;
	width = BRICK_WIDTH;
	height = BRICK_HEIGHT;
	selected = false;
	hit = false;

	ResourceManager r = ResourceManager::instance();
	spriteSheet = r.load("Assets/images/brick_blue_small.png");

	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Brick allocated at (%d,%d)",xpo,ypo);
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
	}
}

/**
* Method used to render ball on screen
* @param ren object of SDL_Renderer, used to render brick on screen
*/
void Brick::render(SDL_Renderer* ren) {
	Dest.x = x;
	Dest.y = y;
	Dest.w = 75;
	Dest.h = 50;

	Src.x = 140;
	Src.y = 180;
	Src.w = 234;
	Src.h = 100;

	if (!hit && selected)
		SDL_RenderCopy(ren, texture, &Src, &Dest);
}

/**
* Method used to update brick
*/
void Brick::update() {
	//hit = true;
}

/**
* Method used to update whether brick is selected.
*/
void Brick::setSelected() {
	selected = true;
}

/**
* Method used to get whether brick is selected.
*/
bool Brick::getSelected() {
	return selected;
}