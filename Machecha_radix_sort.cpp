#include "Machecha_radix_sort.h"
#include <algorithm>
#include <cmath>
#include <format>
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
            a.insert(a.end(), buckets[i].begin(), buckets[i].end());

        if (exp > maximum / 10)
            break;

        exp *= 10;
    }
}

std::vector<double> radixSort(std::vector<double> arr)
{
    int decimalPlaces = 0;

    for (double value : arr)
    {
        value = std::abs(value);
        int whole = value;
        int fullLength = std::format("{}", value).size();
        int intLength = std::to_string(whole).size();
        int after = fullLength - intLength - 1;
        decimalPlaces = std::max(decimalPlaces, after);
    }

    int scale = std::pow(10, decimalPlaces);

    std::vector<int> positive;
    std::vector<int> negative;

    for (double value : arr)
    {
        int number = std::llround(value * scale);

        if (number < 0)
            negative.push_back(-number);
        else
            positive.push_back(number);
    }

    sortDigits(positive);
    sortDigits(negative);
    arr.clear();

    for (int i = negative.size(); i > 0; --i)
        arr.push_back(-static_cast<double>(negative[i - 1]) / scale);

    for (int number : positive)
        arr.push_back(static_cast<double>(number) / scale);

    return arr;
}
