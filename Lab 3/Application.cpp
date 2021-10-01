// Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <limits>

#include "PlayingCards.h"
#include "Menu.h"

//+= , ++, [], exceptions->errors, vector->new object, universal unicode


#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)

//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/

#endif


int main(int argc, wchar_t* argv[])
{

    #if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
    #endif // _MSC_VER


    setlocale(LC_ALL, "en_US.utf8");
    //_setmode(_fileno(stdout), _O_U16TEXT);


    PlayingCards* pc = nullptr;
    start_menu_for_playing_cards(pc);                 //start a dialogue menu with empty deck

    delete pc;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
