#include <Instructions.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include "ResourceManager.h"
#include <fstream>

/**
* Constructor of Instruction class
*/
Instruction::Instruction() {
}

/**
* Destructor of Instruction class
*/
Instruction::~Instruction() {

}

/**
* Method to initialize private variables(data) of Instruction class
* @param ren object of SDL_Renderer, used to render Instruction screen
*/
void Instruction::init(SDL_Renderer* ren) {
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
	for (int i = 0; i<8; i++)
		eText[i].loadFromRenderedText(ren, etxt[11 + i], textColor);

	path = "Assets/languages/French.txt";
	std::ifstream nfile(path);
	count = 0;
	while (std::getline(nfile, line))
	{
		ftxt[count] = line;
		count++;
	}
	for (int i = 0; i<8; i++)
		fText[i].loadFromRenderedText(ren, ftxt[11 + i], textColor);
}

/**
* Method used to render Instruction screen
*/
void Instruction::render(SDL_Renderer* ren) {
	int space = 60;

	if (lang == 'e') {
		for (int i = 0; i < 8; i++) {
			eText[i].render(ren, 0, space*i);
		}
	}

	if (lang == 'f') {
		for (int i = 0; i < 8; i++) {
			fText[i].render(ren, 0, space*i);
		}
	}
}

/**
* Method used to update whether we are working with Instruction screen or not
* @param key boolean to check whether back key is pressed or not
*/
void Instruction::update(char key) {
	if (key == 'b') {
		mainMenu = true;
		flag = false;
	}
}

/**
* Method used to set language in which Instruction screen should be rendered
* @param c set language variable as passed parameter
*/
void Instruction::setLang(char c) {
	lang = c;
}

/**
* Method used to get status of Instruction screen
*/
bool Instruction::getFlag() {
	return flag;
}

/**
* Method used to set status of Instruction screen
*/
void Instruction::setFlag() {
	flag = true;
}

/**
* Method used to return false if we are working with Instruction screen and true if we are done working on Instruction screen
*/
bool Instruction::getMainMenu() {
	return mainMenu;
}

/**
* Method used to set status for main menu
* @param v set mainmenu variable with passed parameter
*/
void Instruction::setMainMenu(bool v) {
	mainMenu = v;
}