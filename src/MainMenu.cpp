#include "MainMenu.h"
#include <SDL_image.h>
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include <string>
#include "ResourceManager.h"
#include "LTexture.h"

/**
* Constructor for MainMenu class
*/
MainMenu::MainMenu(){
}

/**
* Destructor for MainMenu class
*/
MainMenu::~MainMenu() {

}

/**
* Method used to initialize main menu screen
* @param w width of screen
* @param h height of screen
* @param ren Renderer used to render screen
*/
void MainMenu::init(int w, int h,SDL_Renderer* ren) {

	arrowX = w / 2 - 100;
	arrowY = h / 2 - 117;

	startX = w / 2 - 60;
	startY = h / 2 - 130;

	insX = w / 2 - 60;
	insY = h / 2 - 60;

	langX = w / 2 - 60;
	langY = h / 2 + 10;

	credX = w / 2 - 60;
	credY = h / 2 + 80;

	quitX = w / 2 - 60;
	quitY = h / 2 + 150;

	engX = w / 2 - 60;
	engY = h / 2 - 130;

	frenchX = w / 2 - 60;
	frenchY = h / 2 - 60;

	backX = w / 2 - 60;
	backY = h / 2 + 10;
	

	gameStart = false;
	gameQuit = false;
	gameCred = false;
	gameLang = false;
	gameBack = false;
	mainMenu = false;
	langChosen = 'e';
	langArrow = 1;


	ResourceManager r = ResourceManager::instance();
	spriteSheet1 = r.load("Assets/images/arrow.png");
	spriteSheet2 = r.load("Assets/images/start.png");
	spriteSheet3 = r.load("Assets/images/quit.png");

	if (spriteSheet1 == NULL || spriteSheet2 == NULL || spriteSheet3 == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(spriteSheet1, SDL_TRUE, SDL_MapRGB(spriteSheet1->format, 255, 255, 255));
		texture1 = SDL_CreateTextureFromSurface(ren, spriteSheet1);
		SDL_SetColorKey(spriteSheet2, SDL_TRUE, SDL_MapRGB(spriteSheet2->format, 255, 255, 255));
		texture2 = SDL_CreateTextureFromSurface(ren, spriteSheet2);
		SDL_SetColorKey(spriteSheet3, SDL_TRUE, SDL_MapRGB(spriteSheet3->format, 255, 255, 255));
		texture3 = SDL_CreateTextureFromSurface(ren, spriteSheet3);
	}

	sprite = r.load("Assets/images/back.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		back = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/credits.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		cred = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/lang.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		lang = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/eng.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		eng = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/french.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		french = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/ins.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate ins surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		ins = SDL_CreateTextureFromSurface(ren, sprite);
	}

	fspriteSheet2 = r.load("Assets/images/fstart.png");
	fspriteSheet3 = r.load("Assets/images/fquit.png");

	if (spriteSheet1 == NULL || spriteSheet2 == NULL || spriteSheet3 == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(fspriteSheet2, SDL_TRUE, SDL_MapRGB(fspriteSheet2->format, 255, 255, 255));
		ftexture2 = SDL_CreateTextureFromSurface(ren, fspriteSheet2);
		SDL_SetColorKey(fspriteSheet3, SDL_TRUE, SDL_MapRGB(fspriteSheet3->format, 255, 255, 255));
		ftexture3 = SDL_CreateTextureFromSurface(ren, fspriteSheet3);
	}

	sprite = r.load("Assets/images/fback.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		fback = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/fcredits.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		fcred = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/flang.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		flang = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/feng.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		feng = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/ffrench.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		ffrench = SDL_CreateTextureFromSurface(ren, sprite);
	}

	sprite = r.load("Assets/images/fins.png");
	if (sprite == NULL) {
		SDL_Log("Failed to allocate ins surface");
	}
	else {
		//SDL_Log("Pointer allocated");
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 255, 255));
		fins = SDL_CreateTextureFromSurface(ren, sprite);
	}


}

/**
* Method used to render main menu screen
* @param ren Renderer used to render screen
*/
void MainMenu::render(SDL_Renderer* ren) {
	Dest.x = arrowX;
	Dest.y = arrowY;
	Dest.w = 30;
	Dest.h = 30;

	SDL_RenderCopy(ren, texture1, NULL, &Dest);

	if (langChosen == 'e') {

		Dest.x = startX;
		Dest.y = startY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, texture2, NULL, &Dest);

		Dest.x = langX;
		Dest.y = langY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, lang, NULL, &Dest);

		Dest.x = credX;
		Dest.y = credY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, cred, NULL, &Dest);

		Dest.x = insX;
		Dest.y = insY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, ins, NULL, &Dest);

		Dest.x = quitX;
		Dest.y = quitY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, texture3, NULL, &Dest);
	} 
	else if (langChosen == 'f') {
		Dest.x = startX;
		Dest.y = startY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, ftexture2, NULL, &Dest);

		Dest.x = langX;
		Dest.y = langY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, flang, NULL, &Dest);

		Dest.x = credX;
		Dest.y = credY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, fcred, NULL, &Dest);

		Dest.x = insX;
		Dest.y = insY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, fins, NULL, &Dest);

		Dest.x = quitX;
		Dest.y = quitY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, ftexture3, NULL, &Dest);
	}

}

/**
* Method used to update main menu screen based on key press
* @param c character passed based on key press
*/
void MainMenu::update(char c) {
	switch (c) {
	case 'u' : 
		if (arrowPointing != 1) {
			arrowY -= 70;
			arrowPointing--;
		}
		break;
	case 'd' :
		if (arrowPointing != 5) {
			arrowY += 70;
			arrowPointing++;
		}
		break;
	case 'e':
		if (arrowPointing == 1)
			gameStart = true;
		else if (arrowPointing == 2)
			gameIns = true;
		else if (arrowPointing == 3)
			gameLang = true;
		else if (arrowPointing == 4)
			gameCred = true;
		else if (arrowPointing == 5)
			gameQuit = true;
	}

	arrowY += hover;
	limit += hover;

	if (limit >= 4.0 || limit <= -4.0) {
		hover = -hover;
		limit = 0.0;
	}
	
}

/**
* Method used to select language out of all possible options
* @param c character passed based on key press
*/
void MainMenu::updateLang(char c) {
	mainMenu = false;
	switch (c) {
	case 'u':
		if (langArrow != 1) {
			arrowY -= 70;
			langArrow--;
		}
		break;
	case 'd':
		if (langArrow != 3) {
			arrowY += 70;
			langArrow++;
		}
		break;
	case 'e':
		if (langArrow == 1) {
			langChosen = 'e';
			mainMenu = true;
			gameLang = false;
			reduceArrowY(langArrow-1);
			langArrow = 1;
		}
		else if (langArrow == 2) {
			langChosen = 'f';
			mainMenu = true;
			gameLang = false;
			reduceArrowY(langArrow-1);
			langArrow = 1;
		}
		else if (langArrow == 3) {
			mainMenu = true;
			gameBack = true;
			gameLang = false;
			reduceArrowY(langArrow-1);
			langArrow = 1;
		}
		break;
	case 'b':
		mainMenu = true;
		gameBack = true;
		gameLang = false;
		reduceArrowY(langArrow - 1);
		langArrow = 1;
		break;
	}

	arrowY += hover;
	limit += hover;

	if (limit >= 4.0 || limit <= -4.0) {
		hover = -hover;
		limit = 0.0;
	}

}

/**
* Method used to render text
* @param s string to render
* @param x render at x coordinate
* @param y render at y coordinate
* @param ren Renderer used to render screen
*/
void MainMenu::renderText(std::string s, int x, int y, SDL_Renderer* ren) {
	LTexture str;
	SDL_Color textColor = { 255, 255, 255 };
	str.init(x, y);

	str.loadFromRenderedText(ren, s, textColor);
	str.render(ren, x, y);
}

/**
* Method used to get game start status
*/
bool MainMenu::getStartStatus() {
	return gameStart;
}

/**
* Method used to get game quit status
*/
bool MainMenu::getQuitStatus() {
	return gameQuit;
}

/**
* Method used to get status	of whether credit option is selected or not
*/
bool MainMenu::getCred() {
	return gameCred;
}

/**
* Method used to get status of language selected
*/
bool MainMenu::getLang() {
	return gameLang;
}

/**
* Method used to get status of whether we are on main menu screen or not
*/
bool MainMenu::getMainMenu() {
	return mainMenu;
}

/**
* Method used to get language selected
*/
char MainMenu::getLangChosen() {
	return langChosen;
}

/**
* Method used to get status of instruction viewed
*/
bool MainMenu::getInst() {
	return gameIns;
}

/**
* Method used to reset main menu to default setting
*/
void MainMenu::reset() {
	gameStart = false;
	gameQuit = false;
	mainMenu = false;
	gameCred = false;
	gameLang = false; 
	gameBack = false;
	gameIns = false;
	arrowPointing = 1;
	langArrow = 1;
}

/**
* Method used to render main menu screen in respective language
* @param ren Renderer used to render screen
*/
void MainMenu::renderLang(SDL_Renderer* ren) {
	Dest.x = arrowX;
	Dest.y = arrowY;
	Dest.w = 30;
	Dest.h = 30;

	SDL_RenderCopy(ren, texture1, NULL, &Dest);

	if (langChosen == 'e') {

		Dest.x = engX;
		Dest.y = engY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, eng, NULL, &Dest);

		Dest.x = frenchX;
		Dest.y = frenchY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, french, NULL, &Dest);

		Dest.x = backX;
		Dest.y = backY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, back, NULL, &Dest);
	}
	else if (langChosen == 'f') {
		Dest.x = engX;
		Dest.y = engY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, feng, NULL, &Dest);

		Dest.x = frenchX;
		Dest.y = frenchY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, ffrench, NULL, &Dest);

		Dest.x = backX;
		Dest.y = backY;
		Dest.w = 150;
		Dest.h = 60;

		SDL_RenderCopy(ren, fback, NULL, &Dest);

	}

}

/**
* Method used to reset arrow position
* @param n units by which arrow should be shifted
*/
void MainMenu::reduceArrowY(int n) {
	arrowY -= n * 70;
	arrowPointing = 1;
}

/**
* Method used to set status	of credit option
* @param v true if credit option is selected
*/
void MainMenu::setCred(bool v) {
	gameCred = v;
}

/**
* Method used to set status	of instruction option
* @param v true if instruction option is selected
*/
void MainMenu::setInst(bool v) {
	gameIns = v;
}