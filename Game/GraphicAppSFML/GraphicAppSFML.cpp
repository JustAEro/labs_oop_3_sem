#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/
#endif


#include "Game.h"



int main()
{
	#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
	#endif

	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	//Game loop
	while (game.getWindowIsOpen())
	{
		//Update your game
		game.update();

		//Render
		game.render();
	}

	//End of app
	return 0;
}