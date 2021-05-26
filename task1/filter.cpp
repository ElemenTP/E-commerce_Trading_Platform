#include "global.hpp"
using namespace std;
using json = nlohmann::json;

bool Filter::sift(json item) const
{
    if (title)
    {
        if (item["title"].get<string>().find(title_filter) == item["title"].get<string>().npos)
            return false;
    }
    if (type)
    {
        if (item["type"].get<int>() != type_filter)
            return false;
    }
    if (price)
    {
        if (item["price"].get<double>() < price_low_filter || item["price"].get<double>() > price_high_filter)
            return false;
    }
    if (discount)
    {
        if (item["discount"].get<float>() == 1)
            return false;
    }
    if (stock)
    {
        if (item["stock"].get<unsigned long long>() == 0)
            return false;
    }
    return true;
}