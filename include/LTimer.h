#ifdef LINUX
#include <SDL2/SDL.h>
#else // This works for Mac and Linux
#include <SDL.h>
#endif

class LTimer
{
public:
	/**
	* Constructor of LTimer class
	*/
	LTimer();

	/**
	* Start clock action
	*/
	void start();

	/**
	* stop clock action
	*/
	void stop();

	/**
	* Pause clock action
	*/
	void pause();

	/**
	* Unpause clock action
	*/
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	/**
	* Checks the started status of the timer
	*/
	bool isStarted();

	/**
	* Checks the paused status of the timer
	*/
	bool isPaused();

private:
	/**
	* The clock time when the timer started
	*/
	Uint32 mStartTicks;

	/**
	* The ticks stored when the timer was paused
	*/
	Uint32 mPausedTicks;

	/**
	* The paused timer status
	*/
	bool mPaused;

	/**
	* The started timer status
	*/
	bool mStarted;
};
