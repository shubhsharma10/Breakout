#include "GameObject.h"
#include "LTexture.h"

class Credit {
public:
	/**
	* Constructor of Credit class
	*/
	Credit();

	/**
	* Destructor of Credit class
	*/
	~Credit();

	/**
	* hit variable
	*/
	bool hit = false;

	/**
	* Method to initialize private variables(data) of Credit class
	* @param ren object of SDL_Renderer, used to render Credit screen
	*/
	void init(SDL_Renderer* ren);

	/**
	* Method used to render Credit screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to update whether we are working with credit screen or not
	* @param key boolean to check whether back key is pressed or not
	*/
	void update(char key);

	/**
	* Method used to set language in which credit screen should be rendered
	* @param c set language variable as passed parameter
	*/
	void setLang(char c);

	/**
	* Method used to return false if we are working with credit screen and true if we are done working on credit screen
	*/
	bool getMainMenu();

	/**
	* Method used to get status of credit screen
	*/
	bool getFlag();

	/**
	* Method used to set status of credit screen
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