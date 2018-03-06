#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM
#define BRICKS_IN_A_ROW 12
#define NUMBER_OF_ROWS 6


// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#ifdef LINUX
#include <SDL2/SDL.h>
#else // This works for Mac and Linux
#include <SDL.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include "MainMenu.h"
#include "LTexture.h"
#include <Credit.h>
#include <Instructions.h>
#include <string>
#include <SDL_mixer.h>
#include <ResourceManager.h>
using namespace std;


// This class sets up a full graphics program
class SDLGraphicsProgram {
public:

	/**
	* Constructor for SDLGraphics application
	* @param w width of the window
	* @param h height of the window
	*/
	SDLGraphicsProgram(int w, int h);

	/**
	* Destructor for SDLGraphics application
	*/
	~SDLGraphicsProgram();

	/**
	* Method to update the application per frame
	* @param key_press keyboard input passed as parameter
	*/
	void update(char key_press);

	/**
	* Method to render shapes on the screen
	*/
	void render();

	/**
	* Method to loop continuously
	*/
	void loop();

	/**
	* Method to return pointer to the window
	*/
	SDL_Window* getSDLWindow();

	/**
	* Method to return pointer to the renderer
	*/
	SDL_Renderer* getSDLRenderer();

	/**
	* Method to handle collision of ball with paddle
	*/
	void CheckCollisionWithPaddle();

	/**
	* Method to handle collision of ball with bricks
	* @return True if collision happens
	*/
	bool CheckCollisionWithBricks();

	/**
	* Method to handle collision of ball with wall
	*/
	void CheckCollisionWithWall();

	/**
	* Method to reflect ball after collision with paddle
	* @param diffX difference between center of ball and paddle along x-axis
	*/
	void getReflectionFromPaddle(float diffX);

	/**
	* Method to reflect ball after collision with paddle
	* @param &brick pointer to the brick object
	* @return edge which got hit (1=top,2=right,3=bottom,4=left)
	*/
	int getContactEdge(GameObject* brick);

	/**
	* Method to create bricks orientation for each level
	* @param level to indicate the level
	* @return rows to indicate the number of rows required
	*/
	void createLevel(int level, int rows);

	/**
	* Method to render the background image
	*/
	void renderBGIMG(SDL_Renderer* ren);

	/**
	* Method to initialize the background image
	*/
	void bgInit(SDL_Renderer* ren);

	/**
	* Method to render level transition messages on the screen
	* @param level to indicate which level
	* @param status to indicate start or complete
	*/
	void renderMessage(int level, char status, SDL_Renderer*);

	/**
	* Method to reset the the flags
	*/
	void reset();
private:
	/**
	* Parameter to store screen height
	*/
	int screenHeight;

	/**
	* Parameter to store screen width
	*/
	int screenWidth;

	/**
	* Parameter to store refernece to window object rendered
	*/
	SDL_Window* gWindow;
	
	/**
	* Parameter to store refernece to render object
	*/
	SDL_Renderer* gRenderer = NULL;

	int livesLeft;
	LTexture lives;
	LTexture scores;
	LTexture resultOfGame;
	LTexture levels;

	/**
	* Method to determine whether ball center is above or below line between corner1 and corner2
	* @param corner1 Point containing x,y coordinate of one corner of the line
	* @param corner2 Point containing x,y coordinate of another corner of the line
	* @param ballCenter Point containing x,y coordinate of center of the ball
	* @return True if above False else
	*/
	bool isUpperSideOfLine(Point* corner1, Point* corner2, Point* ballCenter);

	MainMenu menu;

	/**
	* Parameter to store bricks used
	*/
	Brick bricks[NUMBER_OF_ROWS][BRICKS_IN_A_ROW];
	
	/**
	* Parameter to store refernece to paddle object
	*/
	Paddle paddle;

	/**
	* Parameter to store refernece to ball object
	*/
	Ball ball;

	/**
	* Parameter to store number of bricks used
	*/
	int numberOfBricks;

	/**
	* Parameter to store level number
	*/
	int level;

	/**
	* Parameter to store total number of bricks
	*/
	int totalnumberofbricks;
	std::string txtAry[6];

	//The music that will be played
	Mix_Music *music = NULL;


	/**
	* Variable to load the spritesheets
	*/
	SDL_Surface *spriteSheet;

	/**
	* Texture variables for different textures
	*/
	SDL_Texture *texture, *bgTexture, *ls1, *ls2, *ls3, *ls4, *ls5, *lc1, *lc2, *lc3, *lc4, *lc5;

	/**
	* A map to store textures
	*/
	std::map<string, SDL_Texture*> tmap;

	/**
	* Vriables used for generating texture (Src) and rendering the same (Dest)
	*/
	SDL_Rect Dest, Src;


	/**
	* A bunch of flags to enable good program flow
	*/
	bool mainMenu = true, credMenu = false, langMenu = false, instMenu = false;

	/**
	* Keeps track of the score
	*/
	int score = 0;

	/**
	* A bunch of flags to enable good program flow
	*/
	bool levelComplete = false, levelStart = false, gameOver = false, congrats = false, quit = false;;


	/**
	* Bunch of variables to keep track of different events time
	*/
	int lastTime, startTime, quitTime, congTime;

	/**
	* Variable to keep track of the language chosen
	*/
	char langChosen = 'e';

	/**
	* Max levels.
	*/
	int maxLevels;

	/**
	* Credit object
	*/
	Credit cred;

	/**
	* Instruction object
	*/
	Instruction inst;

	/**
	* ResrourceManager object
	*/
	ResourceManager r = ResourceManager::instance();
};

#endif
