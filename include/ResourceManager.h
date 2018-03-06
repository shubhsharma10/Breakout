#ifndef ResourceManager_h
#define ResourceManager_h
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>

class ResourceManager {
private:
	/**
	* Hashmap used to keep track of Images where path to image is key and its Spritesheet is value
	*/
    static std::map<const char*, SDL_Surface*> map;

	/**
	* Hashmap used to keep track of fonts where path to font is key and its TTF_Font class is value
	*/
	static std::map<const char*, TTF_Font*> fontMap;

	/**
	* Hashmap used to keep track of musics where path to music is key and its Mix_Music class is value
	*/
	static std::map<const char*, Mix_Music*> soundMap;

	/**
	* Constructor of Resource Manager class
	*/
    ResourceManager() {}
    
public:
	/**
	* Method used to get instance of Resource Manager class
	* @return static instance of Resource Manager class
	*/
	static ResourceManager& instance();

	/**
	* Method used to load Spritesheet of Images from their path
	* @param filePath path where image is stored
	* @return Spritesheet of respective image
	*/
	SDL_Surface* load(const char* filePath);

	/**
	* Method used to load TTF_Font object of respective font from its path
	* @param filePath path where font is stored
	* @return TTF_Font object of respective font
	*/
	TTF_Font* loadFont(const char* filePath);

	/**
	* Method used to load Mix_Music object of respective music from its path
	* @param filePath path where music is stored
	* @return Mix_Music object of respective music
	*/
	Mix_Music* loadSound(const char* filePath);

	/**
	* Method used to create(initialize) hashmap for images
	*/
	static std::map<const char*, SDL_Surface*> createMap();

	/**
	* Method used to create(initialize) hashmap for fonts
	*/
	static std::map<const char*, TTF_Font*> createFontMap();

	/**
	* Method used to create(initialize) hashmap for sounds
	*/
	static std::map<const char*, Mix_Music*> createSoundMap();
	
    
};
#endif /* ResourceManager_h */
