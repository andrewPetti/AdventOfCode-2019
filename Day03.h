#include <string>
#include <iostream>
#include "inputs03.h"
#include <map>

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
        auto counter = 0;
        wirePts.reserve(160000);
        for (auto i : instructions)
        {
            //counter ++;
            auto action = i.first;
            auto step = i.second;

            if (action == "U")
            {
                for (int i = 1; i <= step; i++)
                {
                    auto curPt = std::make_pair(pt.first,pt.second+i);
                    wirePts.push_back(curPt);

                }
                pt.second += step;
            }
            else if (action == "D")
            {
                for (int i = 1; i <= step; i++)
                {
                    auto curPt = std::make_pair(pt.first, pt.second-i);
                    wirePts.push_back(curPt);
                }
                pt.second -= step;
            }
            else if (action == "R")
            {
                for (int i = 1; i <= step; i++)
                {
                    auto curPt = std::make_pair(pt.first+i, pt.second);
                    wirePts.push_back(curPt);
                }
                pt.first += step;
            }
            else if (action == "L")
            {
                for (int i = 1; i <= step; i++)
                {
                    auto curPt = std::make_pair(pt.first-i,pt.second);
                    wirePts.push_back(curPt);
                }
                pt.first -= step;
            }
            else
                throw std::invalid_argument("Action was not recongized");
        }
    }

    int FindMinDistToPt(std::vector<std::pair<int,int>>& wire, std::pair<int,int>& pt)
    {
        auto counter = 0;
        std::map<std::pair<int,int>, int> dict;

        for (auto wirePt : wire)
        {
            counter ++;
            if ( pt == wirePt)
                return counter;
            if (dict.find(wirePt) != dict.end())
                counter = dict.at(wirePt);
            else
                dict[wirePt] = counter;
        }

        return -1;
    }
    std::vector<std::pair<std::pair<int,int>,int>> FindIntercepts(std::vector<std::pair<int,int>>& wire1, std::vector<std::pair<int,int>>& wire2)
    {
        std::vector<std::pair<std::pair<int,int>,int>> intercepts;

        for ( int y=0; y<wire1.size();y++)
        {
            auto ptY = wire1[y];
            for ( int x= 0; x< wire2.size(); x++)
            {
                auto ptX = wire2[x];
                if ( ptY == ptX)
                {
                    auto distY = FindMinDistToPt(wire1,ptY);
                    auto distX = FindMinDistToPt(wire2, ptX);
                    intercepts.push_back(std::make_pair(ptY, distY+distX));                
                }
            }
        }
        return intercepts;
    }

    void Process()
    {
        std::cout << GetText() << std::endl;
        auto inputs = inputs::GetInputs03();
        inputs = std::vector<std::string>{"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};

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
            std::cout << i.first.first << "," << i.first.second <<" - steps "<< i.second<< std::endl;

        auto minDist = -1;
        auto minSteps = -1;
        for (auto& i: intercepts)
        {
            auto dist = CalcManhattenDistance(origin, i.first);
            if ( minDist == -1 || dist < minDist)
                minDist = dist;
            
            if ( minSteps == -1 || i.second < minSteps)
                minSteps = i.second;
        }

        std::cout << "The closes intercept has a distance of: " << minDist << std::endl;
        std::cout << "The minimum combined steps to reach an intercept was: " << minSteps << std::endl;
    }

} // namespace Day03
