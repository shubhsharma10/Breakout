\mainpage

## Breakout Game
 Breakout game (Assignmnet 1) created as part of CS 5850: Building Game Engine 

## Requirements
    - Windows 10 x64 system
    - Visual Studio 2017 C++ setup

## Game trailer
   https://youtu.be/yYMY9JZzALk

## Executable application link
   https://goo.gl/3VVntY

## Source code repo
    https://github.com/Spring18GameEngine/assignment-1-breakout-team10/tree/master/Part1

## Instructions for running visual studio application
   - Pull repo from link provided above 
   - Download SDL2_image, SDL2_ttf,SDL2,SDL2_mixer Visual Studio development libraries and include these in Visual studio project
   - Copy assets folder and keep it in same directory where executable file is generated 
   - Copy config folder and keep it in same directory where executable file is generated 
   - Now Build the solution and it should be running the game
   NOTE: Maximum number of levels allowed are 5

## Instructions for running executable
   - Pull zip file from link provided above
   - Extract zip file contents, it contains Config and Assets folder, dll and .exe
   - Config folder contains config.txt which can be edited to change number of levels in game
   - Double clicking the exe should run the game

## Postmortem
   - We mostly believe we could have written the code way better if we had at least an inkling of idea of what 'changes' Nolan would push upon us, as it was
	 our first time actually building a game. We wrote the code with best OOD practice just enough to accommodate the specifications in part 1. With part 2,
	 as we progressed further and further we began to realize the flaws in our design. For starters, the 'Manager' file that manages every aspect of the game
	 was getting too big for us to handle. It alone has about 1000 lines. We could have split the file into more smaller files and made it more modular.
   - We didn't figure out how to handle different screens in the game till a later stage of development. The main menu and language menu are in the same class.
     But we have different classes for the other screens. We would have liked if all the screens had a class of their own. But one problem with this is, the 
	 program flow will need to make use of a lot of boolean flags to keep track of who is in control and all these classes must have public methods to interact
     with the manager class. This could potentially lead the manager to go into a never ending loop. We don't think this is a huge problem if we keep good track 
	 of the various flags being switched on and off. 
   - We would definitely write a better 'render' function for the manager class. Right now, the render function is a mess. Initially, everything was rendered by the
     manager's render function. This seemed to work great but gives less control to us. Instead, we can have different classes for different screens (as mentioned
	 above) and call their render functions instead.
   - We are in general happy with the code we have written as we feel it is not too shabby. 

## Credits
   - Prem
   - Chandan
   - Shubham


