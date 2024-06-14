#pragma once
#include "../Geometry/Point.h"
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
class Point_index
{
public:
    int x, y, z, i; 
    Point_index(int X, int Y, int Z) : x(X), y(Y), z(Z) {}

    Point_index(const Point& P, const double& map_size)
    {
        x = round(P.x / map_size);
        y = round(P.y / map_size);
        z = round(P.z / map_size);
    }
    Point_index(const Point& P, int _i, const double& map_size)
    {
        x = round(P.x / map_size);
        y = round(P.y / map_size);
        z = round(P.z / map_size);
        i = _i;
    }

    Point_index() { x = 0; y = 0; z = 0; }
    bool operator==(const Point_index& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    void print() const { cout << "(" << x << "," << y << "," << z << ")" << endl; }
    void print2() const { cout << "(" << x << "," << y << "," << z << ")"; }

};

struct Hash_of_Point_index {
    size_t operator() (const Point_index& P) const {
        return (P.x * 18397) + (P.y * 20483) + (P.z * 29303);
    }
};
typedef unordered_multimap< Point_index, int, Hash_of_Point_index> Point_Index_Map;
#define for_range(it,range) for(auto& it = range.first; it != range.second; ++it)
#define for_iter(it,range) for(auto& it = range.begin(); it != range.end(); ++it)

struct Bucket{
    int first, count;
    Bucket(int _first, int _count) : first(_first), count(_count) {}
};

typedef vector<Bucket> Buckets;
typedef vector<Point_index> Point_indexes;

class Space_map3
{
    double map_size;

public:
    Point_Index_Map point_map;
    Buckets buckets;
    Point_indexes point_indexes;

    void generate_cuda_hashmap() {
        int first = 0,count = 0;
        auto bucket_count = point_map.bucket_count();

        for (unsigned i = 0; i < bucket_count; ++i) {
            count = 0;
            for (auto local_it = point_map.begin(i); local_it != point_map.end(i); ++local_it)
            {
                point_indexes.emplace_back(local_it->first, local_it->second, map_size);
                count++;
            }
            buckets.emplace_back(first, count);
            first = first + count;
        }

    }

};
