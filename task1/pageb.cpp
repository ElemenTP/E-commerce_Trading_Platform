#include "global.hpp"
#include <conio.h>
using namespace std;
using json = nlohmann::json;

void Page::setfilter(Filter *filter)
{
    do
    {
        system("cls");
        cout << "*************************Set Filter************************" << endl;
        cout << "Filter by title"
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
        switch (getch())
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
                    switch (getch())
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
                        cout << "Press any key to continue." << endl;
                        getch();
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
            cout << "Press any key to continue." << endl;
            getch();
        }
    } while (true);
}

void Page::setdiscountinbatch(vector<json> *myshelf)
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
        switch (getch())
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
            cout << "Press any key to continue." << endl;
            getch();
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
        switch (getch())
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
            cout << "Press any key to continue." << endl;
            getch();
        }
    } while (true);
}

void Page::browseall()
{
    json::iterator it_usr = data.begin();
    vector<json> cur_shelf;
    vector<json>::iterator it;
    Filter filter;
    while (true)
    {
        if ((*it_usr)["type"].get<int>() == business)
        {
            cur_shelf = (*it_usr)["myShelves"].get<vector<json>>();
            if (!cur_shelf.empty())
            {
                it = cur_shelf.begin();
                break;
            }
        }
        ++it_usr;
        if (it_usr == data.end())
        {
            system("cls");
            cout << "**************************Shelves**************************" << endl;
            cout << "Empty" << endl;
            cout << "Press any key to go back." << endl;
            getch();
            return;
        }
    }
    while (true)
    {
        system("cls");
        cout << "**************************Shelves**************************" << endl;
        switch ((*it)["type"].get<int>())
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
            if (cur_usr->getUserType() == client)
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
        switch (getch())
        {
        case 'a':
        {
            json::iterator tmp_usr = it_usr;
            vector<json> tmp_shelf = cur_shelf;
            vector<json>::iterator tmp = it;
            while (true)
            {
                --it;
                if (it >= cur_shelf.begin())
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
                            cur_shelf = (*it_usr)["myShelves"].get<vector<json>>();
                            if (!cur_shelf.empty())
                            {
                                it = cur_shelf.end();
                                break;
                            }
                        }
                    }
                    if (it_usr < data.begin())
                    {
                        system("cls");
                        cout << "No more." << endl;
                        cout << "Press any key to continue." << endl;
                        getch();
                        it_usr = tmp_usr;
                        cur_shelf = tmp_shelf;
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
                    cout << "Press any key to continue." << endl;
                    getch();
                }
            }
            else
            {
                system("cls");
                cout << "ERROR: Invalid input." << endl;
                cout << "Press any key to continue." << endl;
                getch();
            }
            break;
        case 'd':
        {
            json::iterator tmp_usr = it_usr;
            vector<json> tmp_shelf = cur_shelf;
            vector<json>::iterator tmp = it;
            while (true)
            {
                ++it;
                if (it < cur_shelf.end())
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
                            cur_shelf = (*it_usr)["myShelves"].get<vector<json>>();
                            if (!cur_shelf.empty())
                            {
                                it = cur_shelf.begin() - 1;
                                break;
                            }
                        }
                    }
                    if (it_usr >= data.end())
                    {
                        system("cls");
                        cout << "No more." << endl;
                        cout << "Press any key to continue." << endl;
                        getch();
                        it_usr = tmp_usr;
                        cur_shelf = tmp_shelf;
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
            vector<json> tmp_shelf = cur_shelf;
            vector<json>::iterator tmp = it;
            while (true)
            {
                ++it;
                if (it < cur_shelf.end())
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
                            cur_shelf = (*it_usr)["myShelves"].get<vector<json>>();
                            if (!cur_shelf.empty())
                            {
                                it = cur_shelf.begin() - 1;
                                break;
                            }
                        }
                    }
                    if (it_usr >= data.end())
                    {
                        it_usr = tmp_usr;
                        cur_shelf = tmp_shelf;
                        it = tmp;
                        while (true)
                        {
                            --it;
                            if (it >= cur_shelf.begin())
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
                                        cur_shelf = (*it_usr)["myShelves"].get<vector<json>>();
                                        if (!cur_shelf.empty())
                                        {
                                            it = cur_shelf.end();
                                            break;
                                        }
                                    }
                                }
                                if (it_usr < data.begin())
                                {
                                    system("cls");
                                    cout << "There is nothing fits the filter." << endl;
                                    cout << "Press any key to continue." << endl;
                                    getch();
                                    filter = Filter();
                                    it_usr = tmp_usr;
                                    cur_shelf = tmp_shelf;
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
            cout << "Press any key to continue." << endl;
            getch();
        }
    }
}

void Page::buygoods(json::iterator it_usr, vector<json>::iterator it)
{
    do
    {

    } while (true);
}
