#include <string>
#include <iostream>
#include "inputs04.h"

namespace Day04
{
std::string GetText()
{
    return "You picked Day 04";
}

bool IsPasswordValid(int password)
{
    std::vector<int> digits;
    digits.push_back(password / 100000);
    password = password % 100000;
    digits.push_back(password / 10000);
    password = password % 10000;
    digits.push_back(password / 1000);
    password = password % 1000;
    digits.push_back(password / 100);
    password = password % 100;
    digits.push_back(password / 10);
    digits.push_back(password % 10);

    bool valid = false;
    auto previous = -1;
    for (auto i = 0; i < 5; i++)
    {
        if (digits[i] > digits[i + 1])
            return false;
        if (digits[i] == digits[i + 1])
        {
            if (i == 4)
            {
                if (digits[i] != previous)
                    valid = true;
            }
            else if (i == 0)
            {
                if (digits[i + 1] != digits[i + 2])
                    valid = true;
            }
            else
            {
                if (digits[i - 1] != digits[i] && digits[i + 1] != digits[i + 2])
                    valid = true;
            }
        }
        previous = digits[i];
    }
    return valid;
}
void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs04();

    std::cout << "Start is: " << input.first << " and end is: " << input.second << std::endl;
    auto password = input.first;

    password = 112233;
    auto valid = IsPasswordValid(password);
    std::cout << "Password: " << password << "is valid: " << valid << std::endl;

    password = 123444;
    valid = IsPasswordValid(password);
    std::cout << "Password: " << password << "is valid: " << valid << std::endl;

    password = 111122;
    valid = IsPasswordValid(password);
    std::cout << "Password: " << password << "is valid: " << valid << std::endl;
    auto count = 0;
    for (int i = input.first; i <= input.second; i++)
    {
        if (IsPasswordValid(i))
            count++;
    }

    std::cout << "In the given range the number of potential valid passwords is: " << count << std::endl;
}

} // namespace Day04
