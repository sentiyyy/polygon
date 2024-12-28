#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>
#include "Graph.h"

std::vector<Point> a_star(const Graph& graph, const Point& start, const Point& goal);
