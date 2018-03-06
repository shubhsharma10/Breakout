#include <Credit.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include "ResourceManager.h"
#include <fstream>

/**
* Constructor of Credit class
*/
Credit::Credit(){
}

/**
* Destructor of Credit class
*/
Credit::~Credit() {

}

/**
* Method to initialize private variables(data) of Credit class
* @param ren object of SDL_Renderer, used to render Credit screen
*/
void Credit::init(SDL_Renderer* ren) {
	SDL_Color textColor = { 0, 0, 0 };

	for (int i = 0; i < 10; i++)
		eText[i].init(75, 50);
	for (int i = 0; i < 10; i++)
		fText[i].init(75, 50);

	
	const char* path;

	lang = 'e';


	//Read file line by line and store it in an array
	path = "Assets/languages/English.txt";

	std::ifstream infile(path);
	std::string line;
	int count = 0;
	while (std::getline(infile, line))
	{
		etxt[count] = line;
		count++;
	}
	for(int i=0; i<5; i++)
		eText[i].loadFromRenderedText(ren, etxt[6+i], textColor);

	path = "Assets/languages/French.txt";
	std::ifstream nfile(path);
	count = 0;
	while (std::getline(nfile, line))
	{
		ftxt[count] = line;
		count++;
	}
	for (int i = 0; i<5; i++)
		fText[i].loadFromRenderedText(ren, ftxt[6 + i], textColor);
}

/**
* Method used to render Credit screen
*/
void Credit::render(SDL_Renderer* ren) {
	int space = 80;

	if (lang == 'e') {
		for (int i = 0; i < 5; i++) {
			eText[i].render(ren, 0, space*i);
		}
	}

	if (lang == 'f') {
		for (int i = 0; i < 5; i++) {
			fText[i].render(ren, 0, space*i);
		}
	}
}

/**
* Method used to update whether we are working with credit screen or not
* @param key boolean to check whether back key is pressed or not
*/
void Credit::update(char key) {
	if (key == 'b') {
		mainMenu = true;
		flag = false;
	}
}

/**
* Method used to set language in which credit screen should be rendered
* @param c set language variable as passed parameter
*/
void Credit::setLang(char c) {
	lang = c;
}

/**
* Method used to get status of credit screen
*/
bool Credit::getFlag() {
	return flag;
}

/**
* Method used to set status of credit screen
*/
void Credit::setFlag() {
	flag = true;
}

/**
* Method used to return false if we are working with credit screen and true if we are done working on credit screen
*/
bool Credit::getMainMenu() {
	return mainMenu;
}

/**
* Method used to set status for main menu
* @param v set mainmenu variable with passed parameter
*/
void Credit::setMainMenu(bool v) {
	mainMenu = v;
}