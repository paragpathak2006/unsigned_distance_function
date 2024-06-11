// unsigned_distance_function.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Point.h"
#include "Finder.h"
#include "Space_map2.h"
#include "Loader.h"

// fStream - STD File I/O Library
#include <fstream>

float unsigned_distance_brute_force(const Points &points, const Point &target, double beta, int &nearest_point) {
    nearest_point = -1;
    float min_dist = target.dist(points[0]);
    int i = 0;
    double beta2 = beta * beta;
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
    return (min_dist > beta2) ? beta2 : min_dist;
}

double unsigned_distance_space_map(const Points& points, const Point& target, double beta, double map_size, int& nearest_point) {

    nearest_point = -1;
    Space_map::initialize_space_map(/* with input points as */ points,/* map_size as */ map_size, /*  and beta as */ beta);
    double unsigned_dist = Space_map::search_space_map(points, target, nearest_point);
    Space_map::make_empty();

    return unsigned_dist;
}

double unsigned_distance_space_map2(const Points& points, const Point& target, double beta, double map_size, int& nearest_point) {

    nearest_point = -1;
    Space_map2 space_map(/* with input points as */ points, /* map_size as */ map_size);
    double unsigned_dist = space_map.search_space_map(points, target, beta, nearest_point);
    space_map.make_empty();
    return unsigned_dist;
}

void print_output(float dist, int nearest_point, const Point& target, const Points& points){
    cout << "Unsigned distance : " << sqrt(dist) << endl;
    cout << "Target point : "; target.print();
    cout << "Nearest point : "; 
    if (nearest_point >= 0) points[nearest_point].print();
    else cout << "Point not found!" << endl;

    cout << endl << endl;
}


int main()
{
//    load_file();

    Point target = { 0,1,1.2 };
    double beta = 2;
    double map_size = 0.5;
    // Points points = {Point(0,0,0),Point(0,0,1),Point(0,1,1),Point(0,1,0)};
    Points points;

    objl::Mesh mesh;
    get_mesh("piston.obj", mesh);
    get_points(mesh, points);

    int nearest_point1;
    int nearest_point2;

    cout << "Beta : " << beta <<endl;    
    cout << "Map_size : " << map_size << endl << endl;
    cout << "Target point : "; target.print();
    cout << "Points : " << endl;

//    for(const Point& p : points) p.print();

    cout << "------------------------------------------------------" << endl;
    cout << endl;
    cout << "Unsigned_distance_space_map Debug log" << endl;
    float dist2 = unsigned_distance_space_map2(points, target, beta, map_size, nearest_point2);
    cout << endl << endl;

    cout << "******************************************************************" << endl << endl;
    cout << "Unsigned_distance_brute_force output" << endl;
    float dist1 = unsigned_distance_brute_force(points, target, beta, nearest_point1);
    print_output(dist1, nearest_point1, target, points);

    cout << "------------------------------------------------------" << endl << endl;
    cout << "Unsigned_distance_space_map output..." << endl;
    print_output(dist2, nearest_point2, target, points);

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
