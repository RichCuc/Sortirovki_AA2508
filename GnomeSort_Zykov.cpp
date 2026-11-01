#include "GnomeSort_Zykov.h"

#include <utility>

// Гномья сортировка целых чисел по возрастанию.
std::vector<int> gnomeSort(std::vector<int> arr) {
    int i = 0;
    int n = static_cast<int>(arr.size());
    while (i < n) {
        if (i == 0 || arr[i - 1] <= arr[i]) {
            ++i;
        } else {
            std::swap(arr[i - 1], arr[i]);
            --i;
        }
    }
    return arr;
}

// Гномья сортировка вещественных чисел по возрастанию.
std::vector<double> gnomeSort(std::vector<double> arr) {
    int i = 0;
    int n = static_cast<int>(arr.size());
    while (i < n) {
        if (i == 0 || arr[i - 1] <= arr[i]) {
            ++i;
        } else {
            std::swap(arr[i - 1], arr[i]);
            --i;
        }
    }
    return arr;
}
