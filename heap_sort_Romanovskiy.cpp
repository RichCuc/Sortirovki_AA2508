#include "heap_sort_Romanovskiy.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

template <typename T>
void heapify(T* a, int size, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < size && a[l] > a[largest]) {
        largest = l;
    }
    if (r < size && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, size, largest);
    }
}

template <typename T>
void build_heap(T* a, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(a, size, i);
    }
}

template <typename T>
void heap_sort(T* a, int size) {
    build_heap(a, size);

    for (int i = size - 1; i > 0; i--) {
        swap(a[i], a[0]);
        heapify(a, i, 0);
    }
}

template void heap_sort<int>(int* a, int size);
template void heap_sort<double>(double* a, int size);