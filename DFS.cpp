#include "DFS.h"

std::vector<Point> dfs(const Graph& graph, const Point& start, const Point& end) {
    // �������� ������� � ���������� BFS � DFS - � DFS ������������ �������
    // ���� ��� �������� �����, ������� ����� ����������
    std::stack<Point> stack; // 16n ����

    // ��� ��� ��� �������� ������������ ����� ��� ������ ���������� ����� (��� �������������� ����)
    std::unordered_map<Point, Point, PointHash> parent; // (16 + 16) * n = 32n �����

    // ��� ��������� ��� ������������ ���������� �����
    std::unordered_set<Point, PointHash> visited; // 16n ����

    // ������ ��� �������� ���� �� ��������� �� �������� ����� (���������)
    std::vector<Point> path; // 16k ����

    // ��������� ��������� ����� � ���� � �������� ��� ����������
    stack.push(start); // 16 ����
    visited.insert(start); // 16 ����

    // ���� ���� �� ����, ���������� ���������
    while (!stack.empty()) { // O(V), ��� V - ���������� ������
        // ��������� ������� ����� �� �����
        Point current = stack.top(); // 16 ����
        stack.pop(); // - 16 ����

        // ���� �� �������� �������� �����, ��������������� ����
        if (current == end) {
            // ��������������� ���� �� �������� ����� �� ���������
            while (current != start) { // O(V)
                path.push_back(current); // 16 ����
                current = parent[current];  // ��������� � ������������ �����
            }
            path.push_back(start);                   // ��������� ��������� ����� � ����; 16 ����
            std::reverse(path.begin(), path.end());  // ���� �������� � �������� �������, ������� �������������� ���
            return path;
        }

        // �������� ������� ����� �� �����
        auto iterator = graph.find(current);

        // �������� �� ���� ������� ������� �����
        for (const auto& neighbor : iterator->second) { // O(E), ��� E - ���-�� �����
            Point next = neighbor.first;  // ��������� ����� ��� ���������

            // ���� ����� ��� �� ���� ��������, ��������� �� � ����
            if (visited.find(next) == visited.end()) {
                visited.insert(next);    // �������� ����� ��� ����������; 16 ����
                parent[next] = current;  // ������������� ������������ �����; 16 ����
                stack.push(next);        // ��������� �������� ����� � ����; 16 ����
            }
        }
    }

    // ���� ���� �� ������, ���������� ������
    return {};

   // ����� �� ������ �������� ����� 16n + 32n + 16n + 16k + 16 + 16 + 16 - 16 + 16 + 16 + 16 + 16 + 16 = 64n + 16k + 112 ����.
   // ����� ��������� ��������� - ��������� ���� ���� O(E) + O(V) = O(V + E), ��� V - ���-�� ������, E - ���-�� ����.
}
