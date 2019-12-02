#include <string>
#include <iostream>
#include "inputs02.h"

namespace Day02
{
std::string GetText()
{
    return "You picked Day 02";
}

int Op1(std::vector<int> &vect, int pos1, int pos2)
{
    return vect[pos1] + vect[pos2];
}

int Op2(std::vector<int> &vect, int pos1, int pos2)
{
    return vect[pos1] * vect[pos2];
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

void ExecuteProgram(std::vector<int> &vect, int noun, int verb)
{
    UpdatePair(vect, noun, verb);
    auto it = vect.begin();
    auto cont = true;
    while (cont)
    {
        auto op = *it;
        auto pos1 = *(it + 1);
        auto pos2 = *(it + 2);
        auto value = -1;
        if (op == 99)
            break;
        if (op == 1)
            value = Op1(vect, pos1, pos2);
        else if (op == 2)
            value = Op2(vect, pos1, pos2);
        vect[*(it + 3)] = value;
        it = it + 4;
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
            ExecuteProgram(input, i, j);
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

    auto inputs = inputs::GetInputs02();
    //inputs = std::vector<int>{1, 1, 1, 4, 99, 5, 6, 0, 99};
    ExecuteProgram(inputs, 12, 2);

    std::cout << "The value of position 0 is:" << inputs[0] << std::endl;
    std::cout << "Calculating the pair of inputs that answer 19690720" << std::endl;

    auto output = 19690720;
    inputs = inputs::GetInputs02();
    auto ans = FindAnswer(output, inputs);
    std::cout << "The answer of 100*noun+verb is: " << ans << std::endl;
}

} // namespace Day02
