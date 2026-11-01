#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <utility>
#include <string>
#include "CombSort_Sannikov.h"
#include "GnomeSort_Zykov.h"
#include "Machecha_radix_sort.h"
#include "ShakerSort_Anisimov.h"
#include "heap_sort_Romanovskiy.hpp"

using namespace std;

int main()
{
    ifstream file("array.txt");
    if (!file)
    {
        cout << "Не удалось открыть array.txt.\n";
        return 1;
    }

    vector<double> original;
    double value;
    while (file >> ws && !file.eof())
    {
        if (!(file >> value) || !isfinite(value))
        {
            cout << "Ошибка в array.txt: нужны числа с точкой.\n";
            return 1;
        }
        original.push_back(value);
    }
    if (original.empty())
    {
        cout << "Файл array.txt пуст.\n";
        return 1;
    }
    int n = static_cast<int>(original.size());
    cout << "Считано чисел: " << n << "\n";

    vector<double> expected = original;
    sort(expected.begin(), expected.end());

    string names[] = {"Расчёской", "Гномья", "Поразрядная",
                      "Шейкерная", "Пирамидальная", "std::sort"};

    cout << defaultfloat << setprecision(15);
    cout << "Исходный массив: ";
    for (double value : original)
        cout << value << " ";
    cout << "\n";

    while (true)
    {
        cout << "\n1. Сортировка расчёской\n"
             << "2. Гномья сортировка\n"
             << "3. Поразрядная сортировка\n"
             << "4. Шейкерная сортировка\n"
             << "5. Пирамидальная сортировка\n"
             << "6. std::sort\n"
             << "7. Все сортировки\n"
             << "0. Выход\n"
             << "Ваш выбор: ";

        int choice;
        if (!(cin >> choice))
        {
            cout << "Нужно ввести целое число.\n";
            return 1;
        }
        if (choice == 0)
            break;
        if (choice < 1 || choice > 7)
        {
            cout << "Нет такого пункта.\n";
            continue;
        }

        vector<double> result;

        for (int number = 1; number <= 6; number++)
        {
            if (choice != 7 && choice != number)
                continue;

            vector<double> arr = original;
            auto start = chrono::steady_clock::now();

            switch (number)
            {
            case 1:
                arr = CombSort(std::move(arr));
                break;
            case 2:
                arr = gnomeSort(std::move(arr));
                break;
            case 3:
                arr = radixSort(std::move(arr));
                break;
            case 4:
                arr = shakerSort(std::move(arr));
                break;
            case 5:
                heap_sort(arr.data(), n);
                break;
            case 6:
                sort(arr.begin(), arr.end());
                break;
            }

            auto finish = chrono::steady_clock::now();
            double milliseconds = chrono::duration<double, milli>(finish - start).count();

            cout << fixed << setprecision(6);
            cout << names[number - 1] << ": " << milliseconds << " мс";
            cout << (arr == expected ? " | OK\n" : " | Ошибка сортировки\n");

            result = std::move(arr);
        }

        cout << defaultfloat << setprecision(15);
        cout << (result == expected ? "Отсортированный массив: "
                                   : "Результат с ошибкой: ");
        for (double value : result)
            cout << value << " ";
        cout << "\n";
    }
    return 0;
}
