#include "AStar.h"

// ������� ������������� ������ (��������� ����������)
double heuristic(const Point& a, const Point& b) {
    return std::sqrt(std::pow(a.lat - b.lat, 2) + std::pow(a.lon - b.lon, 2));
}

// �������� A* ��� ������ ����������� ���� � �����
std::vector<Point> a_star(const Graph& graph, const Point& start, const Point& end) {
    // ������� � ���������� �������� � ���, ��� �������� ������������� (���������) ��������� ����
    // ��� ��� ��������� ����
    std::unordered_map<Point, double, PointHash> g_cost; // O(V); (16 + 8) * V = 24V ���� 

    // ��� ��� ����� ��������� (g + ���������)
    std::unordered_map<Point, double, PointHash> f_cost; // O(V); (16 + 8) * V = 24V ����
    
    // ��� ��� ��� �������� ������������ ����� (��� �������������� ����)
    std::unordered_map<Point, Point, PointHash> parent; // O(V); (16 + 16) * V = 32V ����
    
    // ������� � ����������� ��� �������� �����, � ����������� �� ��������� f
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> priority_queue; // O(V); (16 + 8) * V = 24 ����

    // ������������� ���� ����� ������������ �����������
    for (const auto& pair : graph) {
        g_cost[pair.first] = std::numeric_limits<double>::infinity();  // ����������� ��������� g � �������������
        f_cost[pair.first] = std::numeric_limits<double>::infinity();  // ����������� ��������� f � �������������
    }

    // ��� ��������� ����� ��������� g = 0, ��������� f = ��������� �� start �� end
    g_cost[start] = 0;
    f_cost[start] = heuristic(start, end);

    priority_queue.push({ f_cost[start], start });  // ��������� ��������� ����� � ������� � �����������; O(log V)

    // ���� ������� �� �����, ���������� ������ ����
    while (!priority_queue.empty()) { // O(V)
        Point current = priority_queue.top().second;  // ��������� ����� � ���������� ���������� f
        priority_queue.pop(); // O(log V)

        // ���� ������� ����� � ����, �� ����������� ����� ����� � ��������������� ����
        if (current == end) {
            std::vector<Point> path;  // ������ ��� �������� ����
            while (current != start) {  // ���� �� �������� ��������� �����; O(p), ��� p - len ����.
                path.push_back(current);  // ��������� ������� ����� � ����
                current = parent[current];  // ��������� � ������������ �����
            }
            path.push_back(start);  // ��������� ��������� ����� � ����
            std::reverse(path.begin(), path.end());  // ������������� ���� (�� ����� � �������� �������); O(p)
            return path;  // ���������� ��������� ����
        }

        // �������� �� ���� ������� ������� �����
        for (const auto& neighbor : graph.at(current)) { // O(E)
            Point next = neighbor.first; 
            double tentative_g = g_cost[current] + neighbor.second;  // ������������ ��������� ��������� g ��� ������

            // ���� ������ ���� � ������� ���������� (g)
            if (tentative_g < g_cost[next]) {
                parent[next] = current;                              // ������������� ������� ����� ��� ������������ ��� ������
                g_cost[next] = tentative_g;                          // ��������� ��������� g ��� ������
                f_cost[next] = g_cost[next] + heuristic(next, end);  // ��������� ��������� f (g + ���������)
                priority_queue.push({ f_cost[next], next });         // ��������� ������ � �������
            }
        }
    }

    return {};  // ���� ���� �� ������, ���������� ������

   // ����� �� ������ �������� ����� 24V + 24V + 32V + 24V = 104 ����.
   // ����� ��������� ��������� - O((V + E) * log V), ��� V - ���-�� ������, E - ���-�� ����.
}

