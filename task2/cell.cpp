#include "global.hpp"
using namespace std;
using json = nlohmann::json;

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

double Cell::gettopay()
{
    return (*it)["price"].get<double>() * (*it)["discount"].get<float>() * amount;
}

void Cell::toorder() {}

void Cell::outorder() {}

void Cell::purchased() {}
