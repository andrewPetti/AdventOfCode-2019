#include <algorithm>
#include <string>
#include <iostream>
#include "inputs07.h"

namespace Day07
{
std::string GetText()
{
    return "You picked Day 07";
}

void Op1(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;

    vect[dest] = val1 + val2;
}

void Op2(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    vect[dest] = val1 * val2;
}
void Op3(std::vector<int> &vect, int pos, int id)
{
    vect[pos] = id;
}

int Op4(std::vector<int> &vect, int pos, int mode)
{
    auto output = mode == 0 ? vect[pos] : pos;
    //std::cout << "output: " << output << std::endl;
    return output;
}

int Op5(std::vector<int> &vect, int pos1, int pos2, int mode1, int mode2, std::vector<int>::iterator &it)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    if (val1 == 0)
        return 3;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    it = vect.begin() + val2;

    return 0;
}

int Op6(std::vector<int> &vect, int pos1, int pos2, int mode1, int mode2, std::vector<int>::iterator &it)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    if (val1 != 0)
        return 3;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    it = vect.begin() + val2;

    return 0;
}

void Op7(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2, std::vector<int>::iterator &it)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    if (val1 < val2)
        *it = 1;
    else
        *it = 0;
}

void Op7(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    if (val1 < val2)
        vect[dest] = 1;
    else
        vect[dest] = 0;
}

void Op8(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    if (val1 == val2)
        vect[dest] = 1;
    else
        vect[dest] = 0;
}

void SetValue(std::vector<int> &vect, int val, int pos)
{
    vect[pos] = val;
}

void UpdatePair(std::vector<int> &vect, int val1, int val2)
{
    vect[1] = val1;
    vect[2] = val2;
}

int ExecuteProgram(std::vector<int> vect, int phase, int previousOutput)
{
    auto it = vect.begin();
    auto cont = true;
    auto currentOutput = -1;
    //    auto currentOutput = 0;
    auto inputCounter = 0;
    while (cont)
    {
        auto code = *it;
        int op = code % 100;
        int mode3 = code / 10000;
        int mode2 = (code % 10000) / 1000;
        int mode1 = (code % 1000) / 100;
        auto value = -1;

        if (op == 99)
        {
            //std::cout << "Halting do to Op Code 99" << std::endl;
            break;
        }
        if (op == 1 || op == 2 || op == 7 || op == 8)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            if (op == 1)
                Op1(vect, pos1, pos2, *(it + 3), mode1, mode2);
            else if (op == 2)
                Op2(vect, pos1, pos2, *(it + 3), mode1, mode2);
            else if (op == 7)
                Op7(vect, pos1, pos2, *(it + 3), mode1, mode2);
            else if (op == 8)
                Op8(vect, pos1, pos2, *(it + 3), mode1, mode2);
            it = it + 4;
        }
        else if (op == 3)
        {
            auto pos1 = *(it + 1);
            auto input = 0;
            if (inputCounter == 0)
                input = phase;
            else if (inputCounter == 1)
                input = previousOutput;
            else
                input = currentOutput;
            Op3(vect, pos1, input);
            //Op3(vect, pos1, inputCounter == 0 ? phase : previousOutput);
            it = it + 2;
            inputCounter++;
        }
        else if (op == 4)

        {
            auto pos1 = *(it + 1);
            auto output = Op4(vect, pos1, mode1);
            it = it + 2;
            currentOutput = output;
        }
        else if (op == 5)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            auto move = Op5(vect, pos1, pos2, mode1, mode2, it);
            if (move > 0)
                it = it + move;
        }
        else if (op == 6)
        {
            auto pos1 = *(it + 1);
            auto pos2 = *(it + 2);
            auto move = Op6(vect, pos1, pos2, mode1, mode2, it);
            if (move > 0)
                it = it + move;
        }

        else
        {

            cont = false;
            std::cout << "Programmed Halted: reason Unknown!" << std::endl;
        }
    }

    return currentOutput;
} // namespace Day07
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs07();
    //input = std::vector<int>{3, 15, 3, 16, 1002, 16, 10, 16, 1, 16, 15, 15, 4, 15, 99, 0, 0};
    //input = std::vector<int>{3, 23, 3, 24, 1002, 24, 10, 24, 1002, 23, -1, 23, 101, 5, 23, 23, 1, 24, 23, 23, 4, 23, 99, 0, 0};
    //input = std::vector<int>{3, 31, 3, 32, 1002, 32, 10, 32, 1001, 31, -2, 31, 1007, 31, 0, 33, 1002, 33, 7, 33, 1, 33, 31, 31, 1, 32, 31, 31, 4, 31, 99, 0, 0, 0};
    //input = std::vector<int>{3, 26, 1001, 26, -4, 26, 3, 27, 1002, 27, 2, 27, 1, 27, 26, 27, 4, 27, 1001, 28, -1, 28, 1005, 28, 6, 99, 0, 0, 5};
    input = std::vector<int>{3, 52, 1001, 52, -5, 52, 3, 53, 1, 52, 56, 54, 1007, 54, 5, 55, 1005, 55, 26, 1001, 54, -5, 54, 1105, 1, 12, 1, 53, 54, 53, 1008, 54, 0, 55, 1001, 55, 1, 55, 2, 53, 55, 53, 4, 53, 1001, 56, -1, 56, 1005, 56, 6, 99, 0, 0, 0, 0, 10};

    std::vector<int> phases{0, 1, 2, 3, 4};
    std::vector<int> feedbackPhases{5, 6, 7, 8, 9};
    //std::vector<int> phases{5, 6, 7, 8, 9};
    std::vector<int> maxPhaseOrder;
    std::vector<int> maxFeedbackPhaseOrder;
    auto maxThrust = 0;
    auto cont = true;
    // do
    // {
    //     auto currentOutput = 0;
    //     for (auto phase : phases)
    //     {
    //         currentOutput = ExecuteProgram(input, phase, currentOutput);
    //     }

    //     do
    //     {
    //         for (auto feedbackPhase : feedbackPhases)
    //         {
    //             currentOutput = ExecuteProgram(input, feedbackPhase, currentOutput);
    //         }
    //         if (currentOutput > maxThrust)
    //         {
    //             maxThrust = currentOutput;
    //             maxPhaseOrder = phases;
    //             maxFeedbackPhaseOrder = feedbackPhases;
    //         }
    //     } while (std::next_permutation(feedbackPhases.begin(), feedbackPhases.end()));
    // } while (std::next_permutation(phases.begin(), phases.end()));

    phases = feedbackPhases;
    phases = std::vector<int>{9, 7, 8, 5, 6};
    auto firstpass = true;
    do
    {
        auto currentOutput = 0;
        for (auto phase : phases)
        {
            currentOutput = ExecuteProgram(input, phase, currentOutput);
        }

        for (auto feedbackPhase : phases)
        {
            currentOutput = ExecuteProgram(input, feedbackPhase, currentOutput);
        }
        if (firstpass || currentOutput > maxThrust)
        {
            maxThrust = currentOutput;
            maxPhaseOrder = phases;
            //maxFeedbackPhaseOrder = feedbackPhases;
        }
        firstpass = false;
    } while (false); //(std::next_permutation(phases.begin(), phases.end()));
    std::cout
        << "The max thruster is: " << maxThrust << " and is found when using phases: ";
    for (auto phase : maxPhaseOrder)
        std::cout << phase << ",";
    std::cout << " and feekback phases: ";
    for (auto phase : maxFeedbackPhaseOrder)
        std::cout << phase << ",";

    std::cout << std::endl;
}

} // namespace Day07
