// Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "..\Library\Hypocycloid.h"
#include "tchar.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Prog2::Hypocycloid hp;
    Prog2::Point p1, p2, p3;
    double rad1, rad2;
    bool flag1 = true;

    while (flag1)
    {
        std::cout << "Your hypocycloid is:" << std::endl;

        std::cout << "The type of your hypocicloid is: ";
       
        int type = hp.typeOfHypocycloid();
        if (type == Prog2::Hypocycloid::SIMPLE) 
        {
            std::cout << "simple" << std::endl;
        }
        else if (type == Prog2::Hypocycloid::LONG)
        {
            std::cout << "long" << std::endl;
        }
        else
        {
            std::cout << "short" << std::endl;
        }

        std::cout << "Center of big circle: ";
        std::cout << "{" << hp.getC1().x << " , " << hp.getC1().y << "}" << std::endl;
        std::cout << "Radius of big circle: ";
        std::cout << hp.getR1() << std::endl;


        std::cout << "Center of small circle: ";
        std::cout << "{" << hp.getC2().x << " , " << hp.getC2().y << "}" << std::endl;
        std::cout << "Radius of small circle: ";
        std::cout << hp.getR2() << std::endl;

        std::cout << "The coordinates of rolling point: ";
        std::cout << "{" << hp.getRollingPoint().x << " , " << hp.getRollingPoint().y << "}" << std::endl;

        bool flag2 = true;

        while (flag2)
        {
            std::cout << "Enter angle t in radians to calculate curve radius of t, hypocycloid point of t and sectorial area of t, or press Ctrl+Z to quit:" << std::endl;
            double t;
            std::cin >> t;
            
            flag2 = std::cin.good();

            if (!flag2) 
            {
                continue;
            }

            std::cout << "Curve radius of t: " << hp.curvRadiusOfAngle(t) << std::endl;
            std::cout << "Hypocycloid point of t: " << "{" << hp.pointOfAngle(t).x << " , " << hp.pointOfAngle(t).y << "}" << std::endl;
            std::cout << "Sectorial area of t: " << hp.sectorialArea(t) << std::endl;

        }

        std::cin.clear();
        std::cout << "Enter x of new center of big circle, y of big circle, radius of big circle, the same for small cirle, and x, y of rolling point or press Ctrl+Z to quit:" << std::endl;
        std::cin >> p1.x >> p1.y >> rad1 >> p2.x >> p2.y >> rad2 >> p3.x >> p3.y;

        if (std::cin.good())
        {
            bool flag3 = true;

            try
            {
                hp.setR1R2C1C2(rad1, rad2, p1, p2);
            }

            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                flag3 = false;
            }

            if (flag3)
            {
                hp.setRollingPoint(p3);
            }
        }

        else
        {
            flag1 = false;
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
