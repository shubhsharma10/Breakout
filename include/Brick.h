
#include "GameObject.h"

/**
*	A header file for Brick class
*/
class Brick : public GameObject {
public:
	/**
	* Creates an object of Brick class
	*/
	Brick();

	/**
	* Destructor for Brick class
	*/
	~Brick();

	/**
	* Variable to keep state of whether brick was hit or not
	*/
	bool hit = false;

	/**
	* Method to initialize a brick by loading it's image
	* @param xpo x-coordinate of top left most corner of the brick
	* @param ypo y-coordinate of top left most corner of the brick
	* @param ren object of SDL_Renderer, used to render brick on screen
	*/
	void init(int xpo, int ypo, SDL_Renderer* ren);

	/**
	* Method used to render ball on screen
	* @param ren object of SDL_Renderer, used to render brick on screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to update brick
	*/
	void update();

	/**
	* Method used to update whether brick is selected.
	*/
	void setSelected();

	/**
	* Method used to get whether brick is selected.
	*/
	bool getSelected();

private:
	/**
	* Spritesheet of brick
	*/
	SDL_Surface *spriteSheet;

	/**
	* Texture obtained from brick image
	*/
	SDL_Texture *texture;

	/**
	* Destination rectangle where brick should be rendered on screen
	*/
	SDL_Rect Dest;

	/**
	* Source rectangle from where brick is rendered on screen
	*/
	SDL_Rect Src;

	/**
	* Boolean variable to keep state of whether brick is selected or not
	*/
	bool selected;
};
