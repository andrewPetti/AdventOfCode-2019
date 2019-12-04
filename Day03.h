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

    std::vector<std::pair<std::string, int>> GetInstructions(const std::string &wire)
    {
        std::string wireCopy = wire;
        std::string delimiter = ",";

        size_t pos = 0;
        std::string token = "";

        std::vector<std::pair<std::string, int>> instructions;
        while ((pos = wireCopy.find(delimiter)) != std::string::npos)
        {
            token = wireCopy.substr(0, pos);
            wireCopy.erase(0, pos + delimiter.length());
            auto action = token.substr(0, 1);
            auto stepStr = token.substr(1, token.length() - 1);
            auto step = std::stoi(stepStr);
            instructions.push_back(std::make_pair(action, step));
        }

        return instructions;
    }

    void MapWire(std::vector<std::pair<int,int>>& wirePts, const std::string &wire, const std::pair<int, int> &origin)
    {
        std::string wireCopy = wire;
        std::string delimiter = ",";

        std::vector<std::pair<std::string, int>> instructions = GetInstructions(wire);
        auto pt = std::make_pair(0,0);

        for (auto i : instructions)
        {
            auto action = i.first;
            auto step = i.second;

            if (action == "U")
            {
                for (int i = 1; i <= step; i++)
                {
                    wirePts.push_back(std::make_pair(pt.first,pt.second+i));
                }
                pt.second += step;
            }
            else if (action == "D")
            {
                for (int i = 1; i <= step; i++)
                    wirePts.push_back(std::make_pair(pt.first, pt.second-i));
                pt.second -= step;
            }
            else if (action == "R")
            {
                for (int i = 1; i <= step; i++)
                    wirePts.push_back(std::make_pair(pt.first+i, pt.second));
                pt.first += step;
            }
            else if (action == "L")
            {
                for (int i = 1; i <= step; i++)
                    wirePts.push_back(std::make_pair(pt.first-i,pt.second));
                pt.first -= step;
            }
            else
                throw std::invalid_argument("Action was not recongized");
        }
    }

    std::vector<std::pair<int,int>> FindIntercepts(const std::vector<std::pair<int,int>>& wire1, const std::vector<std::pair<int,int>>& wire2)
    {
        std::vector<std::pair<int,int>> intercepts;

        for ( auto y=0; y<wire1.size();y++)
        {
            auto pt1 = wire1[y];
            for ( int x= 0; x< wire2.size(); x++)
            {
                if ( pt1 == wire2[x])
                    intercepts.push_back(pt1);                
            }
        }
        return intercepts;
    }

    void Process()
    {
        std::cout << GetText() << std::endl;
        auto inputs = inputs::GetInputs03();
        //inputs = std::vector<std::string>{"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};

         auto origin = std::make_pair(0,0 );
 
        std::vector<std::vector<std::pair<int,int>>> wirePts;

        for (auto wire : inputs)
        {
            std::vector<std::pair<int,int>> pts;
            MapWire(pts, wire, origin);
            wirePts.push_back(pts);
        }

        auto intercepts = FindIntercepts(wirePts[0], wirePts[1]);
        std::cout << "Intercepts are:" << std::endl;

        for (auto& i: intercepts)
            std::cout << i.first << "," << i.second << std::endl;

        auto minDist = -1;
        //std::vector<std::pair<int,int>> wirePts;
        //std::pair<int,int> origin = std::make_pair(0,0);
        for (auto& i: intercepts)
        {
            auto dist = CalcManhattenDistance(origin, i);
            if ( minDist == -1 || dist < minDist)
                minDist = dist;
        }

        std::cout << "The closes intercept has a distance of: " << minDist << std::endl;
    }

} // namespace Day03
