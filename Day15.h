#pragma once

#include <string>
#include <iostream>
#include "inputs15.h"

namespace Day15
{
    std::string GetText()
    {
        return "You picked Day 15";
    }

    void GrowMemory(std::vector<long long>& vect, long long newSize)
    {
        vect.resize(newSize, 0);
    }
    long long GetValue( std::vector<long long>& vect, long long pos, long long mode,long long relativeBase)
    {
        long long value;
        if ( mode < 2 )
        {
            if ( mode == 0 )
            {
                if ( pos < 0 )
                    throw std::invalid_argument("We can't read from before 0!");
                if ( pos > vect.size() -1)
                    GrowMemory(vect, pos+1);
                value = vect[pos];
            }
            else if ( mode == 1)
            {
                value= pos;
            }
        }
        else
        {
            if ( relativeBase+pos < 0 )
                throw std::invalid_argument("Even with relative mode we can't read before 0!");
            if ( relativeBase+pos > vect.size()-1)
                GrowMemory(vect, relativeBase+pos+1);

            value = vect[relativeBase+pos];
        }

        return value;
    }

    void SetValue(std::vector<long long> &vect, long long val, long long dest, long long mode, long long relativeBase)
    {
        auto location =-1;
        if ( mode == 0 )
        {
            location = dest;
        }
        else if ( mode == 2)
        {
            location = relativeBase+dest;
        }

        if ( location > vect.size()-1)
            GrowMemory(vect, location+1);
        
        vect[location] = val;
    }

void Op1(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3,long long relativeBase)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);

    SetValue(vect, val1+val2, dest,mode3, relativeBase);
}

void Op2(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    SetValue(vect, val1*val2,dest, mode3, relativeBase);
}
void Op3(std::vector<long long> &vect, long long pos, long long mode,long long relativeBase, long long id)
{
    if ( mode == 0)
        vect[pos] = id;
    else if ( mode == 2)
    {
        if (relativeBase+pos > vect.size()-1)
            GrowMemory(vect,relativeBase+pos+1);

        vect[relativeBase+pos] = id;
    }
}

int Op4(std::vector<long long> &vect, long long pos, long long mode, long long relativeBase)
{
    auto output = GetValue(vect, pos, mode, relativeBase);
    //std::cout << "output: " << output << std::endl;
    return output;
}

long long Op5(std::vector<long long> &vect, long long pos1, long long pos2, long long mode1, long long mode2, long long relativeBase, std::vector<long long>::iterator &it)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    if (val1 == 0)
        return 3;

    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if ( val2 > vect.size()-1)
        GrowMemory(vect, val2+1);
    it = vect.begin() + val2;
    return 0;
}

long long Op6(std::vector<long long> &vect, long long pos1, long long pos2, long long mode1, long long mode2, long long relativeBase, std::vector<long long>::iterator &it)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    if (val1 != 0)
        return 3;

    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if( val2 > vect.size()-1)
        GrowMemory(vect, val2+1);
    it = vect.begin() + val2;

    return 0;
}

void Op7(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if (val1 < val2)
        SetValue(vect,1,dest, mode3, relativeBase);//vect[dest] = 1;
    else
        SetValue(vect,0, dest, mode3, relativeBase);//vect[dest] = 0;
}

void Op8(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if (val1 == val2)
        SetValue(vect,1,dest, mode3, relativeBase);//vect[dest] = 1;
    else
        SetValue(vect,0,dest, mode3, relativeBase);//vect[dest] = 0;
}

void Op9(std::vector<long long>& vect, long long& relativeBase, long long pos, long long mode)
{
    relativeBase += GetValue(vect, pos, mode, relativeBase);
}

void UpdatePair(std::vector<long long> &vect, long long val1, long long val2)
{
    vect[1] = val1;
    vect[2] = val2;
}

bool ProcessStatus(int status, int& currentDir, std::pair<int,int>& currentPos )
{
    if ( status == 1 || status == 2)
    {
        switch(currentDir)
        {
        case 1: //north
            currentPos.second--;
            break;
        case 2://south
            currentPos.second++;
            break;
        case 3: //west
            currentPos.first--;
            break;
        case 4://east
            currentPos.first++;
            break;
        default:
            throw std::invalid_argument("CurrentDir is not a valid direction");
        }
        if ( status == 2)
            return true;
    }

    if ( status == 0 )
    {
        switch(currentDir)
        {
        case 1: //north
            currentDir=4;
            break;
        case 2://south
            currentDir=3;
            break;
        case 3: //west
            currentDir=1;
            break;
        case 4://east
            currentDir = 2;
            break;
        default:
            throw std::invalid_argument("CurrentDir is not a valid direction");
        }
    }

    return false;
}

int CalcManhattenDistance(const std::pair<int, int> &pt1, const std::pair<int, int> &pt2)
{
    return abs(pt1.first - pt2.first) + abs(pt1.second - pt2.second);
}

void ExecuteProgram(std::vector<long long> &vect)
{
    long long relativeBase = 0;
    auto it = vect.begin();
    auto cont = true;
    auto currentPos = std::make_pair(0,0);
    auto north = 1;
    auto south = 2;
    auto west =3;
    auto east=4;
    auto currentDir = north;
    std::pair<int,int> oxygenSystem;
    while (cont)
    {
        auto code = *it;
        //std::cout << "Processing : "<<code<<std::endl;
        long long op = code % 100;
        long long mode3 = code / 10000;
        long long mode2 = (code % 10000) / 1000;
        long long mode1 = (code % 1000) / 100;
        auto value = -1;

        if (op == 99)
        {
            std::cout << "Halting do to Op Code 99" << std::endl;
            break;
        }
        if (op == 1 || op == 2 || op == 7 || op == 8)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            if (op == 1)
                Op1(vect, pos1, pos2, *(it + 3), mode1, mode2,mode3,relativeBase);
            else if (op == 2)
                Op2(vect, pos1, pos2, *(it + 3), mode1, mode2,mode3, relativeBase);
            else if (op == 7)
                Op7(vect, pos1, pos2, *(it + 3), mode1, mode2,mode3, relativeBase);
            else if (op == 8)
                Op8(vect, pos1, pos2, *(it + 3), mode1, mode2,mode3, relativeBase);
            it = it + 4;
        }
        else if (op == 3)
        {
            auto pos1 = *(it + 1);
            Op3(vect, pos1, mode1,relativeBase,currentDir);
            std::cout<<"input dir: " << currentDir << " & output is: ";
            it = it + 2;
        }
        else if (op == 4)

        {
            auto pos1 = *(it + 1);
            auto status = Op4(vect, pos1, mode1, relativeBase);
            std::cout << status ;//<< std::endl;
            if (ProcessStatus(status, currentDir, currentPos))
            {
                std::cout<< " The current position is: " << currentPos.first<<","<<currentPos.second<<std::endl;
                oxygenSystem = currentPos;
                std::cout<<"Found the oxygen System at: " << oxygenSystem.first<<","<<oxygenSystem.second<<std::endl;
            }
            else
            {
                std::cout<< " The current position is: " << currentPos.first<<","<<currentPos.second<<std::endl;
            }
            
            it = it + 2;
        }
        else if (op == 5)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            auto move = Op5(vect, pos1, pos2, mode1, mode2, relativeBase, it);
            if (move > 0)
                it = it + move;
        }
        else if (op == 6)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            auto move = Op6(vect, pos1, pos2, mode1, mode2, relativeBase, it);
            if (move > 0)
                it = it + move;
        }
        else if ( op == 9)
        {
            auto pos1 =*(it+1);
            Op9(vect, relativeBase, pos1, mode1);
            it = it + 2;
        }
        else
        {

            cont = false;
            std::cout << "Programmed Halted: reason Unknown!" << std::endl;
        }
    }

    auto dist = CalcManhattenDistance(std::make_pair(0,0),oxygenSystem);
    std::cout<<"The minimum number os steps to the O2 system is: " << dist<<std::endl;
}

void Process()
{
    std::cout << GetText() << std::endl;

    auto inputs = inputs::GetInputs15();
    auto id = 0;
    
    ExecuteProgram(inputs);
}

} // namespace Day09
