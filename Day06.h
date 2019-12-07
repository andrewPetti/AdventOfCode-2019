#include <string>
#include <iostream>
#include "inputs06.h"

namespace Day06
{
std::string GetText()
{
    return "You picked Day 06";
}

void BuildOrbitDictionary(const std::vector<std::string> &input, std::map<std::string, std::vector<std::string>> &orbits, std::map<std::string, std::string> parents)
{
    //std::map<std::string, std::vector<std::string> *> orbits;
    std::string delimiter = ")";

    //std::map<std::string,std::string> parents;
    for (auto i : input)
    {
        auto pos = i.find(delimiter);
        auto parent = i.substr(0, pos);
        //i.erase(0, pos + delimiter.length());
        auto child = i.substr(pos + 1);
        if (orbits.find(parent) == orbits.end())
        {
            std::vector<std::string> temp{child};
            //auto vect = new std::vector<std::string>();
            //vect->push_back(child);
            orbits.insert(std::make_pair(parent, temp));
        }
        else
            orbits[parent].push_back(child);

        parents.insert(std::make_pair(child, parent));
    }
    //std::cout << "test";
    //return orbits;
}

int CalcBranch(std::map<std::string, std::vector<std::string>> &orbits, std::string parent, int parentOrbitCount)
{
    auto orbitCount = parentOrbitCount;
    auto it = orbits.find(parent);
    //orbitCount++;

    if (it != orbits.end())
    {
        auto children = it->second;
        //orbitCount = children.size();
        for (int i = 0; i < children.size(); i++)
        {
            auto child = children.at(i);
            orbitCount += CalcBranch(orbits, child, parentOrbitCount + 1);
        }
    }

    return orbitCount;
}

int CalcTotalDirectAndIndirectOrbits(std::map<std::string, std::vector<std::string>> &orbits)
{
    std::string firstParent = "COM";
    return CalcBranch(orbits, firstParent, 0);
}

int ExecuteProgram(const std::vector<std::string> &input)
{
    std::map<std::string, std::vector<std::string>> orbits;
    std::map<std::string, std::string> parents;
    BuildOrbitDictionary(input, orbits, parents);
    std::cout << "found number of objects with children orbiting: " << orbits.size() << std::endl;
    auto totalOrbits = CalcTotalDirectAndIndirectOrbits(orbits);

    return totalOrbits;
}

bool FindPath(std::string start, std::string end, std::map<std::string, std::vector<std::string>> children, std::map<std::string, std::string> parents);
{
}

int ShorestPath(std::string start, std::string end, std::map<std::string, std::vector<std::string>> children, std::map<std::string, std::string> parents);
{
    std::vector<std::string> paths;
    paths.push_back(parents.at(start));

    auto kids = children.find(start);
    if (kids != children.end())
    {
        for (auto kid : kids)
            paths.push_back(kid);
    }
    auto sibblings = children.find(parent);
    if (sibblings != children.end())
    {
        for (auto sib : sibblings)
        {
            if (sib != start)
                paths = push_back(sib);
        }
    }

    std::vector<std::vector<std::string>> pathLength;
    for (auto path : paths)
    {
        ShortestPath(path, end, children, parents);
    }
}
int ExecuteProgram2(const std::vector<std::string> &input)
{
    std::map<std::string, std::vector<std::string>> orbits;
    std::map<std::string, std::string> parents;
    BuildOrbitDictionary(input, orbits, parents);

    return ShortestPath("YOU", "SAN", orbits, parents);
    //auto parent = parents.find("YOU");
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs06();

    // input = std::vector<std::string>{
    //     "COM)B",
    //     "B)C",
    //     "C)D",
    //     "D)E",
    //     "E)F",
    //     "B)G",
    //     "G)H",
    //     "D)I",
    //     "E)J",
    //     "J)K",
    //     "K)L",
    // };

    auto totalOrbitCount = ExecuteProgram(input);
    std::cout << "The total direct and indirect orbit count is: " << totalOrbitCount << std::endl;

    std::cout << "For part 2 find min number of steps from YOU to SAN: " << std::endl;
    auto minSteps = ExecuteProgam2(input);
}

} // namespace Day06
