#include <iostream>
#include <stdexcept>
#include <limits>

#include "PlayingCards.h"
#include "Menu.h"


#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)

//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/

#endif


int main()
{

    #if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
    #endif // _MSC_VER


    setlocale(LC_ALL, "en_US.utf8");

    #ifdef __APPLE__
    std::wcout.imbue(std::locale("en_US.UTF-8"));    //wcout works correctly with this command on OS X
    #endif


    PlayingCards* pc = nullptr;
    start_menu_for_playing_cards(pc);                 //start a dialogue menu with empty deck

    delete pc;
    return 0;
}

