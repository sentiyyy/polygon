#include "Dijkstra.h"

std::vector<Point> dijkstra(const Graph& graph, const Point& start, const Point& end) {
    // ��� ��� ��� �������� ����������� ���������� �� ��������� ����� �� ������ ����� �����
    std::unordered_map<Point, double, PointHash> distances; // O(V); (16 + 8) * V = 24V ����

    // ��� ��� ��� �������� ������������ �����, ����� ������������ ����
    std::unordered_map<Point, Point, PointHash> parent; // O(V); (16 + 16) * V = 32V ����

    // ������� � ����������� ��� ��������� ����� � ����������� �����������
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> priority_queue; // O(V); 24V ����

    // ��������� ��� ������������ ���������� �����, ����� �� ������������ ���� ����� ��������� ���
    std::unordered_set<Point, PointHash> visited; // O(V); 16V ����

    // ������ ��� �������� ���� �� ��������� �� �������� ����� (���������)
    std::vector<Point> path; // O(V); 16V ����

    // �������������� ��� ����� � ������������ ������������
    for (const auto& point : graph) {
        distances[point.first] = std::numeric_limits<double>::infinity(); // O(V); 16 + 8 = 24 ����
    }

    // ��� ��������� ����� ���������� ����� 0
    distances[start] = 0;

    // ��������� ��������� ����� � ������� � �����������, � ���������� ����� 0
    priority_queue.push({ 0, start }); // O(log V)

    // ���� ������� � ����������� �� �����, ���������� ���������
    while (!priority_queue.empty()) { // O(V)
        // ���� ����� � ����������� ����������� �� �������
        Point current = priority_queue.top().second;
        priority_queue.pop(); // O(log V)

        // ���� ����� ��� ���� ��������, ���������� �
        if (visited.find(current) != visited.end()) {
            continue;
        }

        // �������� ������� ����� ��� ����������
        visited.insert(current);

        // �������� ������� ����� �� �����
        auto iterator = graph.find(current);
        // �������� �� ���� ������� ������� �����
        for (const auto& neighbor : iterator->second) { // O(E), ��� E - ���-�� �����
            // ���� ����� ��� ��� �������, ���������� ���
            if (visited.find(neighbor.first) != visited.end()) {
                continue;
            }

            Point next = neighbor.first;  // ��������� ����� ��� ���������
            double new_dist = distances[current] + neighbor.second;  // ��������� ����� ���������� �� ������

            // ���� ����� ���������� ������ ��������, ��������� ��� � ��������� � ������� � �����������
            if (new_dist < distances[next]) {
                distances[next] = new_dist;  // ��������� ����������� ���������� ��� ������
                parent[next] = current;      // ������������� ������� ����� ��� �������� ��� ������
                priority_queue.push({ new_dist, next });  // ��������� ������ � ������� � ����� �����������; // O(log V)
            }
        }
    }

    // ��������������� ���� �� �������� ����� �� ���������
    if (parent.find(end) != parent.end()) {  // ���� �������� ����� ���� ����������
        path.push_back(end);         // ��������� �������� ����� � ����

        auto current = parent[end];  // �������� � ������������ ����� ��������

        // �������� �� �������� ����� � ���������, �������������� ����
        while (current != start) { // O(p), ��� p - len ����
            path.push_back(current);    
            current = parent[current];  
        }

        path.push_back(start);  // ��������� ��������� ����� � ����

        std::reverse(path.begin(), path.end());  // �������������� ����, ����� �� ��� �� ��������� �� ��������; O(p)
        return path;
    }

    // ���� ���� ��� (��������, ����� �� �������), ���������� ������
    return {};

   // ����� �� ������ �������� ����� 24V + 32V + 24V + 16V + 16V + 24 = 112V + 24 ����.
   // ����� ��������� ��������� - O((V + E) * log V), ��� V - ���-�� ������, E - ���-�� ����.
}
