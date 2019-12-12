#pragma once

#include <string>
#include <iostream>
#include "inputs12.h"

namespace Day12
{
std::string GetText()
{
    return "You picked Day 12";
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs12();

}

} // namespace Day04
