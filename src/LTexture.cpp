#include "LTexture.h"
#include "ResourceManager.h"

/**
* Constructor of LTexture class
*/
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 75;
	mHeight = 50;
}

/**
* Destructor for LTexture class
*/
LTexture::~LTexture()
{
	//Deallocate
	free();
}

/**
* Method to initialize of width and height
* @param w width of texture
* @param h height of texture
*/
void LTexture::init(int w, int h)
{
	mWidth = w;
	mHeight = h;
}

/**
* Deallocates texture
*/
void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

/**
* Method to render texture at given point
* @param ren instance of SDL_Renderer
* @param x x-coordinate where texture will be rendered
* @param y y-coordinate where texture will be rendered
*/
void LTexture::render(SDL_Renderer* ren,int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(ren, mTexture, NULL, &renderQuad);
}

/**
* Method to get width of texture
*/
int LTexture::getWidth()
{
	return mWidth;
}

/**
* Method to get height of texture
*/
int LTexture::getHeight()
{
	return mHeight;
}

/**
* Method to Create image from font string
* @param ren instance of SDL_Renderer
* @param textureText text to be converted into texture
* @param textColor color configurations of text
* @return true if texture is created from text
*/
bool LTexture::loadFromRenderedText(SDL_Renderer* ren, std::string textureText, SDL_Color textColor)
{
	TTF_Font *gFont = NULL;
	ResourceManager r = ResourceManager::instance();
	gFont = r.loadFont("Assets/fonts/arial.ttf");
	if (gFont == NULL)
		SDL_Log("Failed to allocate font");
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor); 

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}