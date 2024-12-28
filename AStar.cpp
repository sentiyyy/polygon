#include "AStar.h"

// Функция эвристической оценки (евклидово расстояние)
double heuristic(const Point& a, const Point& b) {
    return std::sqrt(std::pow(a.lat - b.lat, 2) + std::pow(a.lon - b.lon, 2));
}

// Алгоритм A* для поиска кратчайшего пути в графе
std::vector<Point> a_star(const Graph& graph, const Point& start, const Point& end) {
    // Разница с алгоритмом Дейкстры в том, что вводится эвристическая (оценочная) стоимость пути
    // Хэш мап стоимости пути
    std::unordered_map<Point, double, PointHash> g_cost; // O(V); (16 + 8) * V = 24V байт 

    // Хэш мап общей стоимости (g + эвристика)
    std::unordered_map<Point, double, PointHash> f_cost; // O(V); (16 + 8) * V = 24V байт
    
    // Хэш мап для хранение родительской точки (для восстановления пути)
    std::unordered_map<Point, Point, PointHash> parent; // O(V); (16 + 16) * V = 32V байт
    
    // Очередь с приоритетом для хранения точек, с сортировкой по стоимости f
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> priority_queue; // O(V); (16 + 8) * V = 24 байт

    // Инициализация всех точек бесконечными стоимостями
    for (const auto& pair : graph) {
        g_cost[pair.first] = std::numeric_limits<double>::infinity();  // Изначальная стоимость g — бесконечность
        f_cost[pair.first] = std::numeric_limits<double>::infinity();  // Изначальная стоимость f — бесконечность
    }

    // Для начальной точки стоимость g = 0, стоимость f = эвристика от start до end
    g_cost[start] = 0;
    f_cost[start] = heuristic(start, end);

    priority_queue.push({ f_cost[start], start });  // Добавляем начальную точку в очередь с приоритетом; O(log V)

    // Пока очередь не пуста, продолжаем искать путь
    while (!priority_queue.empty()) { // O(V)
        Point current = priority_queue.top().second;  // Извлекаем точку с наименьшей стоимостью f
        priority_queue.pop(); // O(log V)

        // Если текущая точка — цель, то заканчиваем обход графа и восстанавливаем путь
        if (current == end) {
            std::vector<Point> path;  // Массив для хранения пути
            while (current != start) {  // Пока не достигли начальной точки; O(p), где p - len пути.
                path.push_back(current);  // Добавляем текущую точку в путь
                current = parent[current];  // Переходим к родительской точке
            }
            path.push_back(start);  // Добавляем начальную точку в путь
            std::reverse(path.begin(), path.end());  // Разворачиваем путь (он будет в обратном порядке); O(p)
            return path;  // Возвращаем найденный путь
        }

        // Проходим по всем соседям текущей точки
        for (const auto& neighbor : graph.at(current)) { // O(E)
            Point next = neighbor.first; 
            double tentative_g = g_cost[current] + neighbor.second;  // Рассчитываем временную стоимость g для соседа

            // Если найден путь с меньшей стоимостью (g)
            if (tentative_g < g_cost[next]) {
                parent[next] = current;                              // Устанавливаем текущую точку как родительскую для соседа
                g_cost[next] = tentative_g;                          // Обновляем стоимость g для соседа
                f_cost[next] = g_cost[next] + heuristic(next, end);  // Обновляем стоимость f (g + эвристика)
                priority_queue.push({ f_cost[next], next });         // Добавляем соседа в очередь
            }
        }
    }

    return {};  // Если путь не найден, возвращаем пустой

   // Итого по памяти примерно имеем 24V + 24V + 32V + 24V = 104 байт.
   // Общая временная сложность - O((V + E) * log V), где V - кол-во вершин, E - кол-во рёбер.
}

