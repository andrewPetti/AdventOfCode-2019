#include <iostream>

#include "Day01.h"

int main ()
{
    std::cout  << "Please pick the day to execute: ";
    int choice =0;
    std::cin >> choice;
    //auto number = atoi(choice);
    switch (choice)
    {
        case 1:
            std::cout << Day01::GetText() << std::endl;
            Day01::ProcessDay01();
            break;
        default:
            std::cout << "you picked an invalid day" << std::endl;
    }

    return 0;
}
