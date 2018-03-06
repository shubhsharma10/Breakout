#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

/**
* Method used to get instance of Resource Manager class
* @return static instance of Resource Manager class
*/
ResourceManager& ResourceManager::instance() {
	static ResourceManager *instance = new ResourceManager();
	return *instance;
}

/**
* Method used to load Spritesheet of Images from their path
* @param filePath path where image is stored
* @return Spritesheet of respective image
*/
SDL_Surface* ResourceManager::load(const char* filePath) {
	if (map.find(filePath) != map.end()) {
		return map.at(filePath);
	}
	else {
		// create resource
		SDL_Surface* spriteSheet = IMG_Load(filePath);
		// store in dict
		map[filePath] = spriteSheet;
		if (map[filePath] == NULL)
			SDL_Log("Failed to insert into map %c", filePath);
		return spriteSheet;
	}
}

/**
* Method used to load TTF_Font object of respective font from its path
* @param filePath path where font is stored
* @return TTF_Font object of respective font
*/
TTF_Font* ResourceManager::loadFont(const char* filePath) {
	if (fontMap.find(filePath) != fontMap.end()) {
		return fontMap.at(filePath);
	}
	else {
		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}
		// create resource
		TTF_Font* font = TTF_OpenFont(filePath, 16);
		// store in dict
		fontMap.insert({filePath, font });
		if (fontMap.at(filePath) != font)
			SDL_Log("Failed to insert into map %c", filePath);
		return font;
	}
}

/**
* Method used to load Mix_Music object of respective music from its path
* @param filePath path where music is stored
* @return Mix_Music object of respective music
*/
Mix_Music* ResourceManager::loadSound(const char* filePath) {
	if (soundMap.find(filePath) != soundMap.end()) {
		return soundMap.at(filePath);
	}
	else {
		// create resource
		Mix_Music* sound = Mix_LoadMUS(filePath);
		// store in dict
		soundMap[filePath] = sound;
		return sound;
	}
}

/**
* Method used to create(initialize) hashmap for images
*/
std::map<const char*, SDL_Surface*> ResourceManager::createMap() {
	char t[] = "abc";
	const char *temp = "abc";

	SDL_Surface* tsur = IMG_Load("Assets/images/brick_violet_small.png");
	std::map<const char*, SDL_Surface*> tmap;
	tmap[temp] = tsur;
	return tmap;
}

/**
* Method used to create(initialize) hashmap for fonts
*/
std::map<const char*, TTF_Font*> ResourceManager::createFontMap() {
	char t[] = "abc";
	const char *temp = "abc";

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	TTF_Font* tfont = TTF_OpenFont("Assets/fonts/arial.ttf", 16);

	if (!tfont) {
		SDL_Log("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	std::map<const char*, TTF_Font*> tmap;
	tmap[temp] = tfont;
	return tmap;
}

/**
* Method used to create(initialize) hashmap for sounds
*/
std::map<const char*, Mix_Music*> ResourceManager::createSoundMap() {
	char t[] = "abc";
	const char *temp = "abc";

	Mix_Music* tsound = Mix_LoadMUS("Assets/musics/bensound-anewbeginning.wav");
	std::map<const char*, Mix_Music*> tmap;
	tmap[temp] = tsound;
	return tmap;
}

/**
* Hashmap used to keep track of Images where path to image is key and its Spritesheet is value
*/
std::map<const char*, SDL_Surface*> ResourceManager::map = ResourceManager::createMap();

/**
* Hashmap used to keep track of fonts where path to font is key and its TTF_Font class is value
*/
std::map<const char*, TTF_Font*> ResourceManager::fontMap = ResourceManager::createFontMap();

/**
* Hashmap used to keep track of musics where path to music is key and its Mix_Music class is value
*/
std::map<const char*, Mix_Music*> ResourceManager::soundMap = ResourceManager::createSoundMap();



