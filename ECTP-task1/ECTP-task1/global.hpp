#include "..\..\3rd\json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;
//用户类型
typedef enum
{
	client,
	business,
} usr_type;
//商品类型
typedef enum
{
	food,
	clothing,
	book,
} item_type;
//商品基类
class Merchandise
{
protected:
	string title;             //商品标题
	string detail;            //商品详情
	double price;             //商品价格
	float discount;           //商品折扣
	unsigned long long stock; //商品库存

public:
	virtual item_type getItemType() const = 0; //获取商品类型
	virtual void optItemDes() const = 0;       //获取商品描述
	virtual double getPrice() const = 0;       //获取商品价格
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
	friend void to_json(json& j, const Food& p);
	friend void from_json(const json& j, Food& p);
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
	friend void to_json(json& j, const Clothing& p);
	friend void from_json(const json& j, Clothing& p);
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
	friend void to_json(json& j, const Book& p);
	friend void from_json(const json& j, Book& p);
};
//用户基类
class Account
{
protected:
	string name;    //用户名
	string passwd;  //用户密码
	double balance; //用户余额

public:
	virtual usr_type getUserType() const = 0; //获取用户类型
	Account() {}
	Account(string iptname, string iptpasswd) : name(iptname), passwd(iptpasswd), balance(0) {}
	virtual void optAccoutDet() const = 0;                      //输出用户详情
	double getBalance() const { return balance; }               //获取用户余额
	void changeName(string newname) { name = newname; }         //更改用户名
	void changepasswd(string newpasswd) { passwd = newpasswd; } //更改密码
	bool checkpasswd(string iptpasswd) const                    //检查密码是否正确
	{
		if (iptpasswd == passwd)
			return true;
		else
			return false;
	}
	void changeBalance(double amount) { balance += amount; } //修改余额
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
	friend void to_json(json& j, const Client& p);
	friend void from_json(const json& j, Client& p);
};

class Business : public Account
{
protected:
	vector<json> myShelves; //货架

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
	vector<json>* changeMyShelves() { return (&myShelves); } //获取货架
	friend void to_json(json& j, const Business& p);
	friend void from_json(const json& j, Business& p);
};
//筛选器类
class Filter
{
public:
	bool title = false; //按标题筛选开关
	string title_filter;
	bool type = false; //按类型筛选开关
	item_type type_filter;
	bool price = false; //按价格筛选开关
	double price_low_filter = 0;
	double price_high_filter = DBL_MAX;
	bool discount = false; //按折扣筛选开关
	bool stock = false;    //按库存筛选开关
	Filter() {};
	bool sift(json item) const; //筛选函数
};
//用户界面类
class Page
{
private:
	json data;                                               //数据
	Account* cur_usr = NULL;                                 //当前用户指针
	json::iterator usr_json;                                 //当前用户枚举器
	ifstream iptdata;                                        //输入文件
	ofstream optdata;                                        //输出文件
	void signup();                                           //注册界面
	void signupipt(usr_type type);                           //注册输入界面
	void signinipt();                                        //登录界面
	void browseall();                                        //浏览全部商品界面
	void accouthome();                                       //个人中心界面
	void changename();                                       //更改用户名界面
	void changepasswd();                                     //更改密码界面
	void recharge();                                         //充值界面
	void withdrawals();                                      //提款界面
	void managemyshelf();                                    //商家管理货架界面
	void managemygood(vector<json>::iterator it);            //商家管理商品界面
	json newgood();                                          //新建商品界面
	void storedata();                                        //存储数据函数
	void setfilter(Filter* filter);                          //设置筛选器界面
	void setdiscountinbatch(vector<json>* myshelf);          //批量打折界面
	void buygoods(json::iterator it_usr, json::iterator it); //购买界面

public:
	Page();
	void runapp(); //主界面
};
