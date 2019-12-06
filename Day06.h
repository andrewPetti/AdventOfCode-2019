#include <string>
#include <iostream>
#include "inputs04.h"

namespace Day06
{
std::string GetText()
{
    return "You picked Day 06";
}

void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs04();
}

} // namespace Day06
