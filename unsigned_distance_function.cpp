// unsigned_distance_function.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Point.h"
typedef vector<Point> Points;

float unsigned_distance(const Points &points, const Point &target, int &nearest_point) {
    nearest_point = 0;
    float min_dist = target.dist(points[0]);
    int i = 0;
    for (const Point &p: points)
    {
        float dist = target.dist(p);
        if (dist < min_dist)
        {
            min_dist = dist;
            nearest_point = i;
        }
        i++;
    }
    return min_dist;
}

int main()
{
    Points points = {Point(0,0,0),Point(0,0,1),Point(0,1,1),Point(0,1,0)};
    int nearest_point;
    Point target = { 2,2,2 };
    std::cout << "Hello World!\n";
    float dist = unsigned_distance(points, target, nearest_point);
    std::cout << dist<<endl;
    std::cout << nearest_point << endl;
    target.print();
    points[nearest_point].print();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
