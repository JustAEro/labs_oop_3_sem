// Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../Library/PlayingCards.h"
#include <tchar.h>


//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/

#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int _tmain(int argc, _TCHAR* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
    _setmode(_fileno(stdout), _O_U16TEXT);


    PlayingCards pc(20);
    VectorOfCards vec = pc.subGroupOfSameSuit(Suits::Diamonds);

   
    for (int i = 0; i < vec.size; ++i)
    {
        std::wcout << vec.vector[i];
    }
    std::wcout << std::endl;

    delete[] vec.vector;
   

    std::wcout << pc << std::endl;

    pc.sort();
    std::wcout << "The sorted one:" << std::endl;
    std::wcout << pc;

    //pc.print();
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
