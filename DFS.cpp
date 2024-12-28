#include "DFS.h"

std::vector<Point> dfs(const Graph& graph, const Point& start, const Point& end) {
    // Основное отличие в реализации BFS и DFS - в DFS используется очередь
    // Стек для хранения точек, которые нужно обработать
    std::stack<Point> stack; // 16n байт

    // Хэш мап для хранение родительской точки для каждой посещенной точки (для восстановления пути)
    std::unordered_map<Point, Point, PointHash> parent; // (16 + 16) * n = 32n байта

    // Хэш множество для отслеживания посещенных точек
    std::unordered_set<Point, PointHash> visited; // 16n байт

    // Вектор для хранения пути от начальной до конечной точки (результат)
    std::vector<Point> path; // 16k байт

    // Добавляем начальную точку в стек и помечаем как посещенную
    stack.push(start); // 16 байт
    visited.insert(start); // 16 байт

    // Пока стек не пуст, продолжаем обработку
    while (!stack.empty()) { // O(V), где V - количество вершин
        // Извлекаем текущую точку из стека
        Point current = stack.top(); // 16 байт
        stack.pop(); // - 16 байт

        // Если мы достигли конечной точки, восстанавливаем путь
        if (current == end) {
            // Восстанавливаем путь от конечной точки до начальной
            while (current != start) { // O(V)
                path.push_back(current); // 16 байт
                current = parent[current];  // Переходим к родительской точке
            }
            path.push_back(start);                   // Добавляем начальную точку в путь; 16 байт
            std::reverse(path.begin(), path.end());  // Путь строится в обратном порядке, поэтому переворачиваем его
            return path;
        }

        // Получаем текущую точку из графа
        auto iterator = graph.find(current);

        // Проходим по всем соседям текущей точки
        for (const auto& neighbor : iterator->second) { // O(E), где E - кол-во ребер
            Point next = neighbor.first;  // Следующая точка для обработки

            // Если точка еще не была посещена, добавляем ее в стек
            if (visited.find(next) == visited.end()) {
                visited.insert(next);    // Помечаем точку как посещенную; 16 байт
                parent[next] = current;  // Устанавливаем родительскую точку; 16 байт
                stack.push(next);        // Добавляем соседнюю точку в стек; 16 байт
            }
        }
    }

    // Если путь не найден, возвращаем пустой
    return {};

   // Итого по памяти примерно имеем 16n + 32n + 16n + 16k + 16 + 16 + 16 - 16 + 16 + 16 + 16 + 16 + 16 = 64n + 16k + 112 байт.
   // Общая временная сложность - обработка всех рёбер O(E) + O(V) = O(V + E), где V - кол-во вершин, E - кол-во рёбер.
}
