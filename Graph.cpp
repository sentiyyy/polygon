#include "graph.h"

// ������� ��� �������� ����� �� �����
void load_graph(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);  // �������� �����
    std::string line;

    // ������ ����� ���������
    while (std::getline(file, line)) {
        std::stringstream ss(line);  // ���������� stringstream ��� ������� ������
        std::string part;

        // ���������� ������ �� ������� ':' ��� ��������� ��������� �������� �����
        std::getline(ss, part, ':');
        std::stringstream source_stream(part);
        double lat1, lon1;

        // ���������� ��������� ��������� �� ������� � ����������� � ����������
        std::getline(source_stream, part, ',');
        lat1 = std::stod(part);  
        std::getline(source_stream, part, ',');
        lon1 = std::stod(part);

        // ������ ������ - �����
        Point source{ lat1, lon1 };

        // ��������� ���� ������� ��� �������� �����, ���������� �� ������� ';'
        while (std::getline(ss, part, ';')) {
            std::stringstream target_stream(part);
            double lat2, lon2, cost;

            // ���������� ��������� ���� �� ������� � ����������� � �����
            std::getline(target_stream, part, ',');
            lat2 = std::stod(part);
            std::getline(target_stream, part, ',');
            lon2 = std::stod(part);
            std::getline(target_stream, part, ',');
            cost = std::stod(part);  // ��������� ���� �� �������� ����� � ����

            // ������ ������ ������� �����
            Point target{ lat2, lon2 };

            // ��������� ���� �� �������� ����� � ������� (��������������� ����)
            graph[source].emplace_back(target, cost);

            // ��������� �������� �����, ����� ���� �����������������
            graph[target].emplace_back(source, cost);
        }
    }
}

// ������� ��� ������ ��������� ����� � �����
Point find_nearest_point(const Graph& graph, double lat, double lon) {
    Point nearest_point;  // ���������� ��� �������� ��������� �����
    double min_distance = std::numeric_limits<double>::infinity();  // ���������� ������������� ����������� ���������� ��� �������������

    // �������� �� ���� ������ � �����
    for (const auto& pair : graph) {
        const Point& current_point = pair.first;

        // ���������� ���������� ����� ������� ������ � ��������� ������������
        double distance = std::sqrt(std::pow(current_point.lat - lat, 2) + std::pow(current_point.lon - lon, 2));

        // ���� ������� ���������� ������ ������������, ��������� ��������� �����
        if (distance < min_distance) {
            min_distance = distance;        // ��������� ����������� ����������
            nearest_point = current_point;  // ��������� ��������� �����
        }
    }

    // ���������� ��������� �����
    return nearest_point;
}