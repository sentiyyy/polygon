#include "graph.h"

// Функция для загрузки графа из файла
void load_graph(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);  // Открытие файла
    std::string line;

    // Чтение файла построчно
    while (std::getline(file, line)) {
        std::stringstream ss(line);  // Используем stringstream для разбора строки
        std::string part;

        // Разделение строки по символу ':' для выделения координат исходной точки
        std::getline(ss, part, ':');
        std::stringstream source_stream(part);
        double lat1, lon1;

        // Разделение координат источника по запятой и конвертация в координаты
        std::getline(source_stream, part, ',');
        lat1 = std::stod(part);  
        std::getline(source_stream, part, ',');
        lon1 = std::stod(part);

        // Создаём объект - точка
        Point source{ lat1, lon1 };

        // Обработка всех соседей для исходной точки, разделение по символу ';'
        while (std::getline(ss, part, ';')) {
            std::stringstream target_stream(part);
            double lat2, lon2, cost;

            // Разделение координат цели по запятой и конвертация в числа
            std::getline(target_stream, part, ',');
            lat2 = std::stod(part);
            std::getline(target_stream, part, ',');
            lon2 = std::stod(part);
            std::getline(target_stream, part, ',');
            cost = std::stod(part);  // Стоимость пути от исходной точки к цели

            // Создаём объект целевой точки
            Point target{ lat2, lon2 };

            // Добавляем рёбра из исходной точки в целевую (ориентированный граф)
            graph[source].emplace_back(target, cost);

            // Добавляем обратное ребро, делая граф неориентированным
            graph[target].emplace_back(source, cost);
        }
    }
}

// Функция для поиска ближайшей точки в графе
Point find_nearest_point(const Graph& graph, double lat, double lon) {
    Point nearest_point;  // Переменная для хранения ближайшей точки
    double min_distance = std::numeric_limits<double>::infinity();  // Изначально устанавливаем минимальное расстояние как бесконечность

    // Проходим по всем точкам в графе
    for (const auto& pair : graph) {
        const Point& current_point = pair.first;

        // Вычисление расстояния между текущей точкой и заданными координатами
        double distance = std::sqrt(std::pow(current_point.lat - lat, 2) + std::pow(current_point.lon - lon, 2));

        // Если текущее расстояние меньше минимального, обновляем ближайшую точку
        if (distance < min_distance) {
            min_distance = distance;        // Обновляем минимальное расстояние
            nearest_point = current_point;  // Обновляем ближайшую точку
        }
    }

    // Возвращаем ближайшую точку
    return nearest_point;
}