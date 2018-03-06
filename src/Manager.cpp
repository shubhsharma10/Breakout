#ifdef LINUX
#include <SDL2/SDL.h>
#else // This works for Mac and Linux
#include <SDL.h>
#endif

#include "ManagerHeader.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include "LTimer.h"
#include "LTexture.h"
#include <fstream>
#include <sstream>
#include <string>
#include <SDL_mixer.h>
#include <string>
#include <ResourceManager.h>

#define BRICKS_IN_A_ROW 12
#define NUMBER_OF_ROWS 6
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

using namespace std;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int PAD_INIT_X = 375;
const int PAD_INIT_Y = 550;
const int BALL_INIT_X = 438;
const int BALL_INIT_Y = 526;



/**
* Constructor for SDLGraphics application
* @param w width of the window
* @param h height of the window
*/
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) :screenWidth(w), screenHeight(h) {
	// Initialize random number generation.
	srand(time(NULL));
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag

	//To keep track of lives
	livesLeft = 3;

	numberOfBricks = 0;
	level = 0;

	const char* path;


	//Read file line by line and store it in an array
	path = "Config/config.txt";

	std::ifstream infile(path);
	std::string line, txt[5];

	int count = 0;
	while (std::getline(infile, line))
	{
		txt[count] = line;
		count++;
	}

	line = txt[2];
	int lnt = line.length();

	maxLevels = line.at(lnt-1) - '0';
	maxLevels = maxLevels > 5 ? 5 : maxLevels;
	maxLevels = maxLevels < 1 ? 1 : maxLevels;



	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)< 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {

		//Create window
		gWindow = SDL_CreateWindow("Assignment1",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screenWidth,
			screenHeight,
			SDL_WINDOW_SHOWN);

		// Check if Window did not create.
		if (gWindow == NULL) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		// Check if Renderer did not create.
		if (gRenderer == NULL) {
			errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

	}

	//Text's texture initialization
	lives.init(75, 50);
	scores.init(75, 50);
	resultOfGame.init(75, 50);
	levels.init(75, 50);

	/*
	//Setup bricks
	float sum = 0;
	float yColumn = 50;
	constexpr int xoffset = 75;
	constexpr int yoffset = 50;
	for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
		sum = 0;
		for (int j = 0; j < BRICKS_IN_A_ROW; ++j) {
			bricks[i][j].init(sum,yColumn,getSDLRenderer());
			sum += xoffset;
		}
			yColumn += yoffset;
	} */


	//setup paddle and ball
	
	menu.init(SCREEN_WIDTH, SCREEN_HEIGHT, getSDLRenderer());
	cred.init(getSDLRenderer());
	inst.init(getSDLRenderer());
	paddle.init(PAD_INIT_X, PAD_INIT_Y, screenWidth, getSDLRenderer());
	ball.init(BALL_INIT_X, BALL_INIT_Y, 0,4, screenWidth, getSDLRenderer());
	bgInit(getSDLRenderer());


	// If initialization did not work, then print out a list of errors in the constructor.
	if (!success) {
		errorStream << "Failed to initialize!\n";
		std::string errors = errorStream.str();
		std::cout << errors << "\n";
	}
	else {
		std::cout << "No SDL, or OpenGL, errors Detected\n\n";
	}
}

void SDLGraphicsProgram::bgInit(SDL_Renderer* ren) {
	spriteSheet = r.load("Assets/images/background.jpg");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string t = "bg";
		//const char* temp = "bg";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		bgTexture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[t] = bgTexture;
	}

	spriteSheet = r.load("Assets/images/level_1_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l1s";
		//const char* temp = "l1s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		if (texture == NULL)
		{
			//SDL_Log(temp);
		}
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_2_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l2s";
		//const char* temp = "l2s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_3_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l3s";
		//const char* temp = "l3s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_4_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l4s";
		//const char* temp = "l4s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_5_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l5s";
		//const char* temp = "l5s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_1_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l1c";
		//const char* temp = "l1c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_2_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l2c";
		//const char* temp = "l2c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0, 0));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_3_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l3c";
		//const char* temp = "l3c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_4_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l4c";
		//const char* temp = "l4c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/level_5_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "l5c";
		//const char* temp = "l5c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/gameover.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "gover";
		//const char* temp = "gover";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/congrats.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "con";
		//const char* temp = "con";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	// Check Here
	spriteSheet = r.load("Assets/images/flevel_1_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl1s";
		//const char* temp = "fl1s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		if (texture == NULL)
		{
		//	SDL_Log(temp);
		}
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_2_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl2s";
		//const char* temp = "fl2s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_3_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl3s";
		//const char* temp = "fl3s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_4_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl4s";
		//const char* temp = "fl4s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_5_start.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl5s";
		//const char* temp = "fl5s";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_1_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl1c";
		//const char* temp = "fl1c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_2_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl2c";
		//const char* temp = "fl2c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0, 0));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_3_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl3c";
		//const char* temp = "fl3c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_4_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl4c";
		//const char* temp = "fl4c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/flevel_5_complete.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fl5c";
		//const char* temp = "fl5c";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/fgameover.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fgover";
		//const char* temp = "fgover";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}

	spriteSheet = r.load("Assets/images/fcongrats.png");
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Background loaded");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		string temp = "fcon";
		//const char* temp = "fcon";
		SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 255, 255, 255));
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
		tmap[temp] = texture;
	}
}

void SDLGraphicsProgram::renderBGIMG(SDL_Renderer* ren) {
		Dest.x = 0;
		Dest.y = 0;
		Dest.w = SCREEN_WIDTH;
		Dest.h = SCREEN_HEIGHT;
		SDL_RenderCopy(ren, bgTexture, NULL, &Dest);
		//renderMessage(1, 'c', getSDLRenderer());
		//SDL_RenderPresent(ren);
}




/**
* Destructor for SDLGraphics application
*/
SDLGraphicsProgram::~SDLGraphicsProgram() {
	//Free the music
	Mix_FreeMusic(music);
	//Quit SDL_mixer
	Mix_CloseAudio();
	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	//Destroy window
	SDL_DestroyWindow(gWindow);
	// Point gWindow to NULL to ensure it points to nothing.
	gRenderer = NULL;
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}



/**
* Method to update the application per frame
* @param key_press keyboard input passed as parameter
*/
void SDLGraphicsProgram::update(char key_press)
{
	//Text's texture updation
	SDL_Color textColor = { 255, 255, 255 };
	stringstream livestring;
	stringstream scorestring;
	stringstream levelstring;

	std::string txt[50];
	const char* path;
	

	//Read file line by line and store it in an array
	if (langChosen == 'f')
		path = "Assets/languages/French.txt";
	else
		path = "Assets/languages/English.txt";

	std::ifstream infile(path);
	std::string line;
	int count = 0;
	while (std::getline(infile, line))
	{
		txt[count] = line;
		count++;
	}

	livestring << txt[0] << livesLeft;
	scorestring << txt[2] << score;
	levelstring << txt[1] << level;
	lives.loadFromRenderedText(getSDLRenderer(), livestring.str(), textColor);
	scores.loadFromRenderedText(getSDLRenderer(), scorestring.str(), textColor);
	resultOfGame.loadFromRenderedText(getSDLRenderer(), "You ", textColor);
	levels.loadFromRenderedText(getSDLRenderer(), levelstring.str(), textColor);

	CheckCollisionWithPaddle();
	CheckCollisionWithBricks();
	CheckCollisionWithWall();
	
	for (int i = 0; i < NUMBER_OF_ROWS; ++i)
	{
		for (int j = 0; j < BRICKS_IN_A_ROW; ++j)
			bricks[i][j].update();
	}

	paddle.update(key_press);
	ball.update(key_press);

	//After update, reset key to NULL, otherwise, it will just keep looping over and over.
	key_press = NULL;
}

/**
* Method to handle collision of ball with wall
*/
void SDLGraphicsProgram::CheckCollisionWithWall() {
	// Calculate ball's center coordinate
	float ballCenterX = ball.x + (ball.width / 2);
	float ballCenterY = ball.y + (ball.height / 2);

	if (ballCenterX + (ball.width/2) > SCREEN_WIDTH) {
		// too far right
		ball.x = SCREEN_WIDTH - ball.width;
		ball.flipXDirection();
	}
	if (ballCenterY + (ball.height/2) > SCREEN_HEIGHT) {
		// too far bottom
		--livesLeft;
		if (livesLeft != 0) {
			ball.reset(BALL_INIT_X, BALL_INIT_Y);
			paddle.reset(PAD_INIT_X, PAD_INIT_Y);
		}
	}
	if (ballCenterX - (ball.width/2) < 0) {
		// too far left
		ball.x = 0;
		ball.flipXDirection();
	}
	if (ballCenterY - (ball.height/2) < 0) {
		// too far top
		ball.y = 0;
		ball.flipYDirection();
	}
}

/**
* Method to reflect ball after collision with paddle
* @param diffX difference between center of ball and paddle along x-axis
*/
void SDLGraphicsProgram::getReflectionFromPaddle(float diffX) {
	// Make sure the hitx variable is within the width of the paddle
	if (diffX < 0) {
		diffX = 0;
	}

	float ballCenterX = ball.x + (ball.width * 0.5f);
	float paddleCenterX = paddle.x + (paddle.width * 0.5f);

	if ((ballCenterX >= (paddleCenterX - 6.0f)) &&
		(ballCenterX <= (paddleCenterX + 6.0f)))
	{
		// ball hit paddle on center +/- 6
		ball.setDirection(1, -1);
		ball.changeVelocityX(0);
	}
	else if (diffX < (paddle.width / 2))
	{
		// ball hit paddle on left of center
		ball.setDirection(-1, -1);
		ball.changeVelocityX(1);
	}
	else if(diffX > (paddle.width / 2))
	{
		// ball hit paddle on right of center
		ball.setDirection(1, -1);
		ball.changeVelocityX(1);
	}
	else
	{
		// ball hit paddle on center
		ball.setDirection(1, -1);
		ball.changeVelocityX(0);
	}
	
}

/**
* Method to handle collision of ball with paddle
*/
void SDLGraphicsProgram::CheckCollisionWithPaddle() {
	
	if (ball.Collides(&paddle))
	{
		float ballXCenter = ball.x + (ball.width / 2);
		getReflectionFromPaddle(ballXCenter - paddle.x);
	}
}

/**
* Method to handle collision of ball with bricks
* @return True if collision happens
*/
bool SDLGraphicsProgram::CheckCollisionWithBricks() {

	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		for (int j = 0; j < BRICKS_IN_A_ROW; j++)
		{
			// Check if brick is not hit
			if (!bricks[i][j].hit && bricks[i][j].getSelected())
			{
				// Brick x and y coordinates
				float brickX = bricks[i][j].x;
				float brickY = bricks[i][j].y;

				// Center of the ball
				float ballCenterX = ball.x + 0.5f*ball.width;
				float ballCenterY = ball.y + 0.5f*ball.height;

				// Center of the brick x and y coordinates
				float brickCenterX = brickX + 0.5f*BRICK_WIDTH;
				float brickCenterY = brickY + 0.5f*BRICK_HEIGHT;

				// detect collision
				if (ball.Collides(&bricks[i][j]))
				{
					// Collision detected, remove the brick

					// Set brick hit to be true so that it gets removed
					bricks[i][j].hit = true;
					numberOfBricks--;

					// collision detected increase score
					score = score + 10;

					// Determine which edge of brick got hit by ball
					int side = getContactEdge(&bricks[i][j]);
					return true;
				}
			}
		}
	}
	return false;
}

/**
* Method to reflect ball after collision with paddle
* @param &brick pointer to the brick object
* @return edge which got hit (1=top,2=right,3=bottom,4=left)
*/
int SDLGraphicsProgram::getContactEdge(GameObject* brick)
{
	// Considering ABCD is brick(rectangle), we will use sweep lines methods to determine which edge ball hit
	// Method will return following values corresponding to edges
	// 1 for top edge
	// 2 for right edge
	// 3 for bottom edge
	// 4 for left edge

	// upper left corner
	Point brickA, brickB, brickC, brickD, ballCenter;
	brickA.x = brick->x;
	brickA.y = brick->y;

	// upper right corner
	brickB.x = brick->x + BRICK_WIDTH;
	brickB.y = brick->y;

	// bottom right corner
	brickC.x = brick->x + BRICK_WIDTH;
	brickC.y = brick->y + BRICK_HEIGHT;

	// bottom left corner
	brickD.x = brick->x;
	brickD.y = brick->y + BRICK_HEIGHT;

	ballCenter.x = ball.x + (ball.width / 2);
	ballCenter.y = ball.y + (ball.height / 2);


	bool isAboveAC = isUpperSideOfLine(&brickC, &brickA, &ballCenter);
	bool isAboveBD = isUpperSideOfLine(&brickB, &brickD, &ballCenter);

	if (isAboveAC)
	{
		if (isAboveBD)
		{
			//top edge has intersected
			ball.flipYDirection();
			return 1;
		}
		else
		{
			//right edge intersected
			ball.flipXDirection();
			return 2;
		}
	}
	else
	{
		if (isAboveBD)
		{
			//left edge has intersected
			ball.flipXDirection();
			return 4;
		}
		else
		{
			//bottom edge intersected
			ball.flipYDirection();
			return 3;
		}
	}
}

/**
* Method to determine whether ball center is above or below line between corner1 and corner2
* @param corner1 Point containing x,y coordinate of one corner of the line
* @param corner2 Point containing x,y coordinate of another corner of the line
* @param ballCenter Point containing x,y coordinate of center of the ball
* @return True if above False else
*/
bool SDLGraphicsProgram::isUpperSideOfLine(Point* corner1, Point* corner2, Point* ballCenter)
{
	return ((corner2->x - corner1->x) * (ballCenter->y - corner1->y) - (corner2->y - corner1->y) * (ballCenter->x - corner1->x)) > 0;
}

/**
* Method to render shapes on the screen
*/
void SDLGraphicsProgram::render() {
	//SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
	if (gameOver) {
		if (quitTime + 3000 > SDL_GetTicks()) {
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			renderMessage(level, 'g', getSDLRenderer());
		}
		else if (quitTime + 3000 < SDL_GetTicks()) {
			mainMenu = true;
			gameOver = false;
			menu.reset();
			reset();
		}
	}
	else if (congrats) {
		if (congTime + 3000 > SDL_GetTicks()) {
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			renderMessage(maxLevels, 'c', getSDLRenderer());
		}
		else if (congTime + 3000 < SDL_GetTicks() && (congTime + 6000) > SDL_GetTicks()) {
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			renderMessage(level, 'w', getSDLRenderer());
		}
		else{
			mainMenu = true;
			congrats = false;
			menu.reset();
			reset();
		}
	}
	else {

		if (levelComplete && lastTime && (lastTime + 3000 > SDL_GetTicks())) {
			renderMessage(level - 1, 'c', getSDLRenderer());
			//unsigned int lastTime = 0, currentTime;
			//lastTime = SDL_GetTicks();
			//while (SDL_GetTicks() < lastTime + 3000) {
			//}
			//levelComplete = false;
			startTime = SDL_GetTicks();
		}
		else if (levelStart && startTime && (startTime + 3000 > SDL_GetTicks())) {
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			renderMessage(level, 's', getSDLRenderer());
		}
		else {
			lastTime = NULL;
			startTime = NULL;
			levelComplete = false;
			levelStart = false;
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			//Text's texture rendering
			lives.render(getSDLRenderer(), 0, 0);
			scores.render(getSDLRenderer(), 825, 0);
			levels.render(getSDLRenderer(), 450, 0);
			//resultOfGame.render(getSDLRenderer(),x,y);

			for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
				for (int j = 0; j < BRICKS_IN_A_ROW; ++j) {
					bricks[i][j].render(getSDLRenderer());
				}
			}

			paddle.render(getSDLRenderer());
			ball.render(getSDLRenderer());

		}
	}
	
	SDL_RenderPresent(gRenderer);
}


/**
* Method to loop continuously
*/
void SDLGraphicsProgram::loop() {
	// Main loop flag
	// If this is quit = 'true' then the program terminates.
	
	// Event handler that handles various events in SDL
	// that are related to input and output
	SDL_Event e;

	
	//The frames per second timer
	LTimer fpsTimer;

	//The frames per second cap timer
	LTimer capTimer;

	//In memory text stream
	std::stringstream timeText;

	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	// Enable text input
	SDL_StartTextInput();

	int max = 5;
	
	renderBGIMG(getSDLRenderer());
	
	//Load the music
	// Given credits to https://www.bensound.com 
	music = r.loadSound("Assets/musics/bensound-anewbeginning.wav");
	if (music == NULL)
	{
		SDL_Log("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
	}
	// While application is running
	while (!quit) {

		char key_press = 'a';

		//Start cap timer
		capTimer.start(); 

		if (numberOfBricks == 0) {
			if (level == 0)
			{
				paddle.reset(PAD_INIT_X, PAD_INIT_Y);
				ball.reset(BALL_INIT_X, BALL_INIT_Y);
				createLevel(0, 4);
			}
			else if (level <= maxLevels-1)
			{	
				levelComplete = true;
				lastTime = SDL_GetTicks();
				paddle.reset(PAD_INIT_X, PAD_INIT_Y);
				ball.reset(BALL_INIT_X, BALL_INIT_Y);
				createLevel(max-level, 6);
				levelStart = true;

			}
			else
			{
				if (!congrats) {
					congrats = true;
					congTime = SDL_GetTicks();
				}
				
			}
			level++;
		}
		

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User posts an event to quit
			// An example is hitting the "x" in the corner of the window.
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					key_press = 'l';
					break;

				case SDLK_RIGHT:
					key_press = 'r';
					break;

				case SDLK_a:
					key_press = 'l';
					break;

				case SDLK_d:
					key_press = 'r';
					break;

				case SDLK_SPACE:
					key_press = ' ';
					if (Mix_PlayingMusic() == 0)
					{
						//Play the music
						Mix_PlayMusic(music, -1);
					}
					break;

				case SDLK_UP:
					key_press = 'u';
					break;

				case SDLK_DOWN:
					key_press = 'd';
					break;

				case SDLK_KP_ENTER:
					key_press = 'e';
					break;

				case SDLK_RETURN:
					key_press = 'e';
					break;

				case SDLK_BACKSPACE:
					key_press = 'b';
					break;

				case SDLK_q:
					quit = true;
					break;

				default:
					break;
				}
			}
		}

		
		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		if (mainMenu) {
			levelStart = false;
			levelComplete = false;
			menu.update(key_press);
			if (menu.getStartStatus()) 
			{
				mainMenu = false;
				levelStart = true;
				startTime = SDL_GetTicks();
			}
			if (menu.getQuitStatus()) {
				quit = false;
				break;
			}
			if (menu.getLang()) {
				mainMenu = false;
				langMenu = true;
				menu.reduceArrowY(2);
			}
			if (menu.getCred()) {
				cred.setFlag();
				mainMenu = false;
				cred.setMainMenu(false);
				credMenu = true;
			}
			if (menu.getInst()) {
				inst.setFlag();
				mainMenu = false;
				inst.setMainMenu(false);
				instMenu = true;
			}
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			menu.render(getSDLRenderer());
			SDL_RenderPresent(gRenderer);
		}
		else if (langMenu) {
			menu.updateLang(key_press);
			char c = menu.getLangChosen();
			if (c == 'e' || c == 'f')
				langChosen = c;
			SDL_RenderClear(gRenderer);
			cred.setLang(langChosen);
			inst.setLang(langChosen);
			renderBGIMG(getSDLRenderer());
			menu.renderLang(getSDLRenderer());
			SDL_RenderPresent(gRenderer);
			mainMenu = menu.getMainMenu();
			langMenu = menu.getLang();
		}
		else if (credMenu) {
			cred.update(key_press);
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			cred.render(getSDLRenderer());
			SDL_RenderPresent(gRenderer);
			mainMenu = cred.getMainMenu();
			credMenu = cred.getFlag();
			if (credMenu == false)
				menu.setCred(false);
		}
		else if (instMenu) {
			inst.update(key_press);
			SDL_RenderClear(gRenderer);
			renderBGIMG(getSDLRenderer());
			inst.render(getSDLRenderer());
			SDL_RenderPresent(gRenderer);
			mainMenu = inst.getMainMenu();
			instMenu = inst.getFlag();
			if (instMenu == false)
				menu.setInst(false);
		}
		else
		{

			if (livesLeft != 0) {
				// Update our scene
				update(key_press);
			}
			else if(gameOver == false){
				gameOver = true;
				quitTime = SDL_GetTicks();
			}
			// Render using OpenGL
			if (!mainMenu)
				render();
		}
		//Update screen of our specified window
		SDL_GL_SwapWindow(getSDLWindow());
		
		
		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}

	//Disable text input
	SDL_StopTextInput();
}

/**
* Method to return pointer to the window
*/
SDL_Window* SDLGraphicsProgram::getSDLWindow() {
	return gWindow;
}

/**
* Method to return pointer to the renderer
*/
SDL_Renderer* SDLGraphicsProgram::getSDLRenderer() {
	return gRenderer;
}

/**
* Method to randomly create brick orientations based on 
* @param level and
* @rows
*/
void SDLGraphicsProgram :: createLevel(int level, int rows) {
	int threshold = 9 - level;
	int rowThreshold = 9;
	srand(time(NULL));

	//Setup bricks
	float sum = 0;
	float yColumn = 50;
	constexpr int xoffset = 75;
	constexpr int yoffset = 50;
	numberOfBricks = 0;
	for (int i = 0; i < rows; ++i) {
		sum = 0;
		int n = rand() % 10;
		
		if (n <= rowThreshold)
		{
			for (int j = 0; j < BRICKS_IN_A_ROW; ++j) {
				int n = rand() % 10;
				bricks[i][j].init(sum, yColumn, getSDLRenderer());
				sum += xoffset;
				if (n <= threshold)
				{
					bricks[i][j].setSelected();
					numberOfBricks++;
				}
			}
		}
		else
		{
			for (int j = 0; j < BRICKS_IN_A_ROW; ++j) {
				int n = rand() % 10;
				bricks[i][j].init(sum, yColumn, getSDLRenderer());
				sum += xoffset;
			}
		}
		
		yColumn += yoffset;
	}

	for (int i = rows; i < NUMBER_OF_ROWS; i++)
	{
		sum = 0;
		for (int j = 0; j < BRICKS_IN_A_ROW; ++j) {
			int n = rand() % 10;
			bricks[i][j].init(sum, yColumn, getSDLRenderer());
			sum += xoffset;
		}
		yColumn += yoffset;
	}

	totalnumberofbricks = numberOfBricks;
}

/**
* Method to render messages during level transitions
* @param level indicates the level
* @param status indicates the status of the transition
*/

void SDLGraphicsProgram::renderMessage(int level, char status, SDL_Renderer* ren) {
	SDL_Texture* temp;
	char t[4];
	std::string mes;
	Dest.x = SCREEN_WIDTH / 2 - 120;
	Dest.y = SCREEN_HEIGHT / 2 - 40;
	Dest.w = 240;
	Dest.h = 60;
	if (status == 's') {
		switch (level) {
		case 0: 
			mes = "l1s";
			//strcpy_s(t,"l1s");
			break;
		case 1: 
			mes = "l1s";
			//strcpy_s(t, "l1s");
			break;
		case 2: 
			mes = "l2s";
			//strcpy_s(t, "l2s");
			break;
		case 3: 
			mes = "l3s";
			//strcpy_s(t, "l3s");
			break;
		case 4: 
			mes = "l4s";
			//strcpy_s(t, "l4s");
			break;
		case 5: 
			mes = "l5s";
			//strcpy_s(t, "l5s");
			break;
		}
	}
	if (status == 'c'){
		switch (level) {
		case 0: 
			mes = "l1c";
			//strcpy_s(t, "l1c");
			break;
		case 1: 
			mes = "l1c";
			//strcpy_s(t, "l1c");
			break;
		case 2: 
			mes = "l2c";
			//strcpy_s(t, "l2c");
			break;
		case 3: 
			mes = "l3c";
			//strcpy_s(t, "l3c");
			break;
		case 4: 
			mes = "l4c";
			//strcpy_s(t, "l4c");
			break;
		case 5: 
			mes = "l5c";
			//strcpy_s(t, "con");
			break;
		}
	}
	if (status == 'g') {
		mes = "gover";
		//strcpy_s(t, "gover");
	}
	if (status == 'w') {
		mes = "con";
	}

	std::string f = "f";

	if (langChosen == 'f')
		mes = f + mes;

	//const char* ms = mes.c_str();

	temp = tmap[mes];
	if (temp == NULL)
	{
	//	SDL_Log(mes);
	}
	SDL_RenderCopy(ren, temp, 0, &Dest);

}

/**
* Method to reset everything so that it loops back to main menu after game over or if the game is beaten
*/

void SDLGraphicsProgram::reset(){
	livesLeft = 3;
	level = 0;
	menu.reset();
	numberOfBricks = 0;
}
