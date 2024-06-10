#pragma once
/*
#include <tuple>
typedef long long int Lint;
typedef Lint Key;
typedef pair<int, int> Node_Pair;
typedef vector<Lint> Octet;

// Point Hash functor
struct Hash_of_Point {
    size_t operator() (const Point& P) const {
        constexpr int order = 1e3;
        int Px = round(P.x * order);
        int Py = round(P.y * order);
        int Pz = round(P.z * order);
        return (Px * 18397) + (Py * 20483) + (Pz * 29303);
    }
};

// Point Equal functor
struct Equal_of_Point {
    bool operator()(const Point& P1, const Point& P2) const {
        return is_near_by(P1, P2);
    }
};


// Edge Hash functor
struct Hash_of_Edge {
    size_t operator() (const Edge& P) const {
        auto n0 = P.node[0];
        auto n1 = P.node[1];
        if (n0 < n1) return n0 * 18397 + n1 * 20483;
        return n1 * 18397 + n0 * 20483;
    }
};

// Edge Equal functor
struct Equal_of_Edge {
    bool operator()(const Edge& P1, const Edge& P2) const {
        auto a0 = P1.node[0];        auto a1 = P1.node[1];
        auto b0 = P2.node[0];        auto b1 = P2.node[1];

        if (a0 == b0 && a1 == b1) return true;
        if (a1 == b0 && a0 == b1) return true;

        return false;
    }
};

//typedef unordered_map< Point, Points> Point_Hash;
//typedef unordered_map< Point, Nodes > Node_Hash;

typedef unordered_multimap< Point, int, Hash_of_Point, Equal_of_Point> Point_Hash;


class Finder {
public:
    static Point_Hash point_hash;
    static Edge_Hash edge_hash;
    static Lint oct[27];

    static void add_point(Point& P, int index) { point_hash.emplace(P, index); }
    static void add_edge(int i, int j, int index) { edge_hash.emplace(Edge(i, j), index); }

    static void initialize_hash(int node_num, int edge_num) {
        //FOR(i, j, k) octet(i, j, k) = hasher(i-1, j - 1, k-1);
        point_hash.reserve(node_num);
        edge_hash.reserve(edge_num);
    }

    static int lookup_point(Nodes& nodes, Point& P) {
        //auto hash_P = hasher(P);
        //auto hash_value = hash_P + octet(i, j, k);//Using memonization
        auto count = point_hash.count(P);

        if (count > 0) {
            auto range = point_hash.equal_range(P);

            for_range(it, range) {
                int node_index = it->second;
                if (is_near_by(nodes[node_index], P))
                    return node_index;
            }
        }

        add_point(P, nodes.size());
        return NODE_NOT_FOUND;
    }
}
*/

