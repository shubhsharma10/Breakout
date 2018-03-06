#pragma once

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Texture wrapper class
class LTexture
{
public:
	/**
	* Constructor of LTexture class
	*/
	LTexture();

	/**
	* Destructor for LTexture class
	*/
	~LTexture();

	/**
	* Method to Create image from font string
	* @param ren instance of SDL_Renderer
	* @param textureText text to be converted into texture
	* @param textColor color configurations of text
	* @return true if texture is created from text
	*/
	bool loadFromRenderedText(SDL_Renderer* ren, std::string textureText, SDL_Color textColor);

	/**
	* Deallocates texture
	*/
	void free();

	/**
	* Method to render texture at given point
	* @param ren instance of SDL_Renderer
	* @param x x-coordinate where texture will be rendered
	* @param y y-coordinate where texture will be rendered
	*/
	void render(SDL_Renderer* ren, int x, int y);

	/**
	* Method to initialize of width and height
	* @param w width of texture
	* @param h height of texture
	*/
	void init(int w, int h);

	/**
	* Method to get width of texture
	*/
	int getWidth();

	/**
	* Method to get height of texture
	*/
	int getHeight();

private:
	/**
	* The actual hardware texture
	*/
	SDL_Texture * mTexture;

	/**
	* Image dimensions
	*/
	int mWidth;
	int mHeight;
};
