#include "GnomeSort_Zykov.h"

#include <cmath>
#include <utility>

// Гномья сортировка целых чисел по возрастанию.
std::vector<int> gnomeSort(std::vector<int> arr) {
    std::size_t i = 0;
    while (i < arr.size()) {
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
// NaN, если встречается, помещается после всех остальных значений.
std::vector<double> gnomeSort(std::vector<double> arr) {
    std::size_t i = 0;
    while (i < arr.size()) {
        if (i == 0 || std::isnan(arr[i]) ||
            (!std::isnan(arr[i - 1]) && arr[i - 1] <= arr[i])) {
            ++i;
        } else {
            std::swap(arr[i - 1], arr[i]);
            --i;
        }
    }
    return arr;
}
