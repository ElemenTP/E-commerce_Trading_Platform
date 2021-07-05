#include "global.hpp"
//ɸѡ����
bool Filter::sift(json item) const
{
    if (title)//������ɸѡ
    {
        if (item["title"].get<string>().find(title_filter) == item["title"].get<string>().npos)
            return false;
    }
    if (type)//������ɸѡ
    {
        if (item["type"].get<int>() != type_filter)
            return false;
    }
    if (price)//���۸�����ɸѡ
    {
        if (item["price"].get<double>() < price_low_filter || item["price"].get<double>() > price_high_filter)
            return false;
    }
    if (discount)//���Ƿ����ɸѡ
    {
        if (item["discount"].get<float>() == 1)
            return false;
    }
    if (stock)//���Ƿ��п��ɸѡ
    {
        if (item["stock"].get<unsigned long long>() == 0)
            return false;
    }
    return true;
}