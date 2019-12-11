#include <string>
#include <iostream>
#include "inputs11.h"
#include "Day09.h"
#include <set>

namespace Day11
{
    enum eDir { Up, Down, Left, Right};
    enum eColour {colBlack, colWhite};
    const int BLACK = 1;
    const int WHITE = 0;

std::string GetText()
{
    return "You picked Day 11";
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
    //auto val1 = mode1 == 0 ? vect[pos1] : mode1==1? pos1 : vect[relativeBase + pos1];
    //auto val2 = mode2 == 0 ? vect[pos2] : mode2 ==1? pos2 : vect[relativeBase + pos2];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);

    //vect[dest] = val1 + val2;
    SetValue(vect, val1+val2, dest,mode3, relativeBase);
}

void Op2(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    // auto val1 = mode1 == 0 ? vect[pos1] : mode1 == 1? pos1 : vect[relativeBase + pos1];
    // auto val2 = mode2 == 0 ? vect[pos2] : mode2 == 2? pos2 : vect[relativeBase + pos2];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    //vect[dest] = val1 * val2;
    SetValue(vect, val1*val2,dest, mode3, relativeBase);
}
void Op3(std::vector<long long> &vect, long long pos, long long mode,long long relativeBase, long long id)
{
    //SetValue(vect, pos, mode, id);
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
    //auto output = mode == 0 ? vect[pos] : mode == 1? pos: vect[relativeBase + pos];
    auto output = GetValue(vect, pos, mode, relativeBase);
    //std::cout << "output: " << output << std::endl;
    return output;
}


long long Op5(std::vector<long long> &vect, long long pos1, long long pos2, long long mode1, long long mode2, long long relativeBase, std::vector<long long>::iterator &it)
{
    //auto val1 = mode1 == 0 ? vect[pos1] : mode1==1? pos1:vect[relativeBase+pos1];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    if (val1 == 0)
        return 3;
    //auto val2 = mode2 == 0 ? vect[pos2] : mode2==1? pos2: vect[relativeBase+pos2];
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if ( val2 > vect.size()-1)
        GrowMemory(vect, val2+1);
    it = vect.begin() + val2;
    return 0;
}

long long Op6(std::vector<long long> &vect, long long pos1, long long pos2, long long mode1, long long mode2, long long relativeBase, std::vector<long long>::iterator &it)
{
    //auto val1 = mode1 == 0 ? vect[pos1] :mode1==1?pos1: vect[relativeBase+pos1];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    if (val1 != 0)
        return 3;
    //auto val2 = mode2 == 0 ? vect[pos2] : mode2==1?pos2: vect[relativeBase+pos2];
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if( val2 > vect.size()-1)
        GrowMemory(vect, val2+1);
    it = vect.begin() + val2;

    return 0;
}

// void Op7(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, std::vector<long long>::iterator &it)
// {
//     auto val1 = mode1 == 0 ? vect[pos1] : mode1==1? pos1: vect[relativeBase+pos1];
//     auto val2 = mode2 == 0 ? vect[pos2] : mode2==2? pos2: vect[relativeBase+pos2];
//     if (val1 < val2)
//         *it = 1;
//     else
//         *it = 0;
// }

void Op7(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    //auto val1 = mode1 == 0 ? vect[pos1] : mode1==1? pos1 : vect[relativeBase+pos1];
    //auto val2 = mode2 == 0 ? vect[pos2] : mode2==1? pos2 : vect[relativeBase+pos2];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if (val1 < val2)
        SetValue(vect,1,dest, mode3, relativeBase);//vect[dest] = 1;
    else
        SetValue(vect,0, dest, mode3, relativeBase);//vect[dest] = 0;
}

void Op8(std::vector<long long> &vect, long long pos1, long long pos2, long long dest, long long mode1, long long mode2, long long mode3, long long relativeBase)
{
    //auto val1 = mode1 == 0 ? vect[pos1] : mode1==1? pos1: vect[relativeBase+pos1];
    //auto val2 = mode2 == 0 ? vect[pos2] : mode2==1? pos2 : vect[relativeBase+pos2];
    auto val1 = GetValue(vect, pos1, mode1, relativeBase);
    auto val2 = GetValue(vect, pos2, mode2, relativeBase);
    if (val1 == val2)
        SetValue(vect,1,dest, mode3, relativeBase);//vect[dest] = 1;
    else
        SetValue(vect,0,dest, mode3, relativeBase);//vect[dest] = 0;
}

void Op9(std::vector<long long>& vect, long long& relativeBase, long long pos, long long mode)
{
    //relativeBase += pos;
    relativeBase += GetValue(vect, pos, mode, relativeBase);
}

void UpdatePair(std::vector<long long> &vect, long long val1, long long val2)
{
    vect[1] = val1;
    vect[2] = val2;
}

eColour GetCurrentColour(const std::map<std::pair<int,int>,eColour>& pointState, const std::pair<int,int>& currentPoint)
{
    auto it = pointState.find(currentPoint);
    if ( it == pointState.end())
        return colBlack;
    
    return it->second;
}
void PaintPoint(std::map<std::pair<int,int>,eColour>& pointState, std::pair<int,int>& pt, const int instruction)
{
    auto colour = instruction == 0?colBlack:colWhite;
    if (pointState.find(pt) == pointState.end())
    {
        pointState.insert(std::make_pair(pt, colour));
    }
    else
        pointState[pt] = colour;
}

void MovePoint(std::pair<int,int>& pt, eDir& currentDir, const int turn)
{
    std::cout<< "Moving point: " << pt.first <<"," <<pt.second<< " to ";
    if ( turn == 0 ) //left
    {
        switch (currentDir)
        {
            case Up:
                currentDir = Left;
                pt.first --;
            break;
            case Down:
                currentDir = Right;
                pt.first ++;
            break;
            case Left:
                currentDir = Down;
                pt.second++;
            break;
            case Right:
                currentDir = Up;
                pt.second--;
                break;
            default:
                throw std::invalid_argument("Incorrect current Direction!");
        }
    }
    if ( turn == 1 )
    {
        switch (currentDir)
        {
            case Up:
                currentDir = Right;
                pt.first ++;
            break;
            case Down:
                currentDir = Left;
                pt.first --;
            break;
            case Left:
                currentDir = Up;
                pt.second--;
            break;
            case Right:
                currentDir = Down;
                pt.second++;
                break;
            default:
                throw std::invalid_argument("Incorrect current Direction!");
        }        
    }

    std::cout<< pt.first << ","<< pt.second <<std::endl;
}
int ExecuteProgram(std::vector<long long> &vect, const std::pair<int,int>& startPoint, const eDir startDirection)
{
    std::map<std::pair<int,int>,eColour> pointState;
    std::pair<int,int> currentPoint = startPoint;
    auto currentDirection = startDirection;
    long long relativeBase = 0;
    auto it = vect.begin();
    auto cont = true;

    //part 2
    pointState.insert(std::make_pair(currentPoint, colWhite));

    auto outputCounter = 0;    
    std::set<std::pair<int,int>> painted;
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
            auto colour = GetCurrentColour(pointState, currentPoint);
            auto input = colour == eColour::colBlack? 0:1;
            
            Op3(vect, pos1, mode1,relativeBase,input);
            it = it + 2;
        }
        else if (op == 4)

        {
            auto pos1 = *(it + 1);
            auto output  = Op4(vect, pos1, mode1, relativeBase);
            outputCounter++;
            if ( outputCounter % 2 == 1)
            {
                PaintPoint(pointState, currentPoint, output);
                painted.insert(currentPoint);
            }
            else
                MovePoint(currentPoint, currentDirection, output);

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
    std::cout<< "Output Counter is: " <<outputCounter<<std::endl;
    std::cout << "Set has a size of : " << painted.size()<<std::endl;

    int maxX = 0;
    int maxY = 0;
    for (auto i: pointState )
    {
        if ( i.first.first> maxX)
            maxX = i.first.first;
        if (i.first.second> maxY)
            maxY = i.first.second;
    }

    std::vector<std::vector<std::string>> msg;

    for ( int i=0;i<maxY+1; i++)
    {
        auto line = std::vector<std::string>(maxX+1,"");
        msg.push_back(line);
    }

    for (auto i: pointState)
    {
        auto pt = i.first;
        msg[pt.second][pt.first] = i.second == colBlack?"#":" ";
    }

    for (auto i: msg)
    {
        for (auto j: i)
            std::cout<< j<<",";
        std::cout<< std::endl;
    }

    std::cout<<std::endl;
    return pointState.size();
}

void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs11();

    std::map<std::pair<int,int>,std::string> points;

    auto startPoint = std::make_pair(0,0);
    auto startDirection = eDir::Up;

    auto output = ExecuteProgram(input, startPoint, startDirection);

    std::cout << "The number of panels painted atlest once: " << output << std::endl;

}

} // namespace Day04
