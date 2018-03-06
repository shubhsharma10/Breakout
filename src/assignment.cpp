// Support Code written by Michael D. Shah
// Last Updated: 1/21/17
// Please do not redistribute without asking permission.
#define SDL_MAIN_HANDLED
#include "ManagerHeader.h"
#include "GameObject.h"
#include "ResourceManager.h"

/**
* Main function of Game
* @param argc number of arguments
* @param argv input array of arguments
*/
int main(int argc, char* argv[]) {

	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Run our program forever
	mySDLGraphicsProgram.loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
