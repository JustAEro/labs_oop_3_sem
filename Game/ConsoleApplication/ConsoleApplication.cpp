// ConsoleApplication.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../MilitaryConvoy/Mission/Mission.h"
#include "../MilitaryConvoy/CustomMap.h"

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
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
	#endif

	Mission mission;
	for (int i = 0; i < 10; ++i)
	{
		mission.createBattlePirateShip();
	}

	BinaryTree<int, std::string> tree;
	
	tree.insert(std::make_pair(5, "we"));
	tree.insert(std::make_pair(6, "th"));
	tree.insert(std::make_pair(4, "dvc"));
	tree.insert(std::make_pair(10, "lph"));
	tree.insert(std::make_pair(3, "nv"));

	tree.draw();
	std::cout << "Count = " << tree.getCount() << "\n";


	std::cout << "\n\n\n";
	BinaryTree<int, std::string> treeCopy(tree);
	treeCopy.draw();
	std::cout << "Count = " << treeCopy.getCount() << "\n";



	std::cout << "\n\n\n";

	tree.remove(5);
	tree.draw();


	std::cout << "\n\n\n";
	BinaryTree<int, std::string> treeCopy2(tree);
	treeCopy2.draw();
	std::cout << "Count = " << treeCopy2.getCount() << "\n";
	std::cout << "Copy2 of tree\n";


	tree = treeCopy2;
	std::cout << "\n\n\n" << "Old tree after assignment to 2 copy\n";
	tree.draw();
	std::cout << "Count = " << tree.getCount() << "\n";


	tree = treeCopy;
	std::cout << "\n\n\n" << "Old tree after assignment to 1 copy\n";
	tree.draw();
	std::cout << "Count = " << tree.getCount() << "\n";


	CustomMap<int, std::string> map;
	for (int i = 0; i < 10; ++i)
	{
		map.insert(std::make_pair(i, "str"));
	}
	for (const auto& el : map)
	{
		std::cout << "(" << el.first << ", " << el.second << ")\n";
	}


	std::cout << "\nCopy 1 of map\n";
	auto mapCopy(map);
	for (const auto& el : mapCopy)
	{
		std::cout << "(" << el.first << ", " << el.second << ")\n";
	}

	std::cout << "\nMove of copy 1 of map\n";
	auto moveCopy(std::move(mapCopy));
	for (const auto& el : moveCopy)
	{
		std::cout << "(" << el.first << ", " << el.second << ")\n";
	}


    std::cout << "\nHello World!\n";
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
