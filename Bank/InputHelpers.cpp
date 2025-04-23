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
        std::cout << "������� ���������� ��������: ";
        std::cin >> iterations;
        if (iterations <= 0)
        {
            std::cout << "������: ���������� �������� ������ ���� �������������\n";
            exit(1);
        }
    }
    return iterations;
}