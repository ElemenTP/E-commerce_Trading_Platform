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

static const vector<string> item_type_des = {"食品", "衣物", "书籍"};

class Merchandise
{
protected:
    string title;
    string description;
    double pricing;
    float discount;
    unsigned long long stock;

public:
    virtual item_type getItemType() const = 0;
    virtual void optItemDes() const = 0;
    Merchandise() {}
    Merchandise(string ipttitle, string iptdes, double iptpricing, float iptdiscount, unsigned long long iptstock) : title(ipttitle), description(iptdes), pricing(iptpricing), discount(iptdiscount), stock(iptstock) {}
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    double getPricing() const { return pricing; }
    float getDiscount() const { return discount; }
    bool isDicount() const
    {
        if (discount < 1)
            return true;
        else
            return false;
    }
    double getToPay() const { return pricing * discount; }
    unsigned long long getStock() const { return stock; }
};

class Food : public Merchandise
{
public:
    item_type getItemType() const { return food; }
    Food() {}
    Food(string ipttitle, string iptdes, double iptpricing, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptpricing, iptdiscount, iptstock) {}
    void optItemDes() const
    {
        cout << "种类" << setw(50) << "食品" << endl;
        cout << "名称" << setw(50) << title << endl;
        cout << "详情" << setw(50) << description << endl;
        cout << "售价" << setw(50) << pricing << endl;
        cout << "折扣" << setw(50) << discount << endl;
        cout << "库存" << setw(50) << stock << endl;
    }
    friend void to_json(json &j, const Food &p);
    friend void from_json(const json &j, Food &p);
};

void to_json(json &j, const Food &p)
{
    j = {{"type", food}, {"title", p.title}, {"description", p.description}, {"pricing", p.pricing}, {"discount", p.discount}, {"stock", p.stock}};
}
void from_json(const json &j, Food &p)
{
    j.at("title").get_to(p.title);
    j.at("description").get_to(p.description);
    j.at("pricing").get_to(p.pricing);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

class Clothing : public Merchandise
{
public:
    item_type getItemType() const { return clothing; }
    Clothing() {}
    Clothing(string ipttitle, string iptdes, double iptpricing, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptpricing, iptdiscount, iptstock) {}
    void optItemDes() const
    {
        cout << "种类" << setw(50) << "衣物" << endl;
        cout << "名称" << setw(50) << title << endl;
        cout << "详情" << setw(50) << description << endl;
        cout << "售价" << setw(50) << pricing << endl;
        cout << "折扣" << setw(50) << discount << endl;
        cout << "库存" << setw(50) << stock << endl;
    }
    friend void to_json(json &j, const Clothing &p);
    friend void from_json(const json &j, Clothing &p);
};

void to_json(json &j, const Clothing &p)
{
    j = {{"type", food}, {"title", p.title}, {"description", p.description}, {"pricing", p.pricing}, {"discount", p.discount}, {"stock", p.stock}};
}
void from_json(const json &j, Clothing &p)
{
    j.at("title").get_to(p.title);
    j.at("description").get_to(p.description);
    j.at("pricing").get_to(p.pricing);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

class Book : public Merchandise
{
protected:
    static const item_type type = book;

public:
    item_type getItemType() const { return type; }
    Book() {}
    Book(string ipttitle, string iptdes, double iptpricing, float iptdiscount, unsigned long long iptstock) : Merchandise(ipttitle, iptdes, iptpricing, iptdiscount, iptstock) {}
    void optItemDes() const
    {
        cout << "种类" << setw(50) << "书籍" << endl;
        cout << "名称" << setw(50) << title << endl;
        cout << "详情" << setw(50) << description << endl;
        cout << "售价" << setw(50) << pricing << endl;
        cout << "折扣" << setw(50) << discount << endl;
        cout << "库存" << setw(50) << stock << endl;
    }
    friend void to_json(json &j, const Book &p);
    friend void from_json(const json &j, Book &p);
};

void to_json(json &j, const Book &p)
{
    j = {{"type", food}, {"title", p.title}, {"description", p.description}, {"pricing", p.pricing}, {"discount", p.discount}, {"stock", p.stock}};
}
void from_json(const json &j, Book &p)
{
    j.at("title").get_to(p.title);
    j.at("description").get_to(p.description);
    j.at("pricing").get_to(p.pricing);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

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
    bool changeName(string iptpasswd, string newname)
    {
        if (iptpasswd == passwd)
        {
            name = newname;
            return true;
        }
        else
            return false;
    }
    string getName() const { return name; }
    bool changepasswd(string oldpasswd, string newpasswd)
    {
        if (oldpasswd == passwd)
        {
            passwd = newpasswd;
            return true;
        }
        else
            return false;
    }
    bool checkpasswd(string iptpasswd) const
    {
        if (iptpasswd == passwd)
            return true;
        else
            return false;
    }
    double getBalance(string iptpasswd) const
    {
        if (iptpasswd == passwd)
        {
            return balance;
        }
        else
            return -1;
    }
    bool changeBalance(string iptpasswd, double amount)
    {
        if (iptpasswd == passwd)
        {
            if ((balance + amount) >= 0 && (balance + amount) < __DBL_MAX__)
            {
                balance += amount;
                return true;
            }
        }
        else
            return false;
    }
};

class Client : public Account
{
public:
    usr_type getUserType() const { return client; }
    Client() {}
    Client(string iptname, string iptpasswd) : Account(iptname, iptpasswd)
    {
        cout << "成功创建新消费者账号，用户名：" << name << endl;
    }
    friend void to_json(json &j, const Client &p);
    friend void from_json(const json &j, Client &p);
};

void to_json(json &j, const Client &p)
{
    j = {{"type", client}, {"name", p.name}, {"passwd", p.passwd}, {"balance", p.balance}};
}
void from_json(const json &j, Client &p)
{
    j.at("name").get_to(p.name);
    j.at("passwd").get_to(p.passwd);
    j.at("balance").get_to(p.balance);
}

class Business : public Account
{
protected:
    vector<json> myShelves;

public:
    usr_type getUserType() const { return business; }
    Business() {}
    Business(string iptname, string iptpasswd) : Account(iptname, iptpasswd)
    {
        cout << "成功创建新商家账号，用户名：" << name << endl;
    }
    const vector<json> *getMyShelves() const { return &myShelves; }
    vector<json> *changeMyShelves(string iptpasswd)
    {
        if (iptpasswd == passwd)
            return (&myShelves);
        else
            return NULL;
    }
    friend void to_json(json &j, const Business &p);
    friend void from_json(const json &j, Business &p);
};

void to_json(json &j, const Business &p)
{
    j = {{"type", client}, {"name", p.name}, {"passwd", p.passwd}, {"balance", p.balance}, {"myShelves", p.myShelves}};
}
void from_json(const json &j, Business &p)
{
    j.at("name").get_to(p.name);
    j.at("passwd").get_to(p.passwd);
    j.at("balance").get_to(p.balance);
    j.at("myShelves").get_to(p.myShelves);
}
