#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;
//�û�����
typedef enum
{
     client,
     business,
} usr_type;
//��Ʒ����
typedef enum
{
     food,
     clothing,
     book,
} item_type;
//��Ʒ����
class Merchandise
{
protected:
     string title;             //��Ʒ����
     string detail;            //��Ʒ����
     double price;             //��Ʒ�۸�
     float discount;           //��Ʒ�ۿ�
     unsigned long long stock; //��Ʒ���

public:
     virtual item_type getItemType() const = 0; //��ȡ��Ʒ����
     virtual void optItemDes() const = 0;       //��ȡ��Ʒ����
     virtual double getPrice() const = 0;       //��ȡ��Ʒ�۸�
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
//�û�����
class Account
{
protected:
     string name;    //�û���
     string passwd;  //�û�����
     double balance; //�û����

public:
     virtual usr_type getUserType() const = 0; //��ȡ�û�����
     Account() {}
     Account(string iptname, string iptpasswd) : name(iptname), passwd(iptpasswd), balance(0) {}
     virtual void optAccoutDet() const = 0;                      //����û�����
     double getBalance() const { return balance; }               //��ȡ�û����
     void changeName(string newname) { name = newname; }         //�����û���
     void changepasswd(string newpasswd) { passwd = newpasswd; } //��������
     bool checkpasswd(string iptpasswd) const                    //��������Ƿ���ȷ
     {
          if (iptpasswd == passwd)
               return true;
          else
               return false;
     }
     void changeBalance(double amount) { balance += amount; } //�޸����
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
     vector<json> myShelves; //����

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
     vector<json> *changeMyShelves() { return (&myShelves); } //��ȡ����
     friend void to_json(json &j, const Business &p);
     friend void from_json(const json &j, Business &p);
};
//ɸѡ����
class Filter
{
public:
     bool title = false; //������ɸѡ����
     string title_filter;
     bool type = false; //������ɸѡ����
     item_type type_filter;
     bool price = false; //���۸�ɸѡ����
     double price_low_filter = 0;
     double price_high_filter = DBL_MAX;
     bool discount = false; //���ۿ�ɸѡ����
     bool stock = false;    //�����ɸѡ����
     Filter(){};
     bool sift(json item) const; //ɸѡ����
};
//�û�������
class Page
{
private:
     json data;                                               //����
     Account *cur_usr = NULL;                                 //��ǰ�û�ָ��
     json::iterator usr_json;                                 //��ǰ�û�ö����
     ifstream iptdata;                                        //�����ļ�
     ofstream optdata;                                        //����ļ�
     void signup();                                           //ע�����
     void signupipt(usr_type type);                           //ע���������
     void signinipt();                                        //��¼����
     void browseall();                                        //���ȫ����Ʒ����
     void accouthome();                                       //�������Ľ���
     void changename();                                       //�����û�������
     void changepasswd();                                     //�����������
     void recharge();                                         //��ֵ����
     void withdrawals();                                      //������
     void managemyshelf();                                    //�̼ҹ�����ܽ���
     void managemygood(vector<json>::iterator it);            //�̼ҹ�����Ʒ����
     json newgood();                                          //�½���Ʒ����
     void storedata();                                        //�洢���ݺ���
     void setfilter(Filter *filter);                          //����ɸѡ������
     void setdiscountinbatch(vector<json> *myshelf);          //�������۽���
     void buygoods(json::iterator it_usr, json::iterator it); //�������

public:
     Page();
     void runapp(); //������
};
