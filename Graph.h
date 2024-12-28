#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

struct Point {
    double lat;
    double lon;

    bool operator==(const Point& other) const {
        return lat == other.lat && lon == other.lon;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    bool operator<(const Point& other) const {
        return lat < other.lat || (lat == other.lat && lon < other.lon);
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return std::hash<double>()(p.lat) ^ (std::hash<double>()(p.lon) << 1);
    }
};

using Graph = std::unordered_map<Point, std::vector<std::pair<Point, double>>, PointHash>;

void load_graph(const std::string& filename, Graph& graph);
Point find_nearest_point(const Graph& graph, double lat, double lon);
