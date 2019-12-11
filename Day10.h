#include <string>
#include <iostream>
#include "inputs10.h"
#include <cmath>
#include <set>

namespace Day10
{
std::string GetText()
{
    return "You picked Day 10";
}

std::vector<std::pair<int,int>> FindAsteroids(const std::vector<std::string>& input)
{
    std::vector<std::pair<int,int>> asteroids;
    for (int i=0; i< input.size(); i++)
    {
        auto line = input[i];
        std::size_t found =0;
        std::size_t start=0;
        while( found != std::string::npos )
        {
            found = line.find("#", start);
            if ( found != std::string::npos)
            {
                start = found +1;
                asteroids.push_back(std::make_pair(found, i));
            }
        }
    }

    return asteroids;
}

float Distance(const std::pair<int,int>& pt1, const std::pair<int,int>& pt2)
{
    auto x = (pt1.first - pt2.first)*(pt1.first-pt2.first);
    auto y = (pt1.second - pt2.second)*(pt1.second-pt2.second);

    return sqrt(x+y);
}

bool FloatsEq(float a, float b, float epsilon = 0.0000000000000000001f)
{
    return ( fabs(a-b)<epsilon);
}

struct Vec2
{
    float x;
    float y;
 
    const Vec2 operator-( const Vec2& a )
    {
        Vec2 v;
        v.x = x - a.x;
        v.y = y - a.y;
 
        return v;
    }
 
    const Vec2 operator*( float a ) const
    {
        Vec2 v;
        v.x = x * a;
        v.y = y * a;
 
        return v;
    }
};
 
float Dot( const Vec2& a, const Vec2& b )
{
    return a.x * b.x + a.y * b.y;
}

bool IsPointInBetween(std::pair<float,float>& start, std::pair<float,float> end, std::pair<int,int>& pt )
{
    Vec2 a,b,p;
    a.x = start.first;
    a.y = start.second;
    b.x = end.first;
    b.y = end.second;
    p.x = pt.first;
    p.y = pt.second;

    Vec2 n = b-a;
    Vec2 pa = a-p;
    Vec2 c = n*(Dot(n,pa)/Dot(n,n));
    Vec2 d= pa-c;

    auto cPt = Dot(n,pa);
    if ( cPt > 0.0f)
        return false; //closest to a

    Vec2 bp = p-b;
    if ( Dot(n,bp) > 0.0f)
        return false;// pt is closest to b
        
    float d2 = Dot(d,d);
    if ( d2< .0005f)
    {
        return true;
    }

    return false;
}
std::pair<std::pair<int,int>,int> FindMaxDetectable(const std::vector<std::pair<int,int>>& asteroids)
{
    auto maxCount = -1;
    std::pair<int,int> bestMatch;
    for( int i =0; i<asteroids.size(); i++)
    {
        auto count = 0;
        auto ast = asteroids[i];
        for (auto target: asteroids)
        {
            auto blocked = false;
            if ( ast == target)
                continue;
            for (auto point3 : asteroids)
            {
                if ( ast == point3 || target==point3)
                    continue;
                
                Vec2 a,b,p;
                a.x = ast.first;
                a.y = ast.second;
                b.x = target.first;
                b.y = target.second;
                p.x = point3.first;
                p.y = point3.second;

                Vec2 n = b-a;
                Vec2 pa = a-p;
                Vec2 c = n*(Dot(n,pa)/Dot(n,n));
                Vec2 d= pa-c;

                auto cPt = Dot(n,pa);
                if ( cPt > 0.0f)
                    continue; //closest to a

                Vec2 bp = p-b;
                if ( Dot(n,bp) > 0.0f)
                    continue;// pt is closest to b
                    
                float d2= Dot(d,d);
                if ( d2 < .0005f)
                {

                    blocked = true;
                    break;
                }
            //     auto dist1 = Distance(ast,point3);
            //     auto dist2 = Distance(point3, target);
            //     auto dist3 = Distance(ast,target);
            //     if ( FloatsEq(dist1+dist2,dist3))
            //     {
            //         blocked = true;
            //         break;
            //     }

            }
            if (blocked == false)
                count ++;

        }

        if ( count > maxCount)
        {
            maxCount = count;
            bestMatch = ast;
        }
    }

    return std::make_pair(bestMatch, maxCount);
}


void rotate( const std::pair<float,float>& start, const std::pair<float,float>& end, double angle, std::pair<float,float>& newEnd)
{
    // a and b are arrays of length 2 with the x, y coordinate of
    // your segments extreme points with the form [x, y]
    
    std::pair<float,float> adjustedEnd = std::make_pair(end.first-start.first, end.second-start.second );

    // // Use the rotation matrix from the paper you mentioned
    // a_rotated = [
    //     cos(angle)*a_mid[0] - sin(angle)*a_mid[1],
    //     sin(angle)*a_mid[0] + cos(angle)*a_mid[1]
    // ]
    std::pair<float,float> rotatedEnd = std::make_pair((float)( cos(angle)*adjustedEnd.first - sin(angle)*adjustedEnd.second),
        (float)(sin(angle)*adjustedEnd.first + cos(angle)*adjustedEnd.second));
    // b_rotated = [
    //     cos(angle)*b_mid[0] - sin(angle)*b_mid[1],
    //     sin(angle)*b_mid[0] + cos(angle)*b_mid[1]
    // ]

    // Then add the midpoint coordinates to return to previous origin
    // a_rotated[0] = a_rotated[0] + midpoint[0]
    // a_rotated[1] = a_rotated[1] + midpoint[1]
    newEnd = std::make_pair( (float) (rotatedEnd.first + start.first), (float) (rotatedEnd.second+start.second));
    //b_rotated[1] = b_rotated[1] + midpoint[1]

    // And the rotation is now done
    //return std::m
}

std::pair<int,int> BlastAsteroids(const std::vector<std::pair<int,int>>& asteroids, const std::pair<int,int>& firePoint,  int maxToDestroy)
{
    //auto locations = asteroids;

    std::vector<std::pair<std::pair<int,int>,double>> locations;
    std::map<double,std::vector<std::pair<int,int>>> thetaMap;
    std::set<double> thetaSet;
    auto PI = std::atan(1.0)*4.0;

    for (auto i: asteroids)
    {
        if (i == firePoint)
            continue;

        auto theta = -1.0;

        if ( i.first == firePoint.first && i.second > firePoint.second )
            theta = 180.0; //straight down
        else if ( i.first == firePoint.first && i.second < firePoint.second )
            theta = 0.0; //striaght up
        else if ( i.second == firePoint.second && i.first > firePoint.first)
            theta = 90.0; // straight right
        else if ( i.second == firePoint.second && i.first < firePoint.first)
            theta = 270.0; //straight left
        else if ( i.second < firePoint.second && i.first > firePoint.first) //quad 1 - quad 1
        {
            auto nom = (double)i.second - (double)firePoint.second;
            auto denom = (double) i.first-(double)firePoint.first;
            auto thetaOrg = atan(nom/denom)*180.0/PI;
            // auto thetaOrg =  atan((i.second-firePoint.second)/(i.first-firePoint.first)) *180.0/PI;
            theta = 90.0 + thetaOrg;//theta = atan((i.second-firePoint.second)/(i.first-firePoint.first));
        }
        else if ( i.second < firePoint.second && i.first < firePoint.first)//quad 2 - quad 4
        {
            auto nom = (double)i.second - (double)firePoint.second;
            auto denom = (double) firePoint.first-(double)i.first;
            auto thetaOrg = atan(nom/denom)*180.0/PI;
            //auto thetaOrg =  atan((i.second-firePoint.second)/(firePoint.first-i.first)) *180.0/PI;
            thetaOrg += 180.0; 
            theta = 270.0 + (180.0-thetaOrg);
        }
        else if ( i.second > firePoint.second && i.first<firePoint.first) //quad 3 - quad 3
        {
            auto nom = (double)firePoint.second - (double)i.second;
            auto denom = (double) i.first-(double)firePoint.first;
            auto thetaOrg = atan(nom/denom)*180.0/PI;
            //auto thetaOrg =  atan((firePoint.second-i.second)/(i.first-firePoint.first)) *180.0/PI;
            thetaOrg += 180.0;
            theta = 180.0 + (270.0-thetaOrg);
        }
        else if (i.second > firePoint.second && i.first>firePoint.first) //quad 4 - quad 2
        {
            auto nom = (double)firePoint.second - (double)i.second;
            auto denom = (double) i.first-(double)firePoint.first;
            auto thetaOrg = atan(nom/denom)*180.0/PI;
            //auto thetaOrg =  atan((firePoint.second - i.second)/(i.first-firePoint.first)) *180.0/PI;
            auto temp = atan(-1.0/2.0);
            temp = temp*180.0/PI;
            thetaOrg += 360.0;
            theta = 90.0 + (360.0-thetaOrg);
        }

        std::make_pair(i, theta);
        auto it = thetaMap.find(theta);
        if ( it == thetaMap.end() )
        {
            std::vector<std::pair<int,int>> points {i};
            thetaMap.insert(std::make_pair(theta,points));
            thetaSet.insert(theta);            
        }
        else
        {
            thetaMap[theta].push_back(i);
        }
        
    }
    // auto destroyed = 0;
    // auto angle = 0.0;
    // float PI = std::atan(1.0)*4.0f;
    // //auto rads = angle*PI/180;
    // auto x = firePoint.first;
    // auto height = asteroids.size()+1;
    // auto y = firePoint.second-(int)height;
    // std::pair<float,float> originalEnd = std::make_pair( (float)x, (float)y);
    // std::pair<int,int> lastDestroyed;

    // std::pair<float,float> originalStart = std::make_pair((float)firePoint.first, (float)(firePoint.second));
    std::vector<std::pair<int,int>> destroyed;
    auto cont = true;
    auto previousDestroyed = -1;
    while (destroyed.size() != previousDestroyed)
    {
        previousDestroyed = destroyed.size();
        for (auto theta:thetaSet)
        {
            auto potentials = thetaMap[theta];

            auto minIndex =-1;
            auto minDist = -1;
            for (int i=0; i< potentials.size(); i++)
            {
                auto dist = Distance(firePoint, potentials[i]);
                if ( i == 0 ||dist < minDist)
                {
                    minDist = dist;
                    minIndex = i;
                }
            }

            if ( minDist != -1)
            {
                destroyed.push_back(potentials[minIndex]);
                //potentials.erase(potentials.begin()+minIndex);
                thetaMap[theta].erase(thetaMap[theta].begin()+minIndex);
            }
        }
    }
    return destroyed[maxToDestroy-1];
}


void Process()
{
    std::cout << GetText() << std::endl;
    auto input = inputs::GetInputs10();

    // input = std::vector<std::string>{
    //     ".#..#",
    //     ".....",
    //     "#####",
    //     "....#",
    //     "...##" 
    //     };

    //ex1 best 5,8 with 33    
    // input = std::vector<std::string>{
    //     "......#.#.",
    //     "#..#.#....",
    //     "..#######.",
    //     ".#.#.###..",
    //     ".#..#.....",
    //     "..#....#.#",
    //     "#..#....#.",
    //     ".##.#..###",
    //     "##...#..#.",
    //     ".#....####"
    //     };

    //ex 2 best 1,2 with 35
    // input = std::vector<std::string>
    // {
    // "#.#...#.#.",
    // ".###....#.",
    // ".#....#...",
    // "##.#.#.#.#",
    // "....#.#.#.",
    // ".##..###.#",
    // "..#...##..",
    // "..##....##",
    // "......#...",
    // ".####.###."
    // };

    //ex 3 best 11,13 with 210
    // input = std::vector<std::string> 
    // {
    // ".#..##.###...#######",
    // "##.############..##.",
    // ".#.######.########.#",
    // ".###.#######.####.#.",
    // "#####.##.#.##.###.##",
    // "..#####..#.#########",
    // "####################",
    // "#.####....###.#.#.##",
    // "##.#################",
    // "#####.##.###..####..",
    // "..######..##.#######",
    // "####.##.####...##..#",
    // ".#####..#.######.###",
    // "##...#.##########...",
    // "#.##########.#######",
    // ".####.#.###.###.#.##",
    // "....##.##.###..#####",
    // ".#.#.###########.###",
    // "#.#.#.#####.####.###",
    // "###.##.####.##.#..##"
    // };
    auto asteroids = FindAsteroids(input);
    std::cout << "Found " <<asteroids.size()<<std::endl;

    auto detected = FindMaxDetectable(asteroids);

    std::cout<<"The best match of ("<< detected.first.first<<","<<detected.first.second<<") with a detection of: " << detected.second<<std::endl;

    auto destroyed = BlastAsteroids(asteroids, detected.first, 200);

    std::cout << "The 200th asteroid destroyed was located at: "<<destroyed.first<<","<<destroyed.second<<std::endl;
    std::cout << "The answer to Xcoord * 100 + Y coord is: " << (destroyed.first*100)+destroyed.second<< std::endl;
    // auto start = std::make_pair(0.0f,0.0f);
    // auto end = std::make_pair(0.0f, 10.0f);
    // std::pair<float,float> newEnd;

    // double angle = -90.0;
    // float PI = std::atan(1.0)*4.0f;
    // auto rads = angle*PI/180;

    // auto startFloat = std::make_pair((float) start.first, (float)start.second);
    // auto endFloat = std::make_pair((float)end.first, (float)end.second);
    // rotate(startFloat,endFloat,rads, newEnd);
    // std::cout<<"new end point is: "<< newEnd.first <<","<<newEnd.second<<std::endl;

}

} // namespace Day04
