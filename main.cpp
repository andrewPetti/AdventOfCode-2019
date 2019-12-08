#include <iostream>

#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"
#include "Day07.h"
#include "Day08.h"

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
    case 5:
        Day05::Process();
        break;
    case 6:
        Day06::Process();
        break;
    case 7:
        Day07::Process();
        break;
    case 8:
        Day08::Process();
        break;
    default:
        std::cout << "you picked an invalid day" << std::endl;
    }

    std::cout << "Enter any letter to exit: ";
    char letter;
    std::cin >> letter;
    return 0;
}
