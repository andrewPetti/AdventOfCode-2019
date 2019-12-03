#include <string>
#include <iostream>
#include "inputs03.h"

namespace Day03
{
std::string GetText()
{
    return "You picked Day 03";
}

int CalcManhattenDistance(const std::pair<int, int> &pt1, const std::pair<int, int> &pt2)
{
    return abs(pt1.first - pt2.first) + abs(pt1.second - pt2.second);
}

void MapWire(std::vector<std::vector<std::string> *> &grid, const std::string &wire, const std::pair<int, int> &origin)
{
    std::string wireCopy = wire;
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token = "";
    std::vector < std::pair<std::string, int> instructions;
    while ((pos = wireCopy.find(delimiter)) != std::string::npos)
    {
        token = wireCopy.substr(0, pos);
        wireCopy.erase(0, pos + delimiter.length());
        auto action = token.substr(0, 1);
        auto stepStr = token.substr(1, token.length() - 1);
        auto step = std::stoi(stepStr);
        instructions.push_back
                std::cout
            << "instruction and step are: " << instruction << " " << step << std::endl;
    }
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto inputs = inputs::GetInputs03();
    inputs = std::vector<std::string>{"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};

    std::vector<std::vector<std::string> *> grid;
    auto rows = 148;
    auto columns = 301;
    auto origin = std::make_pair(0, 53);
    grid.reserve(rows);
    for (auto i = 0; i < rows; i++)
    {
        auto row = new std::vector<std::string>(columns, ".");
        grid.push_back(row);
    }

    for (auto wire : inputs)
        MapWire(grid, wire, origin);
}

} // namespace Day03
