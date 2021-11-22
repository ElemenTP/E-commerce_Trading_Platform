#include "global.hpp"
#include <conio.h>

void Page::setfilter(Filter* filter)
{
	do
	{
		system("cls");
		cout << "*************************Set Filter************************" << endl;
		cout << "Filter by title" //显示筛选器状态
			<< "\t"
			<< boolalpha << filter->title << endl;
		cout << "Filter by type"
			<< "\t"
			<< boolalpha << filter->type << endl;
		cout << "Filter by price"
			<< "\t"
			<< boolalpha << filter->price << endl;
		cout << "Filter by discount"
			<< "\t"
			<< boolalpha << filter->discount << endl;
		cout << "Filter by stock"
			<< "\t"
			<< boolalpha << filter->stock << endl;
		cout << "Press A"
			<< "\t"
			<< "Change title filter" << endl;
		cout << "Press S"
			<< "\t"
			<< "Change type filter" << endl;
		cout << "Press D"
			<< "\t"
			<< "Change price filter" << endl;
		cout << "Press F"
			<< "\t"
			<< "Change discount filter" << endl;
		cout << "Press G"
			<< "\t"
			<< "Change stock filter" << endl;
		cout << "Press H"
			<< "\t"
			<< "Reset all filter" << endl;
		cout << "Press Q"
			<< "\t"
			<< "Go Back" << endl;
		switch (_getch())
		{
		case 'a':
		{
			if (filter->title)
				filter->title = false;
			else
			{
				cout << "Input"
					<< "\t"
					<< "Value of title filter" << endl;
				cin >> filter->title_filter;
				filter->title = true;
			}
			break;
		}
		case 's':
		{
			if (filter->type)
				filter->type = false;
			else
			{
				int type = -1;
				do
				{
					system("cls");
					cout << "*****************Set Value of type filter******************" << endl;
					cout << "Press A"
						<< "\t"
						<< "Food" << endl;
					cout << "Press S"
						<< "\t"
						<< "Clothing" << endl;
					cout << "Press D"
						<< "\t"
						<< "Book" << endl;
					cout << "Press Q"
						<< "\t"
						<< "Go Back" << endl;
					switch (_getch())
					{
					case 'a':
						type = food;
						break;
					case 's':
						type = clothing;
						break;
					case 'd':
						type = book;
						break;
					case 'q':
						type = 114514;
					default:
						system("cls");
						cout << "ERROR: Invalid input." << endl;
						system("pause");
					}
				} while (type < 0);
				if (type != 114514)
				{
					filter->type_filter = (item_type)type;
					filter->type = true;
				}
			}
			break;
		}
		case 'd':
		{
			if (filter->price)
				filter->price = false;
			else
			{
				double newprice;
				cout << "Input"
					<< "\t"
					<< "Value of price filter, low" << endl;
			ipt5:
				cin >> newprice;
				if (newprice < 0)
				{
					cout << "Invalid price. Input again." << endl;
					goto ipt5;
				}
				filter->price_low_filter = newprice;
				cout << "Input"
					<< "\t"
					<< "Value of price filter, high" << endl;
			ipt6:
				cin >> newprice;
				if (newprice < 0 || newprice < filter->price_low_filter)
				{
					cout << "Invalid price. Input again." << endl;
					goto ipt6;
				}
				filter->price_high_filter = newprice;
				filter->price = true;
			}
			break;
		}
		case 'f':
			filter->discount = !(filter->discount);
			break;
		case 'g':
			filter->stock = !(filter->stock);
			break;
		case 'h':
			*filter = Filter();
			break;
		case 'q':
			return;
		default:
			system("cls");
			cout << "ERROR: Invalid input." << endl;
			system("pause");
		}
	} while (true);
}

void Page::setdiscountinbatch(vector<json>* myshelf)
{
	int type = -1;
	do
	{
		system("cls");
		cout << "*******************Set discount in batch*******************" << endl;
		cout << "Press A"
			<< "\t"
			<< "Food" << endl;
		cout << "Press S"
			<< "\t"
			<< "Clothing" << endl;
		cout << "Press D"
			<< "\t"
			<< "Book" << endl;
		cout << "Press Q"
			<< "\t"
			<< "Go Back" << endl;
		switch (_getch())
		{
		case 'a':
			type = food;
			break;
		case 's':
			type = clothing;
			break;
		case 'd':
			type = book;
			break;
		case 'q':
			return;
		default:
			system("cls");
			cout << "ERROR: Invalid input." << endl;
			system("pause");
		}
	} while (type < 0);
	cout << "Input"
		<< "\t"
		<< "new discount" << endl;
	float newdiscount;
ipt4:
	cin >> newdiscount;
	if (newdiscount < 0 || newdiscount > 1)
	{
		cout << "Invalid price. Input again." << endl;
		goto ipt4;
	}
	vector<json>::iterator it;
	for (it = myshelf->begin(); it < myshelf->end(); ++it)
	{
		if ((*it)["type"].get<int>() == type)
			(*it)["discount"] = newdiscount;
	}
}

void Page::managemygood(vector<json>::iterator it)
{
	do
	{
		system("cls");
		cout << "***************************Manage**************************" << endl;
		cout << "Press A"
			<< "\t"
			<< "Change title" << endl;
		cout << "Press S"
			<< "\t"
			<< "Change detail" << endl;
		cout << "Press D"
			<< "\t"
			<< "Change price" << endl;
		cout << "Press F"
			<< "\t"
			<< "Change discount" << endl;
		cout << "Press G"
			<< "\t"
			<< "Change stock" << endl;
		cout << "Press Q"
			<< "\t"
			<< "Go Back" << endl;
		switch (_getch())
		{
		case 'a':
		{
			cout << "Input"
				<< "\t"
				<< "new title" << endl;
			string newtitle;
			std::getline(std::cin, newtitle, '\n');
			(*it)["title"] = newtitle;
			break;
		}
		case 's':
		{
			cout << "Input"
				<< "\t"
				<< "new detail" << endl;
			string newdetail;
			std::getline(std::cin, newdetail, '\n');
			(*it)["detail"] = newdetail;
			break;
		}
		case 'd':
		{
			cout << "Input"
				<< "\t"
				<< "new price" << endl;
			double newprice;
		ipt1:
			cin >> newprice;
			if (newprice < 0)
			{
				cout << "Invalid price. Input again." << endl;
				goto ipt1;
			}
			(*it)["price"] = newprice;
			break;
		}
		case 'f':
		{
			cout << "Input"
				<< "\t"
				<< "new discount" << endl;
			float newdiscount;
		ipt2:
			cin >> newdiscount;
			if (newdiscount < 0 || newdiscount > 1)
			{
				cout << "Invalid price. Input again." << endl;
				goto ipt2;
			}
			(*it)["discount"] = newdiscount;
			break;
		}
		case 'g':
		{
			cout << "Input"
				<< "\t"
				<< "new stock" << endl;
			unsigned long long newstock;
			cin >> newstock;
			(*it)["stock"] = newstock;
			break;
		}
		case 'q':
			return;
		default:
			system("cls");
			cout << "ERROR: Invalid input." << endl;
			system("pause");
		}
	} while (true);
}

void Page::browseall()
{
	json::iterator it_usr = data.begin(); //卖家用户迭代器
	json::iterator it;                    //商品迭代器
	Filter filter;                        //筛选器对象
	while (true)                          //找到第一个货架非空的卖家
	{
		if ((*it_usr)["type"].get<int>() == business)
		{
			if (!(*it_usr)["myShelves"].empty())
			{
				it = (*it_usr)["myShelves"].begin();
				break;
			}
		}
		++it_usr;
		if (it_usr == data.end()) //不存在这样的卖家，即没有商品可以展示
		{
			system("cls");
			cout << "**************************Shelves**************************" << endl;
			cout << "Empty" << endl;
			cout << "Press any key to go back." << endl;
			_getch();
			return;
		}
	}
	while (true)
	{
		system("cls");
		cout << "**************************Shelves**************************" << endl;
		switch ((*it)["type"].get<int>()) //展示当前商品的信息
		{
		case food:
		{
			Food mer_tmp = *it;
			mer_tmp.optItemDes();
			break;
		}
		case clothing:
		{
			Clothing mer_tmp = *it;
			mer_tmp.optItemDes();
			break;
		}
		case book:
		{
			Book mer_tmp = *it;
			mer_tmp.optItemDes();
			break;
		}
		}
		cout << "Press A"
			<< "\t"
			<< "Previous" << endl;
		if (cur_usr)
			if (cur_usr->getUserType() == client) //如果用户是客户则可以购买商品
				cout << "Press S"
				<< "\t"
				<< "Buy" << endl;
		cout << "Press D"
			<< "\t"
			<< "Next" << endl;
		cout << "Press H"
			<< "\t"
			<< "Set filter" << endl;
		cout << "Press Q"
			<< "\t"
			<< "Go Back" << endl;
		switch (_getch())
		{
		case 'a':
		{
			json::iterator tmp_usr = it_usr;
			json::iterator tmp = it;
			while (true) //向前寻找符合筛选条件的商品，没有则向前寻找一个货架非空的卖家，在该卖家的商品中继续寻找，仍然找不到则重复到找到为止。如果找完了所有也未找到，提示找不到并回到之前的状态
			{
				--it;
				if (it >= (*it_usr)["myShelves"].begin())
				{
					if (filter.sift(*it))
						break;
				}
				else
				{
					while (true)
					{
						--it_usr;
						if (it_usr < data.begin())
							break;
						if ((*it_usr)["type"].get<int>() == business)
						{
							if (!(*it_usr)["myShelves"].empty())
							{
								it = (*it_usr)["myShelves"].end();
								break;
							}
						}
					}
					if (it_usr < data.begin())
					{
						system("cls");
						cout << "No more." << endl;
						system("pause");
						it_usr = tmp_usr;
						it = tmp;
						break;
					}
				}
			}
			break;
		}

		case 's':
			if (cur_usr)
			{
				if (cur_usr->getUserType() == client)
				{
					buygoods(it_usr, it);
					storedata();
				}
				else
				{
					system("cls");
					cout << "ERROR: Invalid input." << endl;
					system("pause");
				}
			}
			else
			{
				system("cls");
				cout << "ERROR: Invalid input." << endl;
				system("pause");
			}
			break;
		case 'd':
		{
			json::iterator tmp_usr = it_usr;
			json::iterator tmp = it;
			while (true) //向后寻找符合筛选条件的商品，没有则向后寻找一个货架非空的卖家，在该卖家的商品中继续寻找，仍然找不到则重复到找到为止。如果找完了所有也未找到，提示找不到并回到之前的状态
			{
				++it;
				if (it < (*it_usr)["myShelves"].end())
				{
					if (filter.sift(*it))
						break;
				}
				else
				{
					while (true)
					{
						++it_usr;
						if (it_usr >= data.end())
							break;
						if ((*it_usr)["type"].get<int>() == business)
						{
							if (!(*it_usr)["myShelves"].empty())
							{
								it = (*it_usr)["myShelves"].begin() - 1;
								break;
							}
						}
					}
					if (it_usr >= data.end())
					{
						system("cls");
						cout << "No more." << endl;
						system("pause");
						it_usr = tmp_usr;
						it = tmp;
						break;
					}
				}
			}
			break;
		}

		case 'h':
		{
			setfilter(&filter);
			json::iterator tmp_usr = it_usr;
			json::iterator tmp = it;
			while (true) //设置筛选器后先向后寻找符合筛选条件的商品，没有则向后寻找一个货架非空的卖家，在该卖家的商品中继续寻找，仍然找不到则重复到找到为止。如果找完了所有也未找到，向前寻找符合筛选条件的商品，没有则向前寻找一个货架非空的卖家，在该卖家的商品中继续寻找，仍然找不到则重复到找到为止。如果找完了所有也未找到，提示找不到并回到之前的状态，并重置筛选器
			{
				++it;
				if (it < (*it_usr)["myShelves"].end())
				{
					if (filter.sift(*it))
						break;
				}
				else
				{
					while (true)
					{
						++it_usr;
						if (it_usr >= data.end())
							break;
						if ((*it_usr)["type"].get<int>() == business)
						{
							if (!(*it_usr)["myShelves"].empty())
							{
								it = (*it_usr)["myShelves"].begin() - 1;
								break;
							}
						}
					}
					if (it_usr >= data.end())
					{
						it_usr = tmp_usr;
						it = tmp;
						while (true)
						{
							--it;
							if (it >= (*it_usr)["myShelves"].begin())
							{
								if (filter.sift(*it))
									break;
							}
							else
							{
								while (true)
								{
									--it_usr;
									if (it_usr < data.begin())
										break;
									if ((*it_usr)["type"].get<int>() == business)
									{
										if (!(*it_usr)["myShelves"].empty())
										{
											it = (*it_usr)["myShelves"].end();
											break;
										}
									}
								}
								if (it_usr < data.begin())
								{
									system("cls");
									cout << "There is nothing fits the filter." << endl;
									system("pause");
									filter = Filter();
									it_usr = tmp_usr;
									it = tmp;
									break;
								}
							}
						}
						break;
					}
				}
			}
			break;
		}
		case 'q':
			return;
		default:
			system("cls");
			cout << "ERROR: Invalid input." << endl;
			system("pause");
		}
	}
}

void Page::buygoods(json::iterator it_usr, json::iterator it)
{
	unsigned long long amount = 1;
	double total = (*it)["price"].get<double>() * (*it)["discount"].get<float>() * amount;
	do
	{
		system("cls");
		cout << "****************************Buy****************************" << endl;
		cout << "Stock"
			<< "\t"
			<< (*it)["stock"].get<unsigned long long>() << " Pcs" << endl;
		cout << "You buy"
			<< "\t"
			<< amount << " Pcs" << endl;
		cout << "You need to pay"
			<< "\t"
			<< total << endl;
		cout << "Press A"
			<< "\t"
			<< "Change the quantity to purchase" << endl;
		if (amount <= (*it)["stock"].get<unsigned long long>() && total <= cur_usr->getBalance()) //库存足够，余额足够才可购买
			cout << "Press D"
			<< "\t"
			<< "Purchase" << endl;
		cout << "Press Q"
			<< "\t"
			<< "Go Back" << endl;
		switch (_getch())
		{
		case 'a':
		{
			cout << "Input"
				<< "\t"
				<< "New quantity" << endl;
			cin >> amount;
			total = (*it)["price"].get<double>() * (*it)["discount"].get<float>() * amount;
			break;
		}
		case 'd':
		{
			if (amount > (*it)["stock"].get<unsigned long long>() || total > cur_usr->getBalance())
			{
				system("cls");
				cout << "ERROR: Invalid input." << endl;
				system("pause");
			}
			else
			{
				(*it)["stock"] = (*it)["stock"].get<unsigned long long>() - amount;
				cur_usr->changeBalance(-total);
				(*it_usr)["balance"] = (*it_usr)["balance"].get<double>() + total;
				system("cls");
				cout << "Purchase was successful." << endl;
				system("pause");
				return;
			}
			break;
		}
		case 'q':
			return;
		default:
			system("cls");
			cout << "ERROR: Invalid input." << endl;
			system("pause");
		}
	} while (true);
}
