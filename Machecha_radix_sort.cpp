#include "Machecha_radix_sort.h"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <string>


static void sortDigits(std::vector<long long>& a)
{
    long long maximum = 0;
    for (long long x : a)
        if (x > maximum)
            maximum = x;
    for (long long exp = 1; maximum / exp > 0; exp *= 10)
    {
        std::size_t count[10] = {};
        std::vector<long long> result(a.size());
        for (long long x : a)
            ++count[(x / exp) % 10];
        for (int i = 1; i < 10; ++i)
            count[i] += count[i - 1];.
        for (std::size_t i = a.size(); i > 0; --i)
        {
            int digit = (a[i - 1] / exp) % 10;
            result[--count[digit]] = a[i - 1];
        }
        a = result;
    }
}

std::vector<int> radixSort(std::vector<int> arr)
{
    std::vector<long long> positive;
    std::vector<long long> negative;

    for (int x : arr)
    {
        if (x < 0)
            negative.push_back(-static_cast<long long>(x));
        else
            positive.push_back(x);
    }

    sortDigits(positive);
    sortDigits(negative);

    arr.clear();

    for (std::size_t i = negative.size(); i > 0; --i)
        arr.push_back(static_cast<int>(-negative[i - 1]));

    for (long long x : positive)
        arr.push_back(static_cast<int>(x));

    return arr;
}

std::vector<double> radixSort(std::vector<double> arr)
{
    int decimalPlaces = 0;
    for (double x : arr)
    {
        char buffer[512];
        auto result = std::to_chars(
            buffer, buffer + sizeof(buffer),
            x, std::chars_format::fixed
        );

        std::string text(buffer, result.ptr);
        std::size_t point = text.find('.');

        if (point != std::string::npos)
            decimalPlaces = std::max(
                decimalPlaces,
                static_cast<int>(text.size() - point - 1)
            );
    }

    long long scale = 1;

    for (int i = 0; i < decimalPlaces; ++i)
        scale *= 10;

    std::vector<long long> positive;
    std::vector<long long> negative;

    for (double x : arr)
    {
        long long number = std::llround(std::abs(x) * scale);

        if (x < 0)
            negative.push_back(number);
        else
            positive.push_back(number);
    }

    sortDigits(positive);
    sortDigits(negative);

    arr.clear();

    for (std::size_t i = negative.size(); i > 0; --i)
        arr.push_back(-static_cast<double>(negative[i - 1]) / scale);

    for (long long x : positive)
        arr.push_back(static_cast<double>(x) / scale);

    return arr;
}