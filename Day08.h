#include <string>
#include <iostream>
#include "inputs08.h"

namespace Day08
{
std::string GetText()
{
    return "You picked Day 08";
}


std::vector<std::vector<int>> BuildLayer(const std::string& input, int layerNum, int height, int width )
{
    auto pos = layerNum * (height*width);
    //auto end = start + (height+width);
    auto layer = std::vector<std::vector<int>>();
    layer.reserve(height);
    
    for ( int i=0; i<height; i++)
    {
        auto row = std::vector<int>();
        row.reserve(width);
        for (int j=0;j<width;j++)
        {
            int val = std::stoi(input.substr(pos, 1));
            row.push_back(val);
            pos++;
        }
        layer.push_back(row);
    }

    return layer;
}

std::vector<std::vector<std::vector<int>>> BuildImage(const std::string& input, int height, int width)
{
    auto inputCount = input.length();
    auto layerLength = height*width;
    auto layerCount = inputCount/layerLength;//input.length()/(height+width);
    auto image = std::vector<std::vector<std::vector<int>>>();
    image.reserve(layerCount);

    //auto layer = 0;
    auto row = 0;
    auto pos = 0;

    
    for (int i = 0; i<layerCount; i++)
    {
        auto layer = BuildLayer(input, i, height,width);
        image.push_back(layer);
    }

    // for (auto in : input)
    // {
    //     if ( pos = 0 )
    //     {
    //         image.push_back(std::vector<std::vector<int>>())
    //     }
    //     image[row].push_back(in);
    //     pos++;
    //     if ( pos == width)
    //     {
    //         pos = 0;
    //         row++;
    //     }
    // }

    return image;
}

int GetLayerCount(const std::vector<std::vector<int>>& layer, int val)
{
    int count = 0;
    for (auto i: layer)
        count += std::count(i.begin(), i.end(), val);
    return count;
}

std::vector<std::vector<int>> DecodeImage(const std::vector<std::vector<std::vector<int>>>& image,int height, int width)
{
    auto decoded = std::vector<std::vector<int>>();
    decoded.reserve(height);

    for ( int h=0; h<height; h++)
    {
        auto row = std::vector<int>(width, 2);
        //row.reserve(width);
        for (int pos = 0; pos<width; pos ++)
        {
            auto layerCount = 0;
            auto cont = true;
            while(cont)
            {
                auto layer = image[layerCount];
                if ( layer[h][pos] != 2)
                {
                    row[pos]= layer[h][pos];
                    cont = false;
                }
                else 
                    layerCount++;
            }
        }
        decoded.push_back(row);
    }
    return decoded;
}

void Process()
{
    std::cout << GetText() << std::endl;

    auto input = inputs::GetInputs08();
    //std::count << "Max string size : " << input.max_size() << std::endl;
    //input = "123456789012";
    //auto height = 2;
    //auto width = 3;
    auto height = 6;
    auto width = 25;
    auto image = BuildImage(input, height, width);

    auto layerNum = -1;
    auto minCount = (height*width)+1;
    for ( int i = 0; i< image.size(); i++)
    {
        auto count = GetLayerCount( image[i], 0);
        if ( count < minCount)
        {
            layerNum = i;
            minCount = count;
        }
    }

    int count1 = GetLayerCount(image[layerNum], 1);
    int count2 = GetLayerCount(image[layerNum],2);

    std::cout << "Count of 1 x Count of 2 in layer with min 0's is: " << count1*count2 << std::endl;

    // input="0222112222120000";
    // height=2;
    // width=2;
    // image = BuildImage(input,height,width);

    auto decodedImage = DecodeImage(image, height, width);
    std::cout << "The decoded image is: " << std::endl;
    for(auto row: decodedImage)
    {
        for (auto cell: row)
        {
            if ( cell ==1 )
                std::cout << cell;
            else
                std::cout << " ";
                
        }
            
        std::cout<< std::endl;
    }
}
} // namespace Day05
