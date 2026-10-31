#include "radix_sort.h"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <string>

std::vector<double> radixSort(std::vector<double> arr)
{
    int decimalPlaces = 0;

    for (double value : arr)
    {
        char buffer[512];
        auto result = std::to_chars(buffer, buffer + sizeof(buffer), value,
                                    std::chars_format::fixed);
        std::string text(buffer, result.ptr);
        std::size_t point = text.find('.');
        if (point != std::string::npos)
            decimalPlaces = std::max(decimalPlaces,
                static_cast<int>(text.size() - point - 1));
    }

    long long scale = 1;
    for (int i = 0; i < decimalPlaces; ++i)
        scale *= 10;

    std::vector<long long> positive;
    std::vector<long long> negative;

    for (double value : arr)
    {
        double scaled = std::abs(value) * static_cast<double>(scale);
        long long number = std::llround(scaled);
        if (value < 0)
            negative.push_back(number);
        else
            positive.push_back(number);
    }

    auto sortDigits = [](std::vector<long long>& numbers)
    {
        long long maximum = 0;
        for (long long number : numbers)
            if (number > maximum)
                maximum = number;

        for (long long place = 1; maximum / place > 0; place *= 10)
        {
            std::vector<long long> buckets[10];

            for (long long number : numbers)
            {
                int digit = static_cast<int>((number / place) % 10);
                buckets[digit].push_back(number);
            }

            numbers.clear();
            for (const auto& bucket : buckets)
                for (long long number : bucket)
                    numbers.push_back(number);
        }
    };

    sortDigits(positive);
    sortDigits(negative);

    arr.clear();

    for (std::size_t i = negative.size(); i > 0; --i)
        arr.push_back(-static_cast<double>(negative[i - 1]) / static_cast<double>(scale));

    for (long long number : positive)
        arr.push_back(static_cast<double>(number) / static_cast<double>(scale));

    return arr;
}
