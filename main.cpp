#include <iostream>

#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"

int main()
{
    std::cout << "Please pick the day to execute: ";
    int choice = 0;
    std::cin >> choice;
    //auto number = atoi(choice);
    switch (choice)
    {
    case 1:
        std::cout << Day01::GetText() << std::endl;
        Day01::ProcessDay01();
        break;
    case 2:
        Day02::Process();
        break;
    case 3:
        Day03::Process();
        break;
    case 4:
        Day04::Process();
        break;
    default:
        std::cout << "you picked an invalid day" << std::endl;
    }

    return 0;
}
