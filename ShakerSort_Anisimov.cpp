#include "ShakerSort_Anisimov.h"

#include <cmath>
#include <utility>

// Шейкерная сортировка целых чисел по возрастанию.
std::vector<int> shakerSort(std::vector<int> arr) {
    if (arr.size() < 2) {
        return arr;
    }

    std::size_t left = 0;
    std::size_t right = arr.size() - 1;
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;
        for (std::size_t i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        --right;

        swapped = false;
        for (std::size_t i = right; i > left; --i) {
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++left;
    }
    return arr;
}

// Шейкерная сортировка вещественных чисел по возрастанию.
// NaN, если встречается, помещается после всех остальных значений.
std::vector<double> shakerSort(std::vector<double> arr) {
    if (arr.size() < 2) {
        return arr;
    }

    std::size_t left = 0;
    std::size_t right = arr.size() - 1;
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;
        for (std::size_t i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1] ||
                (std::isnan(arr[i]) && !std::isnan(arr[i + 1]))) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        --right;

        swapped = false;
        for (std::size_t i = right; i > left; --i) {
            if (arr[i - 1] > arr[i] ||
                (std::isnan(arr[i - 1]) && !std::isnan(arr[i]))) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++left;
    }
    return arr;
}
