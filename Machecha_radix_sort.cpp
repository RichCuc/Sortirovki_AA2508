#include "Machecha_radix_sort.h"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <string>

static void sortDigits(std::vector<int>& a)
{
    if (a.empty())
        return;
    int maximum = *std::max_element(a.begin(), a.end());
    int exp = 1;
    while (maximum / exp > 0)
    {
        std::vector<int> buckets[10];
        for (int number : a)
        {
            int digit = (number / exp) % 10;
            buckets[digit].push_back(number);
        }
        a.clear();
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < static_cast<int>(buckets[i].size()); ++j)
                a.push_back(buckets[i][j]);
        if (exp > maximum / 10)
            break;
        exp *= 10;
    }
}



std::vector<int> radixSort(std::vector<int> arr)
{
    std::vector<int> positive;
    std::vector<int> negative;

    for (int value : arr)
    {
        if (value < 0)
            negative.push_back(-static_cast<int>(value));
        else
            positive.push_back(value);
    }

    sortDigits(positive);
    sortDigits(negative);
    arr.clear();
    for (int i = static_cast<int>(negative.size()); i > 0; --i)
        arr.push_back(static_cast<int>(-negative[i - 1]));
    for (int number : positive)
        arr.push_back(static_cast<int>(number));
    return arr;
}

std::vector<double> radixSort(std::vector<double> arr)
{
    int decimalPlaces = 0;

    for (double value : arr)
    {
        std::string text = std::to_string(value);
        while (text.back() == '0')
            text.pop_back();
        int length = static_cast<int>(text.size());
        int point = 0;
        while (point < length && text[point] != '.')
            ++point;
        if (point < length)
            decimalPlaces = std::max(decimalPlaces, length - point - 1);
    }

    int scale = std::pow(10, decimalPlaces);

    std::vector<int> positive;
    std::vector<int> negative;

    for (double value : arr)
    {
        int number = static_cast<int>(std::llround(value * scale));
        if (number < 0)
            negative.push_back(-number);
        else
            positive.push_back(number);
    }

    sortDigits(positive);
    sortDigits(negative);

    arr.clear();

    for (int i = static_cast<int>(negative.size()); i > 0; --i)
        arr.push_back(-static_cast<double>(negative[i - 1]) / static_cast<double>(scale));
    for (int number : positive)
        arr.push_back(static_cast<double>(number) / static_cast<double>(scale));

    return arr;
}
