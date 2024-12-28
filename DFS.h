#pragma once
#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>
#include <unordered_set>
#include "Graph.h"

std::vector<Point> dfs(const Graph& graph, const Point& start, const Point& end);