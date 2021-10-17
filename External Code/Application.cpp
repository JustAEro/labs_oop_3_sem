#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DynSet.h"
#include "SetTheoryProblems.h"
#include "Menu.h"


//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS

	SetTheoryProblems obj;
	start_menu(obj);

	return 0;
}