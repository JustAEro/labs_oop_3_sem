// Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "..\Library\Hypocycloid.h"
#include "tchar.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Hypocycloid hp;
    double rad1, rad2, dist;
    bool flag_exit_from_program = false;

    while (!flag_exit_from_program)
    {
        std::cout << "Your hypocycloid is:" << std::endl;
        std::cout << "The type of your hypocicloid is: ";
       
        Hypocycloid::Types type = hp.type();
        if (type == Hypocycloid::Types::SIMPLE) 
        {
            std::cout << "simple" << std::endl;
        }
        else if (type == Hypocycloid::Types::LONG)
        {
            std::cout << "long" << std::endl;
        }
        else
        {
            std::cout << "short" << std::endl;
        }

        std::cout << "Radius of big circle: " << hp.getRadiusBig() << std::endl;
        std::cout << "Radius of small circle: " << hp.getRadiusSmall() << std::endl;
        std::cout << "Distance from center of small circle to rolling point: " << hp.getDistance() << std::endl;
;

        bool flag_wrong_parameter = false;

        while (!flag_wrong_parameter)
        {
            std::cout << "Enter angle t in radians to calculate curve radius of t, hypocycloid point of t and sectorial area of t, or press Ctrl+Z to quit:" << std::endl;
            double t;
            std::cin >> t;
            
            flag_wrong_parameter = !std::cin.good();

            if (flag_wrong_parameter) 
            {
                break;
            }

            std::cout << "Curve radius of t: " << hp.curvRadiusOfAngle(t) << std::endl;
            std::cout << "Hypocycloid point of t: " << "{" << hp.pointOfAngle(t).x << " , " << hp.pointOfAngle(t).y << "}" << std::endl;
            std::cout << "Sectorial area of t: " << hp.sectorialArea(t) << std::endl;

        }

        std::cin.clear();
        

        std::cout << "Enter radius of new big circle, radius of new small cirle, and from center of small circle to rolling point or press Ctrl+Z to quit:" << std::endl;
        std::cin >> rad1 >> rad2 >> dist;

        if (std::cin.good())
        {
            try
            {
                if (rad1 < hp.getRadiusBig())
                {
                    hp.setRadiusSmall(rad2);
                    hp.setRadiusBig(rad1);
                }

                if (rad2 > hp.getRadiusSmall())
                {
                    hp.setRadiusBig(rad1);
                    hp.setRadiusSmall(rad2);
                }

                hp.setRadiusBig(rad1);
                hp.setRadiusSmall(rad2);
                hp.setDistance(dist);
                
            }

            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                std::cout << "Hypocycloid with this configuration doesn't exist! The previous hypocycloid is saved!" << std::endl;
            }
        }

        else
        {
            flag_exit_from_program = true;
        }
    }

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
