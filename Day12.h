#pragma once

#include <string>
#include <iostream>
#include "inputs12.h"
#include <map>

namespace Day12
{
std::string GetText()
{
    return "You picked Day 12";
}

void CalcVelocityChange(const std::vector<int>& x, const std::vector<int>& y, std::vector<int>& xVel, std::vector<int>& yVel)
{
    for (int i=0; i<3; i++)
    {
        if ( x[i]< y[i])
        {
            xVel[i]++;
            yVel[i]--;
        }
        else if (x[i]>y[i])
        {
            xVel[i]--;
            yVel[i]++;
        }
    }
    
}
void CalcVelocity(const std::vector<std::vector<int>>& pos, std::vector<std::vector<int>>& vel)
{
    auto a = pos[0];
    auto b = pos[1];
    auto c = pos[2];
    auto d = pos[3];

    auto& aVel = vel[0];
    auto& bVel = vel[1];
    auto& cVel = vel[2];
    auto& dVel = vel[3];
    
    CalcVelocityChange(a,b,aVel, bVel);
    CalcVelocityChange(a,c, aVel, cVel);
    CalcVelocityChange(a,d, aVel,dVel);

    CalcVelocityChange(b,c,bVel,cVel);
    CalcVelocityChange(b,d,bVel,dVel);

    CalcVelocityChange(c,d,cVel, dVel);
}

void UpdatePositions(std::vector<std::vector<int>>& pos, const std::vector<std::vector<int>>& vel)
{
    for (int i=0;i<4; i++)
    {
        auto& x = pos[i];
        auto& v = vel[i];

        x[0] += v[0];
        x[1] += v[1];
        x[2] += v[2];
    }
}

int CalcTotalEnergy(const std::vector<std::vector<int>>& pos, const std::vector<std::vector<int>>& vel)
{
    auto energy = 0;
    for (int i=0;i<4;i++)
    {
        auto p = pos[i];
        auto pot = abs(p[0]) +abs(p[1])+abs(p[2]);
        auto k = vel[i];
        auto kin = abs(k[0]) +abs(k[1])+abs(k[2]);
        energy += pot*kin;
    }

    return energy;
}
int CalcEnergyForSteps(const std::vector<std::vector<int>>& startLocation, int steps)
{
    auto vel = std::vector<std::vector<int>>{
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0}
    };

    auto pos = startLocation;

    for(int i = 1; i< steps+1; i++)
    {
        CalcVelocity(pos, vel);
        UpdatePositions(pos,vel);
        std::cout<< "Step i: " << i<<std::endl;
        for(int j=0;j<4;j++)
        {
            std::cout<<pos[j][0] << ","<< pos[j][1]<<","<<pos[j][2];
            std::cout<<" with vel = "<< vel[j][0] << ","<< vel[j][1]<<","<<vel[j][2]<<std::endl;
        }
        std::cout<<std::endl;
    }

    auto totalEnergy = CalcTotalEnergy(pos,vel);

    return totalEnergy;
}

std::string GetKey(std::vector<int>& info)
{
    auto key = std::to_string(info[0])+std::to_string(info[1])+std::to_string(info[2]);
    return key;
}

int CalcStepsToRepeat(const std::vector<std::vector<int>>& startLocation)
{
    auto vel = std::vector<std::vector<int>>{
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0}
    };

    auto pos = startLocation;

    auto cont = true;
    long long counter = 0;
    std::map<std::string,std::vector<std::string>> history;
    for(int j=0;j<4;j++)
    {
        auto posKey = std::to_string(j) + GetKey(pos[j]);
        
        history.insert(std::make_pair(posKey, std::vector<std::string>{GetKey(vel[j])}));
    }
    auto found = std::vector<bool>(4,false);
    while(cont)
    {
        counter++;
        CalcVelocity(pos, vel);
        UpdatePositions(pos,vel);
        if (counter%500000 == 0)
            std::cout<<"Currently at step: " << counter<<std::endl;

        for ( int i = 0; i<4;i++)
        {
            auto posKey = std::to_string(i) + GetKey(pos[i]);
            auto velKey = GetKey(vel[i]);
            if (history.find(posKey)== history.end())
                history.insert(std::make_pair(posKey, std::vector<std::string> {velKey}));
            else
            {
                auto vel = history[posKey];
                if ( std::find(vel.begin(), vel.end(), velKey) == vel.end())
                    vel.push_back(velKey);
                else
                    found[i]=true;                
            }    
        }
        if ( found[0]==found[1] && found[1]==found[2] && found[2]==found[3] && found[0]== true)
        {
            cont = false;
        }
        else
        {
            found[0]=found[1]=found[2]=found[3]=false;
        }
    }

    return  counter;
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs12();

    // input = std::vector<std::vector<int>> {
    //     std::vector<int>{-1,0,2},
    //     std::vector<int>{2,-10,-7},
    //     std::vector<int>{4,-8,8},
    //     std::vector<int>{3,5,-1}
    // };
    input = std::vector<std::vector<int>>{
        std::vector<int>{-8,-10,0},
        std::vector<int>{5,5,10},
        std::vector<int>{2,-7,3},
        std::vector<int>{9,-8,-3}
    };
    //part 1
    //auto steps = 1000;
    // auto totalEnergy = CalcEnergyForSteps(input, steps);
// std::cout<<"The total Energy is: " << totalEnergy <<std::endl;

    auto steps = CalcStepsToRepeat(input);
    std::cout << "The total number of steps before repeating a pos/vel combo for all 4 moons is: " <<steps<<std::endl;    
    }
} // namespace Day04
