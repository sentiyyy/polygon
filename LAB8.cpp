#include <iostream>
#include <chrono>
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "AStar.h"

void display_path(std::vector<Point> path) {
    for (const auto& point : path) {
        std::cout << "(" << point.lat << ", " << point.lon << ")\n";
    }
}


double get_path_cost(const Graph& graph, std::vector<Point> path) {
    double total_cost = 0.0;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        const Point& current_point = path[i];
        const Point& next_point = path[i + 1];

        // Find the cost between current_point and next_point
        for (const auto& neighbor : graph.at(current_point)) {
            if (neighbor.first == next_point) {
                total_cost += neighbor.second;
                break;
            }
        }
    }

    return total_cost;
}

void test() {
    Graph graph;
    load_graph("tst_graph.txt", graph);

    Point start = { 1, 1 };
    Point end = { 1, 3 };

    std::cout << "BFS:\n";
    auto path_bfs = bfs(graph, start, end);
    display_path(path_bfs);
    auto path_bfs_cost = get_path_cost(graph, path_bfs);
    std::cout << "Path cost: " << path_bfs_cost << "\n";
    std::cout << "\n";

    std::cout << "DFS:\n";
    auto path_dfs = dfs(graph, start, end);
    display_path(path_dfs);
    auto path_dfs_cost = get_path_cost(graph, path_dfs);
    std::cout << "Path cost: " << path_dfs_cost << "\n";
    std::cout << "\n";

    std::cout << "Dijkstra:\n";
    auto path_dijkstra = dijkstra(graph, start, end);
    display_path(path_dijkstra);
    auto path_dijkstra_cost = get_path_cost(graph, path_dijkstra);
    std::cout << "Path cost: " << path_dijkstra_cost << "\n";
    std::cout << "\n";

    std::cout << "AStar:\n";
    auto path_a_star = a_star(graph, start, end);
    display_path(path_a_star);
    auto path_a_star_cost = get_path_cost(graph, path_a_star);
    std::cout << "Path cost: " << path_a_star_cost << "\n";

    std::cout << "\n";
}

void real() {
    int runs = 3;

    Graph graph;
    load_graph("spb_graph.txt", graph);

    Point start = find_nearest_point(graph, 30.331975, 59.876368);
    Point end   = find_nearest_point(graph, 30.337795, 59.926835);

    std::cout << "BFS:\n";
    std::chrono::duration<double> duration_bfs(0);
    for (auto i = 0; i < runs; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto path = bfs(graph, start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Path consists of " << path.size() << " points\n";
        std::cout << "Execution time: " << duration.count() << " seconds\n";
        std::cout << "Path cost: " << get_path_cost(graph, path) << "\n";
        std::cout << "\n";
        duration_bfs += duration;
    }
    std::cout << "Average execution time: " << duration_bfs.count() / runs << " seconds\n";
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "DFS:\n";
    std::chrono::duration<double> duration_dfs(0);
    for (auto i = 0; i < runs; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto path = dfs(graph, start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Path consists of " << path.size() << " points\n";
        std::cout << "Execution time: " << duration.count() << " seconds\n";
        std::cout << "Path cost: " << get_path_cost(graph, path) << "\n";
        std::cout << "\n";
        duration_dfs += duration;
    }
    std::cout << "Average execution time: " << duration_dfs.count() / runs << " seconds\n";
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "Dijkstra:\n";
    std::chrono::duration<double> duration_dijkstra(0);
    for (auto i = 0; i < runs; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto path = dijkstra(graph, start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Path consists of " << path.size() << " points\n";
        std::cout << "Execution time: " << duration.count() << " seconds\n";
        std::cout << "Path cost: " << get_path_cost(graph, path) << "\n";
        std::cout << "\n";
        duration_dijkstra += duration;
    }
    std::cout << "Average execution time: " << duration_dijkstra.count() / runs << " seconds\n";
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "AStar:\n";
    std::chrono::duration<double> duration_a_star(0);
    for (auto i = 0; i < runs; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto path = a_star(graph, start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Path consists of " << path.size() << " points\n";
        std::cout << "Execution time: " << duration.count() << " seconds\n";
        std::cout << "Path cost: " << get_path_cost(graph, path) << "\n";
        std::cout << "\n";
        duration_a_star += duration;
    }
    std::cout << "Average execution time: " << duration_a_star.count() / runs << " seconds\n";
    std::cout << "\n";
    std::cout << "\n";
}

int main()
{
   // test();
    real();
    return 0;
}