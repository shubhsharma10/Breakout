#include "GameObject.h"
#include <string>
using namespace std;

/**
*	A header file for Ball class
*/
class Ball : public GameObject{

public:
	/**
	* Creates an object of Ball class
	*/
	Ball();

	/**
	* Destructor for Ball class
	*/
	~Ball();

	/**
	* Method to initialize private variables(data) of Ball class
	* @param xpo x-coordinate of ball
	* @param ypo y-coordinate of ball
	* @param vx1 velocity of ball along x-axis
	* @param vy1 velocity of ball along y-axis
	* @param screenW screen width
	* @param ren object of SDL_Renderer, used to render ball on screen
	*/
	void init(int xpo, int ypo, int vx1, int vy1, int screenW, SDL_Renderer* ren);

	/**
	* Method used to render ball on screen
	*/
	void render(SDL_Renderer* ren);

	/**
	* Method used to update position and direction of ball
	* @param key it is used to identify direction in which we should move ball when its stationary
	*/
	void update(char key);

	/**
	* Method used to check whether ball is stationary or not
	* @return True if ball is stationary
	*/
	bool isBallStationary();

	/**
	* Method used to set direction of ball
	* @param dx direction of ball along x-axis
	* @param dy direction of ball along y-axis
	*/
	void setDirection(int dx, int dy);

	/**
	* Method used to update position of ball based on its direction and velocity
	*/
	void updatePos();

	/**
	* Method used to update velocity of ball along x-axis
	* @param newVx new velocity of ball along x-axis
	*/
	void changeVelocityX(int newVx);

	/**
	* Method used to update velocity of ball along y-axis
	* @param newVy new velocity of ball along y-axis
	*/
	void changeVelocityY(int newVy);

	/**
	* Method used to flip movement of ball along y-axis
	*/
	void flipYDirection();

	/**
	* Method used to flip movement of ball along x-axis
	*/
	void flipXDirection();

	/**
	* Method used to reset position of ball to default configurations
	* @param ix change x-coordinate of ball to ix
	* @param iy change y-coordinate of ball to iy
	*/
	void reset(int ix, int iy);

private:
	/**
	* Velocity of ball along x-axis and y-axis
	*/
	int vx, vy;

	/**
	* Direction of ball along x-axis and y-axis
	*/
	int dirX, dirY;

	/**
	* Width of scrren
	*/
	int screenWidth;

	/**
	* Used to move ball along x-axis by l unit
	*/
	int l = -5;

	/**
	* Used to move ball along x-axis by r unit
	*/
	int r = 5;

	/**
	* Spritesheet of ball
	*/
	SDL_Surface *spriteSheet;

	/**
	* Texture obtained from ball image
	*/
	SDL_Texture *texture;

	/**
	* Destination rectangle where ball should be rendered on screen
	*/
	SDL_Rect Dest;

	/**
	* Source rectangle from where ball is rendered on screen
	*/
	SDL_Rect Src;

	/**
	* Used to store whether ball is stationary or not
	*/
	bool ballStationary = true;

	/**
	* 1 - Up, 2- Down, 3- Left, 4- Right for now
	*/
	int direction = 1;
};

