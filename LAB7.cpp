#include <vector>

using namespace std;

class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        // Сортируем длины горизонтальных и вертикальных разрезов торта в порядке убывания.
        sort(horizontalCut.rbegin(), horizontalCut.rend()); // O(n log n), где n - кол-во горизонтальных разрезов торта.
        sort(verticalCut.rbegin(), verticalCut.rend()); // O(k log k), где k - кол-во вертикальных разрезов торта.

        long long totalCost = 0; // Общая стоимость разрезов всего торта; 8 байт.
        long long horizontalPiecesOfCake = 1; // Разрезанные горизонтальные куски торта (изначально имеем 1 кусок); 8 байт.
        long long verticalPiecesOfCake = 1; // Разрезанные вертикальные куски торта (изначально имеем 1 кусок); 8 байт.

        int i = 0; // Разрез торта по горизонтальной линии; 4 байта.
        int j = 0; // Разрез торта по вертикальной линии; 4 байта.

        while (i < horizontalCut.size() or j < verticalCut.size()) { // O(n + k).
            if (i < horizontalCut.size() and (j >= verticalCut.size() or horizontalCut[i] >= verticalCut[j])) { // O(1).
                totalCost += horizontalCut[i] * verticalPiecesOfCake; // Добавление к общей стоимости стоимость разреза.
                horizontalPiecesOfCake++; // Увеличение количества горизонтальных кусков торта.
                i++; // Переход к следующему горизонтальному разрезу.
            }
            else {
                totalCost += verticalCut[j] * horizontalPiecesOfCake;
                verticalPiecesOfCake++;
                j++;
            }
        }

        return totalCost;
    }
    // Итого, что касаемо памяти, в циклах не происходит динамического выделения памяти, тогда по памяти мы примерно имеем 8 + 8 + 8 + 4 + 4 = 32 байта. 
    // Общая временная сложность - O(n log n + k log k), где n и k - это кол-во горизонтальных и вертикальных разрезов торта соответственно.
};