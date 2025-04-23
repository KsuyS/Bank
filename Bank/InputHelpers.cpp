#include "InputHelpers.h"
#include <iostream>
#include <cstdlib>

int GetIterations(int argc, char* argv[])
{
    int iterations = 0;
    if (argc > 1)
    {
        iterations = std::atoi(argv[1]);
    }

    if (iterations <= 0)
    {
        std::cout << "Введите количество итераций: ";
        std::cin >> iterations;
        if (iterations <= 0)
        {
            std::cout << "Ошибка: количество итераций должно быть положительным\n";
            exit(1);
        }
    }
    return iterations;
}