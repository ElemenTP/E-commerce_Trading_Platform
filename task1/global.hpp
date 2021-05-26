#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;

typedef enum
{
     client,
     business,
} usr_type;

typedef enum
{
     food,
     clothing,
     book,
} item_type;

class Merchandise
{
protected:
     string title;
     string detail;
     double price;
     float discount;
     unsigned long long stock;

public:
     virtual item_type getItemType() const = 0;
     virtual void optItemDes() const = 0;
     virtual double getPrice() const = 0;
     Merchandise() {}
     Merchandise(string ipttitle, string iptdes, double iptprice, float iptdiscount, unsigned long long iptstock) : title(ipttitle), detail(iptdes), price(iptprice), discount(iptdiscount), stock(iptstock) {}
};

class Food : public Merchandise
{
public:
     item_type getItemType() const { return food; }
     Food() {}
     Food(string ipttitle, string iptdes, double iptprice, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptprice, iptdiscount, iptstock) {}
     double getPrice() const { return price; }
     void optItemDes() const
     {
          cout << "Type"
               << "\t"
               << "Food" << endl;
          cout << "Name"
               << "\t" << title << endl;
          cout << "Detail"
               << "\t" << detail << endl;
          cout << "Price"
               << "\t" << price << endl;
          cout << "Discount"
               << "\t" << discount << endl;
          cout << "Stock"
               << "\t" << stock << endl;
     }
     friend void to_json(json &j, const Food &p);
     friend void from_json(const json &j, Food &p);
};

class Clothing : public Merchandise
{
public:
     item_type getItemType() const { return clothing; }
     Clothing() {}
     Clothing(string ipttitle, string iptdes, double iptprice, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptprice, iptdiscount, iptstock) {}
     double getPrice() const { return price; }
     void optItemDes() const
     {
          cout << "Type"
               << "\t"
               << "Clothing" << endl;
          cout << "Name"
               << "\t" << title << endl;
          cout << "Detail"
               << "\t" << detail << endl;
          cout << "Price"
               << "\t" << price << endl;
          cout << "Discount"
               << "\t" << discount << endl;
          cout << "Stock"
               << "\t" << stock << endl;
     }
     friend void to_json(json &j, const Clothing &p);
     friend void from_json(const json &j, Clothing &p);
};

class Book : public Merchandise
{
public:
     item_type getItemType() const { return book; }
     Book() {}
     Book(string ipttitle, string iptdes, double iptprice, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptprice, iptdiscount, iptstock) {}
     double getPrice() const { return price; }
     void optItemDes() const
     {
          cout << "Type"
               << "\t"
               << "Book" << endl;
          cout << "Name"
               << "\t" << title << endl;
          cout << "Detail"
               << "\t" << detail << endl;
          cout << "Price"
               << "\t" << price << endl;
          cout << "Discount"
               << "\t" << discount << endl;
          cout << "Stock"
               << "\t" << stock << endl;
     }
     friend void to_json(json &j, const Book &p);
     friend void from_json(const json &j, Book &p);
};

class Account
{
protected:
     string name;
     string passwd;
     double balance;

public:
     virtual usr_type getUserType() const = 0;
     Account() {}
     Account(string iptname, string iptpasswd) : name(iptname), passwd(iptpasswd), balance(0) {}
     virtual void optAccoutDet() const = 0;
     double getBalance() const { return balance; }
     void changeName(string newname) { name = newname; }
     void changepasswd(string newpasswd) { passwd = newpasswd; }
     bool checkpasswd(string iptpasswd) const
     {
          if (iptpasswd == passwd)
               return true;
          else
               return false;
     }
     void changeBalance(double amount) { balance += amount; }
};

class Client : public Account
{
public:
     usr_type getUserType() const { return client; }
     Client() {}
     Client(string iptname, string iptpasswd) : Account(iptname, iptpasswd) {}
     void optAccoutDet() const
     {
          cout << "Type"
               << "\t"
               << "Buyer" << endl;
          cout << "Name"
               << "\t" << name << endl;
          cout << "Balance"
               << "\t" << balance << endl;
     }
     friend void to_json(json &j, const Client &p);
     friend void from_json(const json &j, Client &p);
};

class Business : public Account
{
protected:
     vector<json> myShelves;

public:
     usr_type getUserType() const { return business; }
     Business() {}
     Business(string iptname, string iptpasswd) : Account(iptname, iptpasswd) {}
     void optAccoutDet() const
     {
          cout << "Type"
               << "\t"
               << "Seller" << endl;
          cout << "Name"
               << "\t" << name << endl;
          cout << "Balance"
               << "\t" << balance << endl;
          cout << "Number of my products"
               << "\t" << myShelves.size() << endl;
     }
     //const vector<json> *getMyShelves() const { return &myShelves; }
     vector<json> *changeMyShelves() { return (&myShelves); }
     friend void to_json(json &j, const Business &p);
     friend void from_json(const json &j, Business &p);
};

class Filter
{
public:
     bool title = false;
     string title_filter;
     bool type = false;
     item_type type_filter;
     bool price = false;
     double price_low_filter = 0;
     double price_high_filter = __DBL_MAX__;
     bool discount = false;
     bool stock = false;
     Filter(){};
     bool sift(json item) const;
};

class Page
{
private:
     json data;
     Account *cur_usr = NULL;
     json::iterator usr_json;
     ifstream iptdata;
     ofstream optdata;
     void signup();
     void signupipt(usr_type type);
     void signinipt();
     void browseall();
     void accouthome();
     void changename();
     void changepasswd();
     void recharge();
     void withdrawals();
     void managemyshelf();
     void managemygood(vector<json>::iterator it);
     json newgood();
     void storedata();
     void setfilter(Filter *filter);
     void setdiscountinbatch(vector<json> *myshelf);
     void buygoods(json::iterator it_usr, vector<json>::iterator it);

public:
     Page();
     void runapp();
};
