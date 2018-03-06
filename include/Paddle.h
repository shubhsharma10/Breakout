// version 1
#include "GameObject.h"

/**
*	A header file for Paddle class
*/
class Paddle : public GameObject{
public:
	/**
	* Creates an object of Paddle class
	*/
	Paddle();

	/**
	* Destructor for Paddle class
	*/
	~Paddle();

	/**
	* Method to initialize private variables(data) of Paddle class
	* @param xpo x-coordinate of Paddle
	* @param ypo y-coordinate of Paddle
	* @param screenW screen width
	* @param ren object of SDL_Renderer, used to render Paddle on screen
	*/
	void init(int xpo,int ypo,int screenW,SDL_Renderer* ren);

	/**
	* Method used to render Paddle on screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to update position and direction of Paddle
	* @param c it is used to identify direction in which we should move Paddle
	*/
	void update(char c);

	/**
	* Method used to reset position of Paddle to default configurations
	* @param ix change x-coordinate of Paddle to ix
	* @param iy change y-coordinate of Paddle to iy
	*/
	void reset(int ix, int iy);

private:
	/**
	* Width of scrren
	*/
	int screenWidth;

	/**
	* Used to move Paddle along x-axis by l unit
	*/
	int l = -5;

	/**
	* Used to move Paddle along x-axis by r unit
	*/
	int r = 5;

	/**
	* Spritesheet of Paddle
	*/
	SDL_Surface *spriteSheet;

	/**
	* Texture obtained from Paddle image
	*/
	SDL_Texture *texture;

	/**
	* Destination rectangle where Paddle should be rendered on screen
	* Source rectangle from where Paddle is rendered on screen
	*/
	SDL_Rect Dest, Src;

};
