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

void CalcVelocityChange(int axis, const std::vector<int>& x, const std::vector<int>& y, std::vector<int>& xVel, std::vector<int>& yVel)
{
    if ( x[axis]< y[axis])
    {
        xVel[axis]++;
        yVel[axis]--;
    }
    else if (x[axis]>y[axis])
    {
        xVel[axis]--;
        yVel[axis]++;
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

void UpdatePos (int axis, std::vector<std::vector<int>>& pos, std::vector<std::vector<int>>& vel)
{
    for (int moon=0;moon<pos.size(); moon++)
    {
        pos[moon][axis] += vel[moon][axis];
    }
}
void step(int axis, std::vector<std::vector<int>>& pos, std::vector<std::vector<int>>& vel)
{
    auto a = pos[0];
    auto b = pos[1];
    auto c = pos[2];
    auto d = pos[3];

    auto& aVel = vel[0];
    auto& bVel = vel[1];
    auto& cVel = vel[2];
    auto& dVel = vel[3];
    
    CalcVelocityChange(axis, a,b,aVel, bVel);
    CalcVelocityChange(axis, a,c, aVel, cVel);
    CalcVelocityChange(axis, a,d, aVel,dVel);

    CalcVelocityChange(axis, b,c,bVel,cVel);
    CalcVelocityChange(axis, b,d,bVel,dVel);

    CalcVelocityChange(axis, c,d,cVel, dVel);
    
    UpdatePos(axis, pos,vel);
}
long long CycleLength(int axis, const std::vector<std::vector<int>>& pos, const std::vector<std::vector<int>>& vel)
{
    auto currentPos = pos;
    auto currentVel = vel;

    long long counter = 0;
    bool cont = true;
    do
    {
        step(axis,currentPos, currentVel);
        
        counter++;
        /* code */
        if (pos[0][axis] == currentPos[0][axis] 
         && pos[1][axis] == currentPos[1][axis]
         && pos[2][axis] == currentPos[2][axis]
         && pos[3][axis] == currentPos[3][axis]
         && vel[0][axis] == currentVel[0][axis]
         && vel[1][axis] == currentVel[1][axis]
         && vel[2][axis] == currentVel[2][axis]
         && vel[3][axis] == currentVel[3][axis])
            cont = false;

    } while ( cont );
    
    
    return counter;
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

    // auto cycleX = CycleLength(0, pos, vel);
    // auto cycleY = CycleLength(2,pos,vel);
    // auto cycleZ = CycleLength(3,pos,vel);

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

long long GreatestCommonDenominator(long long a, long long b)
{
    if (b==0)
        return a;
    
    auto gcm= GreatestCommonDenominator(b,a%b);
    return gcm;
}
long long LowestCommonMultiple(long long a, long long b)
{
    if (a==0 || b==0)
        return 0;
        
    auto nom = a*b;
    auto denom = GreatestCommonDenominator(a,b);
    auto lcm = nom/denom;
    return lcm;
}
long long CalcStepsToRepeat(const std::vector<std::vector<int>>& startLocation)
{
    auto vel = std::vector<std::vector<int>>{
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0},
        std::vector<int>{0,0,0}
    };

    auto pos = startLocation;

    auto cycleX = CycleLength(0, pos, vel);
    auto cycleY = CycleLength(1,pos,vel);
    auto cycleZ = CycleLength(2,pos,vel);
    
    return  LowestCommonMultiple(LowestCommonMultiple(cycleX, cycleY), cycleZ);
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
    // input = std::vector<std::vector<int>>{
    //     std::vector<int>{-8,-10,0},
    //     std::vector<int>{5,5,10},
    //     std::vector<int>{2,-7,3},
    //     std::vector<int>{9,-8,-3}
    // };
    //part 1
    //auto steps = 1000;
    // auto totalEnergy = CalcEnergyForSteps(input, steps);
// std::cout<<"The total Energy is: " << totalEnergy <<std::endl;

    auto steps = CalcStepsToRepeat(input);
    std::cout << "The total number of steps before repeating a pos/vel combo for all 4 moons is: " <<steps<<std::endl;    
    }
} // namespace Day04
