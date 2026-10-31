
#include "CombSort_Sannikov.h"

std::vector<double> CombSort(std::vector<double> arr)
{
    auto gap = arr.size();
    bool swapped = true;
    if (arr.size() < 2)
    {
        return arr;
    }
    while (gap > 1 || swapped)
    {
        gap = (gap > 1) ? gap * 10 / 13 : 1;
        swapped = false;
        for (int i = 0; i < (arr.size() - gap); i++)
        {
            if (arr[i] > arr[i + gap])
            {
                double temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
    return arr;
}

std::vector<int> CombSort(std::vector<int> arr)
{
    auto gap = arr.size();
    bool swapped = true;
    if (arr.size() < 2)
    {
        return arr;
    }
    while (gap > 1 || swapped)
    {
        gap = (gap > 1) ? gap * 10 / 13 : 1;
        swapped = false;
        for (int i = 0; i < (arr.size() - gap); i++)
        {
            if (arr[i] > arr[i + gap])
            {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
    return arr;
}