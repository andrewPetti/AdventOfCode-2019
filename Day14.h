#include <string>
#include <iostream>
#include "inputs14.h"

namespace Day14
{
std::string GetText()
{
    return "You picked Day 14";
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs14();
}

} // namespace Day14
