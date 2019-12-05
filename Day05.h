#include <string>
#include <iostream>
#include "inputs05.h"

namespace Day05
{
std::string GetText()
{
    return "You picked Day 05";
}

void Op1(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    //auto value = (
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;

    vect[dest] = val1 + val2;
}

void Op2(std::vector<int> &vect, int pos1, int pos2, int dest, int mode1, int mode2)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    auto val2 = mode2 == 0 ? vect[pos2] : pos2;
    //auto value = vect[pos1] * vect[pos2];
    vect[dest] = val1 * val2;
}
void Op3(std::vector<int> &vect, int pos, int id)
{
    vect[pos] = id;
}

void Op4(std::vector<int> &vect, int pos, int mode)
{
    auto output = mode == 0 ? vect[pos] : pos;
    std::cout << "output: " << output << std::endl;
}

int Op5(std::vector<int> &vect, int pos1, int pos2, int mode1, int mode2, std::vector<int>::iterator &it)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    if (val1 == 0)
        return 3;
    //*it = mode2 == 0 ? vect[pos2] : pos2;
    auto val2 = mode2 == 0?vect[pos2]:pos2;
    it = vect.begin()+val2;
    //return *it;
    return 0;
}

int Op6(std::vector<int> &vect, int pos1, int pos2, int mode1, int mode2, std::vector<int>::iterator &it)
{
    auto val1 = mode1 == 0 ? vect[pos1] : pos1;
    if (val1 != 0)
        return 3;
    //*it = mode2 == 0 ? vect[pos2] : pos2;
    auto val2 = mode2 ==0?vect[pos2]:pos2;
    it = vect.begin()+val2;
    //return *it;
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

void ExecuteProgram(std::vector<int> &vect, int id /* , int noun, int verb */)
{
    //UpdatePair(vect, noun, verb);
    auto it = vect.begin();
    auto cont = true;
    while (cont)
    {
        auto code = *it;
        int op = code % 100;
        int mode3 = code / 10000;
        int mode2 = (code % 10000) / 1000;
        int mode1 = (code % 1000) / 100;
        //int modes = code / 100;
        //auto pos1 = *(it + 1);
        //auto pos2 = *(it + 2);
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
            Op3(vect, pos1, id);
            it = it + 2;
        }
        else if (op == 4)

        {
            auto pos1 = *(it + 1);
            Op4(vect, pos1, mode1);
            it = it + 2;
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
    //for (auto i : vect)
    //    std::cout << i << " ";
    //std::cout << std::endl;
}

int FindAnswer(int &output, const std::vector<int> &inputs)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            auto input = inputs;
            //ExecuteProgram(input, i, j);
            if (output == input[0])
            {
                return 100 * i + j;
            }
        }
    }
    throw;
}

void Process()
{
    std::cout << GetText() << std::endl;

    auto inputs = inputs::GetInputs05();
    //inputs = std::vector<int>{3, 0, 4, 0, 99};
    //inputs = std::vector<int>{1002, 4, 3, 4, 33};

    // inputs = std::vector<int>{3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31,
    //                           1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104,
    //                           999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99};
    // // 0 for imput does not work
    //inputs = std::vector<int>{3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    //inputs = std::vector<int>{3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    //inputs = std::vector<int>{3, 3, 1107, -1, 8, 3, 4, 3, 99};
    auto id = 0;
    std::cout << "Please enter the system id: ";
    std::cin >> id;
    ExecuteProgram(inputs, id);

    // auto output = 19690720;
    // inputs = inputs::GetInputs02();
    // auto ans = FindAnswer(output, inputs);
    // std::cout << "The answer of 100*noun+verb is: " << ans << std::endl;
}

} // namespace Day05
