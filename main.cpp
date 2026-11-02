#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <utility>

#include "CombSort_Sannikov.h"
#include "GnomeSort_Zykov.h"
#include "Machecha_radix_sort.h"
#include "ShakerSort_Anisimov.h"
#include "heap_sort_Romanovskiy.hpp"

using namespace std;

int main()
{
    // В files.txt записаны имена 18 файлов с массивами.
    ifstream list("files.txt");
    if (!list)
    {
        cout << "Не удалось открыть files.txt.\n";
        return 1;
    }

    vector<string> files;
    string filename;
    int fileWidth = 24;
    while (list >> filename)
    {
        files.push_back(filename);
        fileWidth = max(fileWidth, static_cast<int>(filename.size()) + 2);
    }
    if (files.size() != 18)
    {
        cout << "В files.txt должно быть 18 имён файлов. Сейчас: "
             << files.size() << "\n";
        return 1;
    }

    string names[] = {"Comb", "Gnome", "Radix", "Shaker", "Heap", "std::sort"};
    const int timeWidth = 13;
    int tableWidth = fileWidth + 9 + 6 * timeWidth;
    int loaded = 0;
    int errors = 0;

    cout << "Автоматический запуск: 18 файлов, 6 сортировок, всего 108 запусков.\n";
    cout << "Время в миллисекундах, один запуск на каждую пару файл/сортировка.\n";
    cout << "Comb: расчёской, Gnome: гномья, Radix: поразрядная,\n"
         << "Shaker: шейкерная, Heap: пирамидальная.\n\n";
    cout << left << setw(fileWidth) << "File" << right << setw(9) << "Count";
    for (const string& name : names)
        cout << setw(timeWidth) << name;
    cout << "\n" << string(tableWidth, '-') << "\n";
    cout << fixed << setprecision(6);

    // Внешний цикл перебирает файлы, внутренний — сортировки.
    for (const string& filename : files)
    {
        ifstream file(filename);
        vector<double> original;
        double value;
        bool valid = file.is_open();

        while (valid && file >> ws && !file.eof())
        {
            if (!(file >> value) || !isfinite(value))
                valid = false;
            else
                original.push_back(value);
        }

        cout << left << setw(fileWidth) << filename << right;
        if (!valid || original.empty())
        {
            cout << setw(9) << "-";
            for (int i = 0; i < 6; i++)
                cout << setw(timeWidth) << "FILE ERROR";
            cout << "\n";
            continue;
        }

        loaded++;
        int n = static_cast<int>(original.size());
        cout << setw(9) << n;

        // Эталон готовим вне замера.
        vector<double> expected = original;
        sort(expected.begin(), expected.end());

        for (int number = 1; number <= 6; number++)
        {
            // Все сортировки получают одинаковый исходный массив.
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
            double milliseconds =
                chrono::duration<double, milli>(finish - start).count();

            if (arr == expected)
                cout << setw(timeWidth) << milliseconds << flush;
            else
            {
                cout << setw(timeWidth) << "ERROR";
                errors++;
            }
        }
        cout << "\n";
    }

    cout << string(tableWidth, '-') << "\n";
    cout << "Прочитано файлов: " << loaded << "/18.\n";
    cout << "Выполнено сортировок: " << loaded * 6 << ".\n";
    cout << "Ошибок результатов: " << errors << ".\n";
    cout << "ERROR: результат не совпал с эталоном.\n";
    cout << "FILE ERROR: файл не найден, пуст или содержит неверные данные.\n";
    return (loaded == 18 && errors == 0) ? 0 : 1;
}
