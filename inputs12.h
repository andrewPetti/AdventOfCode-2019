#pragma once

#include <vector>
#include <tuple>
namespace inputs
{
std::vector<std::vector<int>> GetInputs12()
{
    auto inputs = std::vector<std::vector<int>>
    {
        std::vector<int>{17,-9,4},
        std::vector<int>{2,2,-13},
        std::vector<int>{-1,5,-1},
        std::vector<int>{4,7,-7}
    };
    return inputs;
}
} // namespace inputs