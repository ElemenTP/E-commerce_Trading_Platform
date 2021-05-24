#include "global.hpp"
#include <conio.h>
using namespace std;
using json = nlohmann::json;

Page::Page()
{
    iptdata.open("datafile.json");
    if (iptdata)
        iptdata >> data;
    iptdata.close();
}

void Page::runapp()
{
    do
    {
        system("cls");
        cout << "****************E-commerce Trading Platform****************" << endl;
        cout << "Press A"
             << "\t"
             << "Sign Up" << endl;
        if (!data.empty())
        {
            cout << "Press S"
                 << "\t"
                 << "Sign In" << endl;
            cout << "Press D"
                 << "\t"
                 << "Browse items as a tourist" << endl;
        }
        cout << "Press Q"
             << "\t"
             << "Quit" << endl;
        switch (getch())
        {
        case 'a':
            signup();
            break;
        case 's':
            if (data.empty())
            {
                system("cls");
                cout << "ERROR: Invalid Input." << endl;
                cout << "Press any key to continue." << endl;
                getch();
            }
            else
                signinipt();
            break;
        case 'd':
            if (data.empty())
            {
                system("cls");
                cout << "ERROR: Invalid Input." << endl;
                cout << "Press any key to continue." << endl;
                getch();
            }
            else
                browseall();
            break;
        case 'q':
            delete cur_usr;
            return;
        default:
            system("cls");
            cout << "ERROR: Invalid Input." << endl;
            cout << "Press any key to continue." << endl;
            getch();
        }
        if (cur_usr)
            accouthome();
    } while (true);
}

void Page::signup()
{
    do
    {
        system("cls");
        cout << "**************************Sign Up**************************" << endl;
        cout << "Press A"
             << "\t"
             << "Sign up for a new buyer account" << endl;
        cout << "Press S"
             << "\t"
             << "Sign up for a new seller account" << endl;
        cout << "Press Q"
             << "\t"
             << "Go Back" << endl;
        switch (getch())
        {
        case 'a':
            signupipt(client);
            break;
        case 's':
            signupipt(business);
            break;
        case 'q':
            return;
        default:
            system("cls");
            cout << "ERROR: Invalid Input." << endl;
            cout << "Press any key to continue." << endl;
            getch();
        }
        if (cur_usr)
            return;
    } while (true);
}

void Page::signupipt(usr_type type)
{
    string iptname, iptpasswd;
    json::iterator it;
    json j;
    do
    {
        system("cls");
        cout << "**************************Sign Up**************************" << endl;
        cout << "Input"
             << "\t"
             << "Name of the new account" << endl;
        std::getline(std::cin, iptname, '\n');
        for (it = data.begin(); it < data.end(); ++it)
        {
            if ((*it)["name"].get<string>() == iptname)
            {
                system("cls");
                cout << "ERROR: This name has been used." << endl;
                cout << "Press any key to continue." << endl;
                getch();
                break;
            }
        }
    } while (it != data.end());
    cout << "Input"
         << "\t"
         << "Password of the new account" << endl;
    std::getline(std::cin, iptname, '\n');
    if (type == client)
    {
        cur_usr = new Client(iptname, iptpasswd);
        j = *(Client *)cur_usr;
    }
    else if (type == business)
    {
        cur_usr = new Business(iptname, iptpasswd);
        j = *(Business *)cur_usr;
    }
    data.push_back(j);
    usr_json = data.end() - 1;
    optdata.open("datafile.json");
    optdata << setw(4) << data;
    optdata.close();
}

void Page::signinipt()
{
    do
    {
        system("cls");
        cout << "**************************Sign In**************************" << endl;
        string iptname, iptpasswd;
        cout << "Input"
             << "\t"
             << "Name of the account" << endl;
        std::getline(std::cin, iptname, '\n');
        ;
        cout << "Input"
             << "\t"
             << "Password of the account" << endl;
        std::getline(std::cin, iptpasswd, '\n');
        ;
        for (usr_json = data.begin(); usr_json < data.end(); ++usr_json)
        {
            if ((*usr_json)["name"].get<string>() == iptname && (*usr_json)["passwd"].get<string>() == iptpasswd)
            {
                if ((*usr_json)["type"].get<int>() == client)
                {
                    cur_usr = new Client();
                    *(Client *)cur_usr = (*usr_json);
                }
                else if ((*usr_json)["type"].get<int>() == business)
                {
                    cur_usr = new Business();
                    *(Business *)cur_usr = (*usr_json);
                }
                break;
            }
        }
        if (!cur_usr)
        {
            system("cls");
            cout << "ERROR: Invalid name or password." << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            cout << "Press another"
                 << "\t"
                 << "Continue" << endl;
            if (getch() == 'q')
                return;
        }
    } while (!cur_usr);
}

void Page::browseall() {}

void Page::accouthome()
{
    do
    {
        system("cls");
        cout << "*************************My Account************************" << endl;
        cur_usr->optAccoutDet();
        cout << "Input A"
             << "\t"
             << "Change name" << endl;
        cout << "Input S"
             << "\t"
             << "Change password" << endl;
        cout << "Input D"
             << "\t"
             << "Recharge balance" << endl;
        cout << "Input F"
             << "\t"
             << "Draw balance" << endl;
        cout << "Input G"
             << "\t"
             << "Browse all products" << endl;
        if (cur_usr->getUserType() == business)
            cout << "Input H"
                 << "\t"
                 << "Manage my shelf" << endl;
        cout << "Input Q"
             << "\t"
             << "Logout" << endl;
        switch (getch())
        {
        case 'a':
            changename();
            break;
        case 's':
            changepasswd();
            break;
        case 'd':
            recharge();
            break;
        case 'f':
            withdrawals();
            break;
        case 'g':
            browseall();
            break;
        case 'q':
            delete cur_usr;
            cur_usr = NULL;
            return;
        case 'h':
            if (cur_usr->getUserType() == business)
            {
                managemyshelf();
                break;
            }
        default:
            system("cls");
            cout << "ERROR: Invalid Input." << endl;
            cout << "Press any key to continue." << endl;
            getch();
        }
    } while (true);
}

void Page::changename()
{
    do
    {
        system("cls");
        cout << "************************Change Name************************" << endl;
        string iptpasswd, newname;
        cout << "Input"
             << "\t"
             << "Your password" << endl;
        std::getline(std::cin, iptpasswd, '\n');
        ;
        if (cur_usr->checkpasswd(iptpasswd))
        {
            cout << "Input"
                 << "\t"
                 << "New name" << endl;
            std::getline(std::cin, newname, '\n');
            int it;
            for (it = data.size() - 1; it >= 0; --it)
            {
                if (data[it]["name"].get<string>() == newname)
                {
                    system("cls");
                    cout << "ERROR: This name has been used." << endl;
                    break;
                }
            }
            if (it < 0)
            {
                cur_usr->changeName(newname);
                storedata();
                cout << "The user name was changed successfully." << endl;
                cout << "Press any key to continue." << endl;
                getch();
                return;
            }
        }
        else
        {
            system("cls");
            cout << "ERROR: Invalid password." << endl;
        }
        cout << "Press Q"
             << "\t"
             << "Go Back" << endl;
        cout << "Press another"
             << "\t"
             << "Continue" << endl;
        if (getch() == 'q')
            return;
    } while (true);
}

void Page::changepasswd()
{
    do
    {
        system("cls");
        cout << "**********************Change Password**********************" << endl;
        string iptpasswd, newpasswd;
        cout << "Input"
             << "\t"
             << "Your password" << endl;
        std::getline(std::cin, iptpasswd, '\n');
        ;
        if (cur_usr->checkpasswd(iptpasswd))
        {
            cout << "Input"
                 << "\t"
                 << "New password" << endl;
            std::getline(std::cin, newpasswd, '\n');
            cur_usr->changepasswd(newpasswd);
            storedata();
            cout << "The user password was changed successfully." << endl;
            cout << "Press any key to continue." << endl;
            getch();
            return;
        }
        else
        {
            system("cls");
            cout << "ERROR: Invalid password." << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            cout << "Press another"
                 << "\t"
                 << "Continue" << endl;
            if (getch() == 'q')
                return;
        }
    } while (true);
}

void Page::recharge()
{
    do
    {
        system("cls");
        cout << "**********************Recharge Balance*********************" << endl;
        double money;
        cout << "Input"
             << "\t"
             << "The amount of the top-up" << endl;
        cin >> money;
        if (money > 0 && (cur_usr->getBalance() + money) < __DBL_MAX__)
        {
            cur_usr->changeBalance(money);
            storedata();
            cout << "The top-up was successful." << endl;
            cout << "Press any key to continue." << endl;
            getch();
            return;
        }
        else
        {
            system("cls");
            cout << "ERROR: Invalid amount." << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            cout << "Press another"
                 << "\t"
                 << "Continue" << endl;
            if (getch() == 'q')
                return;
        }
    } while (true);
}

void Page::withdrawals()
{
    do
    {
        system("cls");
        cout << "************************Draw Balance***********************" << endl;
        double money;
        cout << "Input"
             << "\t"
             << "The amount of the withdrawal" << endl;
        cin >> money;
        if (money > 0 && (cur_usr->getBalance() - money) > 0)
        {
            cur_usr->changeBalance(-money);
            storedata();
            cout << "The withdrawal was successful." << endl;
            cout << "Press any key to continue." << endl;
            getch();
            return;
        }
        else
        {
            system("cls");
            cout << "ERROR: Invalid amount." << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            cout << "Press another"
                 << "\t"
                 << "Continue" << endl;
            if (getch() == 'q')
                return;
        }
    } while (true);
}

void Page::managemyshelf()
{
    vector<json> *myshelf = ((Business *)cur_usr)->changeMyShelves();
    vector<json>::iterator it = myshelf->begin();
    do
    {
        system("cls");
        cout << "**************************My Shelf*************************" << endl;
        if (myshelf->empty())
        {
            cout << "Empty" << endl;
            cout << "Press F"
                 << "\t"
                 << "New one here" << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            switch (getch())
            {
            case 'f':
                myshelf->push_back(newgood());
                it = myshelf->begin();
                storedata();
                break;
            case 'q':
                return;
            default:
                system("cls");
                cout << "ERROR: Invalid input." << endl;
                cout << "Press any key to continue." << endl;
                getch();
            }
        }
        else
        {
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
            cout << "Press S"
                 << "\t"
                 << "More" << endl;
            cout << "Press D"
                 << "\t"
                 << "Next" << endl;
            cout << "Press F"
                 << "\t"
                 << "New one here" << endl;
            cout << "Press G"
                 << "\t"
                 << "Delete this" << endl;
            cout << "Press Q"
                 << "\t"
                 << "Go Back" << endl;
            switch (getch())
            {
            case 'a':
                --it;
                if (it < myshelf->begin())
                {
                    system("cls");
                    cout << "No more." << endl;
                    cout << "Press any key to continue." << endl;
                    getch();
                    it = myshelf->begin();
                }
                break;
            case 's':
                managemygood(it);
                storedata();
                break;
            case 'd':
                ++it;
                if (it >= myshelf->end())
                {
                    system("cls");
                    cout << "No more." << endl;
                    cout << "Press any key to continue." << endl;
                    getch();
                    it = myshelf->end() - 1;
                }
                break;
            case 'f':
                it = myshelf->insert(it, newgood());
                storedata();
                break;
            case 'g':
                it = myshelf->erase(it);
                storedata();
                break;
            case 'q':
                return;
            default:
                system("cls");
                cout << "ERROR: Invalid input." << endl;
                cout << "Press any key to continue." << endl;
                getch();
            }
        }
    } while (true);
}

json Page::newgood()
{
    json j;
    do
    {
        system("cls");
        cout << "**************************New Good*************************" << endl;
        cout << "Press A"
             << "\t"
             << "Food" << endl;
        cout << "Press S"
             << "\t"
             << "Clothing" << endl;
        cout << "Press D"
             << "\t"
             << "Book" << endl;
        switch (getch())
        {
        case 'a':
            j["type"] = food;
            break;
        case 's':
            j["type"] = clothing;
            break;
        case 'd':
            j["type"] = book;
            break;
        default:
            system("cls");
            cout << "ERROR: Invalid input." << endl;
            cout << "Press any key to continue." << endl;
            getch();
        }
    } while (j.empty());
    string ipttitle, iptdetail;
    double iptprice;
    unsigned long long iptstock;
    cout << "Input"
         << "\t"
         << "title" << endl;
    std::getline(std::cin, ipttitle, '\n');
    j["title"] = ipttitle;
    cout << "Input"
         << "\t"
         << "detail" << endl;
    std::getline(std::cin, iptdetail, '\n');
    j["detail"] = iptdetail;
    cout << "Input"
         << "\t"
         << "price" << endl;
ipt3:
    cin >> iptprice;
    if (iptprice < 0)
    {
        cout << "Invalid price. Input again." << endl;
        goto ipt3;
    }
    j["price"] = iptprice;
    j["discount"] = 1.0;
    cout << "Input"
         << "\t"
         << "stock" << endl;
    cin >> iptstock;
    j["stock"] = iptstock;
    return j;
}

void Page::storedata()
{
    if (cur_usr->getUserType() == client)
        *usr_json = *(Client *)cur_usr;
    else if (cur_usr->getUserType() == business)
        *usr_json = *(Business *)cur_usr;
    optdata.open("datafile.json");
    optdata << setw(4) << data;
    optdata.close();
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