//main function of the application program is here


//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/

#include <iostream>
#include "..\Library\Hypocycloid.h"
#include "Menu.h"
#include "tchar.h"

int _tmain(int argc, _TCHAR* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS

    Hypocycloid* hp = nullptr;
    start_menu(hp);                 //start a dialogue menu with empty hypocycloid

    delete hp;
    return 0;
}

