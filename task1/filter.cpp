#include "global.hpp"
//筛选函数
bool Filter::sift(json item) const
{
    if (title)//按标题筛选
    {
        if (item["title"].get<string>().find(title_filter) == item["title"].get<string>().npos)
            return false;
    }
    if (type)//按类型筛选
    {
        if (item["type"].get<int>() != type_filter)
            return false;
    }
    if (price)//按价格区间筛选
    {
        if (item["price"].get<double>() < price_low_filter || item["price"].get<double>() > price_high_filter)
            return false;
    }
    if (discount)//按是否促销筛选
    {
        if (item["discount"].get<float>() == 1)
            return false;
    }
    if (stock)//按是否有库存筛选
    {
        if (item["stock"].get<unsigned long long>() == 0)
            return false;
    }
    return true;
}