#include "GameObject.h"
#include "LTexture.h"

class Instruction {
public:
	/**
	* Constructor of Instruction class
	*/
	Instruction();

	/**
	* Destructor of Instruction class
	*/
	~Instruction();

	/**
	* hit variable
	*/
	bool hit = false;

	/**
	* Method to initialize private variables(data) of Instruction class
	* @param ren object of SDL_Renderer, used to render Instruction screen
	*/
	void init(SDL_Renderer* ren);

	/**
	* Method used to render Instruction screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to update whether we are working with Instruction screen or not
	* @param key boolean to check whether back key is pressed or not
	*/
	void update(char key);

	/**
	* Method used to set language in which Instruction screen should be rendered
	* @param c set language variable as passed parameter
	*/
	void setLang(char c);

	/**
	* Method used to return false if we are working with Instruction screen and true if we are done working on Instruction screen
	*/
	bool getMainMenu();

	/**
	* Method used to get status of Instruction screen
	*/
	bool getFlag();

	/**
	* Method used to set status of Instruction screen
	*/
	void setFlag();

	/**
	* Method used to set status for main menu
	* @param v set mainmenu variable with passed parameter
	*/
	void setMainMenu(bool v);

private:
	/**
	* Textures for English and French text
	*/
	LTexture eText[50], fText[50];

	/**
	* Strings in English and French language
	*/
	std::string etxt[50], ftxt[50];

	/**
	* Spritesheet used for rendering
	*/
	SDL_Surface *spriteSheet;

	/**
	* Texture used for rendering
	*/
	SDL_Texture *texture;

	/**
	* Destination rectangle where image should be rendered on screen
	* Source rectangle from where image is rendered on screen
	*/
	SDL_Rect Dest, Src;

	/**
	* selected variable
	*/
	bool selected;

	/**
	* language variable
	*/
	char lang;

	/**
	* varible used to store status of main menu
	*/
	bool mainMenu = false;

	/**
	* varible used to store status of credit screen
	*/
	bool flag = false;
};