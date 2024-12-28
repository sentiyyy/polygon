#include "Dijkstra.h"

std::vector<Point> dijkstra(const Graph& graph, const Point& start, const Point& end) {
    // Хэш мап для хранения минимальных расстояний от начальной точки до других точек графа
    std::unordered_map<Point, double, PointHash> distances; // O(V); (16 + 8) * V = 24V байт

    // Хэш мап для хранения родительских точек, чтобы восстановить путь
    std::unordered_map<Point, Point, PointHash> parent; // O(V); (16 + 16) * V = 32V байт

    // Очередь с приоритетом для обработки точек с минимальным расстоянием
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> priority_queue; // O(V); 24V байт

    // Множество для отслеживания посещенных точек, чтобы не обрабатывать одну точку несколько раз
    std::unordered_set<Point, PointHash> visited; // O(V); 16V байт

    // Вектор для хранения пути от начальной до конечной точки (результат)
    std::vector<Point> path; // O(V); 16V байт

    // Инициализируем все точки с бесконечными расстояниями
    for (const auto& point : graph) {
        distances[point.first] = std::numeric_limits<double>::infinity(); // O(V); 16 + 8 = 24 байт
    }

    // Для начальной точки расстояние равно 0
    distances[start] = 0;

    // Добавляем начальную точку в очередь с приоритетом, её расстояние равно 0
    priority_queue.push({ 0, start }); // O(log V)

    // Пока очередь с приоритетом не пуста, продолжаем обработку
    while (!priority_queue.empty()) { // O(V)
        // Берём точку с минимальным расстоянием из очереди
        Point current = priority_queue.top().second;
        priority_queue.pop(); // O(log V)

        // Если точка уже была посещена, пропускаем её
        if (visited.find(current) != visited.end()) {
            continue;
        }

        // Помечаем текущую точку как посещенную
        visited.insert(current);

        // Получаем текущую точку из графа
        auto iterator = graph.find(current);
        // Проходим по всем соседям текущей точки
        for (const auto& neighbor : iterator->second) { // O(E), где E - кол-во ребер
            // Если сосед уже был посещен, пропускаем его
            if (visited.find(neighbor.first) != visited.end()) {
                continue;
            }

            Point next = neighbor.first;  // Следующая точка для обработки
            double new_dist = distances[current] + neighbor.second;  // Вычисляем новое расстояние до соседа

            // Если новое расстояние меньше текущего, обновляем его и добавляем в очередь с приоритетом
            if (new_dist < distances[next]) {
                distances[next] = new_dist;  // Обновляем минимальное расстояние для соседа
                parent[next] = current;      // Устанавливаем текущую точку как родителя для соседа
                priority_queue.push({ new_dist, next });  // Добавляем соседа в очередь с новым приоритетом; // O(log V)
            }
        }
    }

    // Восстанавливаем путь от конечной точки до начальной
    if (parent.find(end) != parent.end()) {  // Если конечная точка была достигнута
        path.push_back(end);         // Добавляем конечную точку в путь

        auto current = parent[end];  // Начинаем с родительской точки конечной

        // Проходим от конечной точки к начальной, восстанавливая путь
        while (current != start) { // O(p), где p - len пути
            path.push_back(current);    
            current = parent[current];  
        }

        path.push_back(start);  // Добавляем начальную точку в путь

        std::reverse(path.begin(), path.end());  // Переворачиваем путь, чтобы он был от начальной до конечной; O(p)
        return path;
    }

    // Если пути нет (например, точки не связаны), возвращаем пустой
    return {};

   // Итого по памяти примерно имеем 24V + 32V + 24V + 16V + 16V + 24 = 112V + 24 байт.
   // Общая временная сложность - O((V + E) * log V), где V - кол-во вершин, E - кол-во рёбер.
}
