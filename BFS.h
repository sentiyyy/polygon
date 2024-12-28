#pragma once
#include <queue>
#include <vector>
#include "Graph.h"

std::vector<Point> bfs(const Graph& graph, const Point& start, const Point& end);
