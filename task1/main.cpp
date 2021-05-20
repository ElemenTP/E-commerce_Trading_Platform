#include "global.hpp"
using namespace std;
using json = nlohmann::json;

int main(void)
{
    system("chcp 65001");
    json data;
    Account *cur_usr = NULL;
    int usr_ptr;
    ifstream iptdata("datafile.json");
    ofstream optdata;
    if (iptdata)
        iptdata >> data;
    iptdata.close();
    bool start_page_state = true, content_page_state;
    while (true)
    {
        system("cls");
        while (start_page_state)
        {
            cout << "**********************电商交易平台**********************" << endl;
            try
            {
                cout << "输入1" << setw(50) << "注册新账户" << endl;
                if (!data.empty())
                {
                    cout << "输入2" << setw(50) << "登录已有账户" << endl;
                    cout << "输入3" << setw(50) << "以游客身份浏览货架" << endl;
                }
                int ipt;
                cin >> ipt;
                system("cls");
                switch (ipt)
                {
                case 1:
                    cout << "输入1" << setw(50) << "注册新客户账户" << endl;
                    cout << "输入2" << setw(50) << "注册新商家账户" << endl;
                    cout << "输入3" << setw(50) << "返回" << endl;
                    int ipt;
                    cin >> ipt;
                    system("cls");
                    switch (ipt)
                    {
                    case 1:
                    {
                        string iptname, iptpasswd;
                        cout << "输入" << setw(50) << "新账户的名称" << endl;
                        cin >> iptname;
                        for (int it = 0; it < data.size(); it++)
                        {
                            if (data[it]["name"].get<string>() == iptname)
                                throw "错误：该名称已被使用\n";
                        }
                        cout << "输入" << setw(50) << "新账户的密码" << endl;
                        cin >> iptpasswd;
                        cur_usr = new Client(iptname, iptpasswd);
                        json j = *(Client *)cur_usr;
                        usr_ptr = data.size();
                        data.push_back(j);
                        optdata.open("datafile.json");
                        optdata << setw(4) << data;
                        optdata.close();
                        start_page_state = false;
                        break;
                    }
                    case 2:
                    {
                        string iptname, iptpasswd;
                        cout << "输入" << setw(50) << "新账户的名称" << endl;
                        cin >> iptname;
                        for (int it = 0; it < data.size(); it++)
                        {
                            if (data[it]["name"].get<string>() == iptname)
                                throw "错误：该名称已被使用\n";
                        }
                        cout << "输入" << setw(50) << "新账户的密码" << endl;
                        cin >> iptpasswd;
                        cur_usr = new Business(iptname, iptpasswd);
                        json j = *(Business *)cur_usr;
                        usr_ptr = data.size();
                        data.push_back(j);
                        optdata.open("datafile.json");
                        optdata << setw(4) << data;
                        optdata.close();
                        start_page_state = false;
                        break;
                    }
                    case 3:
                        break;

                    default:
                        throw "错误:输入不合法\n";
                    }
                    break;

                case 2:
                {
                    if (data.empty())
                        throw "错误:输入不合法\n";
                    string iptname, iptpasswd;
                    cout << "输入" << setw(50) << "账户的名称" << endl;
                    cin >> iptname;
                    cout << "输入" << setw(50) << "账户的密码" << endl;
                    cin >> iptpasswd;
                    for (int it = 0; it < data.size(); it++)
                    {
                        if (data[it]["name"].get<string>() == iptname && data[it]["passwd"].get<string>() == iptpasswd)
                        {
                            usr_ptr = it;
                            if (data[it]["type"].get<int>() == client)
                            {
                                cur_usr = new Client();
                                *(Client *)cur_usr = data[it];
                            }
                            else if (data[it]["type"].get<int>() == business)
                            {
                                cur_usr = new Business();
                                *(Business *)cur_usr = data[it];
                            }
                        }
                    }
                    if (!cur_usr)
                        throw "错误：用户名或密码错误\n";
                    else
                        start_page_state = false;
                    break;
                }

                case 3:
                    if (!data.empty())
                    {
                        start_page_state = false;
                        break;
                    }

                default:
                    throw "错误:输入不合法\n";
                }
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                system("pause");
            }
        }
        content_page_state = true;
        system("cls");
        while (content_page_state)
        {
            switch (cur_usr == NULL)
            {
            case false:
            {
                break;
            }
            case true:
            {
                int acc_ptr = 0;
                while (data[acc_ptr]["type"].get<int>() != business)
                {
                    acc_ptr++;
                    if (acc_ptr == data.size())
                        break;
                }
                if (acc_ptr < data.size())
                {
                    int ipt = 0;
                    do
                    {
                        Business acc_tmp = data[acc_ptr];
                        for (int mer_ptr = 0; mer_ptr < (*(acc_tmp.getMyShelves())).size() && mer_ptr > -1 && content_page_state;)
                        {
                            bool input_bad;
                            do
                            {
                                cout << "**********************全部商品**********************" << endl;
                                switch ((*(acc_tmp.getMyShelves()))[mer_ptr]["type"].get<int>())
                                {
                                case food:
                                {
                                    Food mer_tmp = (*(acc_tmp.getMyShelves()))[mer_ptr];
                                    mer_tmp.optItemDes();
                                    break;
                                }
                                case clothing:
                                {
                                    Clothing mer_tmp = (*(acc_tmp.getMyShelves()))[mer_ptr];
                                    mer_tmp.optItemDes();
                                    break;
                                }
                                case book:
                                {
                                    Book mer_tmp = (*(acc_tmp.getMyShelves()))[mer_ptr];
                                    mer_tmp.optItemDes();
                                    break;
                                }
                                }
                                cout << "输入1" << setw(50) << "下一个" << endl;
                                cout << "输入2" << setw(50) << "上一个" << endl;
                                cout << "输入3" << setw(50) << "退出" << endl;
                                cin >> ipt;
                                switch (ipt)
                                {
                                case 1:
                                    mer_ptr++;
                                    input_bad = false;
                                    break;

                                case 2:
                                    mer_ptr--;
                                    input_bad = false;
                                    break;

                                case 3:
                                    content_page_state = false;
                                    input_bad = false;
                                    break;
                                default:
                                    system("cls");
                                    cout << "错误：输入不合法";
                                    system("pause");
                                    input_bad = true;
                                    system("cls");
                                }
                            } while (input_bad);
                            system("cls");
                        }
                        int acc_ptr_bkp = acc_ptr;
                        switch (ipt)
                        {
                        case 1:
                        {
                            while (data[acc_ptr]["type"].get<int>() != business)
                            {
                                acc_ptr++;
                                if (acc_ptr == data.size())
                                    break;
                            }
                            if (acc_ptr == data.size())
                            {
                                cout << "没有更多了！\n";
                                system("pause");
                                acc_ptr = acc_ptr_bkp;
                                system("cls");
                            }
                        }
                        case 2:
                        {
                            while (data[acc_ptr]["type"].get<int>() != business)
                            {
                                acc_ptr--;
                                if (acc_ptr == -1)
                                    break;
                            }
                            if (acc_ptr < 0)
                            {
                                cout << "没有更多了！\n";
                                system("pause");
                                acc_ptr = acc_ptr_bkp;
                                system("cls");
                            }
                        }
                        }
                    } while (content_page_state);
                    if (ipt == 0)
                    {
                        cout << "没有商品可以展示。\n";
                        system("pause");
                        system("cls");
                    }
                }
                else
                {
                    cout << "没有商品可以展示。\n";
                    system("pause");
                    system("cls");
                }
                if (cur_usr)
                    content_page_state = true;
            }
            }
        }
        start_page_state = true;
    }
}
