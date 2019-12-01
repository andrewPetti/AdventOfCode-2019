#include <string>
#include <iostream>
#include "inputs01.h"

namespace Day01
{
    std::string GetText()
    { 
        return "You picked Day 01";
    }

    int CalcFuel(int mass)
    {
        auto floor = mass/ 3;
        return floor - 2;
    }
    void ProcessDay01()
    {
        auto inputs = inputs::GetInputs();
        //inputs = std::vector<int> {12,14, 1969, 100756};
        auto sum = 0;
        for( auto value : inputs)
        {
            sum += CalcFuel( value );
            //std::cout << "Fuel needed is: " << fuel << std::endl;
        }
        std::cout << "Part 1 fuel needed for all parts is: " << sum << std::endl;
        auto fuel = 0;
        sum = 0;
        for (auto value : inputs)
        {
            fuel = value;
            while ( fuel>=0)
            {
                fuel = CalcFuel(fuel);

                if ( fuel >=0)
                    sum += fuel;
            }
        }
        std::cout << "Correcting for the fuel weight as well, the totall fuel is: " << sum << std::endl;

    }
    
}
