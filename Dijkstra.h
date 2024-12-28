#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include "Graph.h"

std::vector<Point> dijkstra(const Graph& graph, const Point& start, const Point& end);