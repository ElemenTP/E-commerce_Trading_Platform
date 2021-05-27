#include "global.hpp"
using namespace std;
using json = nlohmann::json;
//输出订单详情
void Cell::printdes()
{
     switch ((*it)["type"].get<int>())
     {
     case food:
          cout << "Type"
               << "\t"
               << "Food" << endl;
          break;
     case clothing:
          cout << "Type"
               << "\t"
               << "Clothing" << endl;
          break;
     case book:
          cout << "Type"
               << "\t"
               << "Book" << endl;
          break;
     }
     cout << "Title"
          << "\t" << (*it)["title"].get<string>() << endl;
     cout << "Price"
          << "\t" << (*it)["price"].get<double>() << endl;
     cout << "Discount"
          << "\t" << (*it)["discount"].get<float>() << endl;
     cout << "Amount"
          << "\t" << amount << endl;
     cout << "Need to pay"
          << "\t" << gettopay() << endl;
}
//返回订单实付
double Cell::gettopay() { return (*it)["price"].get<double>() * (*it)["discount"].get<float>() * amount; }
//返回货品库存
unsigned long long Cell::getstock() { return (*it)["stock"].get<unsigned long long>(); }
//下订单操作
void Cell::toorder()
{
     (*it)["stock"] = (*it)["stock"].get<unsigned long long>() - amount;
     if ((*it)["locked"].is_object())
          (*it)["locked"] = (*it)["locked"].get<unsigned long long>() + amount;
     else
          (*it)["locked"] = amount;
}
//取消订单操作
void Cell::outorder()
{
     (*it)["stock"] = (*it)["stock"].get<unsigned long long>() + amount;
     (*it)["locked"] = (*it)["locked"].get<unsigned long long>() - amount;
     if ((*it)["locked"].get<unsigned long long>() == 0)
          it->erase("locked");
}
//支付订单操作
void Cell::purchased()
{
     (*it)["locked"] = (*it)["locked"].get<unsigned long long>() - amount;
     if ((*it)["locked"].get<unsigned long long>() == 0)
          it->erase("locked");
     (*it_usr)["balance"] = (*it_usr)["balance"].get<double>() + gettopay();
}
