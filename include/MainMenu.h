#include <string>
#include <SDL.h>
using namespace std;

class MainMenu{
public:
	/**
	* Constructor for MainMenu class
	*/
	MainMenu();

	/**
	* Destructor for MainMenu class
	*/
	~MainMenu();

	/**
	* Method used to initialize main menu screen
	* @param w width of screen
	* @param h height of screen
	* @param ren Renderer used to render screen
	*/
	void init(int w, int h,SDL_Renderer* ren);

	/**
	* Method used to render main menu screen
	* @param ren Renderer used to render screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to render main menu screen in respective language
	* @param ren Renderer used to render screen
	*/
	void renderLang(SDL_Renderer* ren);

	/**
	* Method used to update main menu screen based on key press
	* @param c character passed based on key press
	*/
	void update(char c);

	/**
	* Method used to select language out of all possible options
	* @param c character passed based on key press
	*/
	void updateLang(char c);

	/**
	* Method used to render text
	* @param s string to render
	* @param x render at x coordinate
	* @param y render at y coordinate
	* @param ren Renderer used to render screen
	*/
	void renderText(std::string s, int x, int y, SDL_Renderer* ren);

	/**
	* Method used to get game start status
	*/
	bool getStartStatus();

	/**
	* Method used to get game quit status
	*/
	bool getQuitStatus();

	/**
	* Method used to reset main menu to default setting
	*/
	void reset();

	/**
	* Method used to get status	of whether credit option is selected or not
	*/
	bool getCred();

	/**
	* Method used to set status	of credit option
	* @param v true if credit option is selected
	*/
	void setCred(bool v);

	/**
	* Method used to set status	of instruction option
	* @param v true if instruction option is selected
	*/
	void setInst(bool v);

	/**
	* Method used to get status of language selected
	*/
	bool getLang();

	/**
	* Method used to get language selected
	*/
	char getLangChosen();

	/**
	* Method used to get status of whether we are on main menu screen or not
	*/
	bool getMainMenu();

	/**
	* Method used to get status of instruction viewed
	*/
	bool getInst();

	/**
	* Method used to reset arrow position
	* @param n units by which arrow should be shifted
	*/
	void reduceArrowY(int n);

private:
	SDL_Surface *spriteSheet1, *spriteSheet2, *spriteSheet3, *sprite;
	SDL_Surface *fspriteSheet1, *fspriteSheet2, *fspriteSheet3;
	SDL_Texture *texture1, *texture2, *texture3, *cred, *eng, *french, *lang, *back, *ins;
	SDL_Texture *ftexture1, *ftexture2, *ftexture3, *fcred, *feng, *ffrench, *flang, *fback, *fins;
	SDL_Rect Dest, Src;
	bool selected;
	float arrowX, arrowY;
	int startX, startY;
	int quitX, quitY;
	int credX, credY;
	int langX, langY;
	int engX, engY;
	int frenchX, frenchY;
	int backX, backY;
	int insX, insY;
	std::string start = "START";
	std::string quit = "QUIT";
	int arrowPointing = 1, langArrow = 1;
	bool gameStart;
	bool gameQuit;
	bool gameIns;
	bool mainMenu = false;
	float hover = 0.3;
	float limit = 0.0;
	bool gameCred;
	bool gameLang, gameBack;
	char langChosen;
};
