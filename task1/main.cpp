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
        while (start_page_state)
        {
            system("cls");
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
                                throw "错误：该名称已被使用";
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
                                throw "错误：该名称已被使用";
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
                        throw "错误:输入不合法";
                    }
                    break;

                case 2:
                {
                    if (data.empty())
                        throw "错误:输入不合法";
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
                        throw "错误：用户名或密码错误";
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
                    throw "错误:输入不合法";
                }
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                system("pause");
            }
        }
        content_page_state = true;
        while (content_page_state)
        {
            system("cls");
            try
            {
                switch (cur_usr == NULL)
                {
                case false:
                {
                    int ipt;
                    bool loop_page;
                    do
                    {
                        cout << "**********************我的账户**********************" << endl;
                        cur_usr->optAccoutDet();
                        cout << "输入1" << setw(50) << "更改用户名" << endl;
                        cout << "输入2" << setw(50) << "更改密码" << endl;
                        cout << "输入3" << setw(50) << "充值余额" << endl;
                        cout << "输入4" << setw(50) << "提取余额" << endl;
                        cout << "输入5" << setw(50) << "浏览全部商品" << endl;
                        if (cur_usr->getUserType() == business)
                            cout << "输入6" << setw(50) << "浏览我的货架" << endl;
                        cout << "输入7" << setw(50) << "注销" << endl;
                        cin >> ipt;
                        system("cls");
                        switch (ipt)
                        {
                        case 1:
                        {
                            string iptpasswd, newname;
                            cout << "输入" << setw(50) << "账户密码" << endl;
                            cin >> iptpasswd;
                            if (cur_usr->checkpasswd(iptpasswd))
                            {
                                cout << "输入" << setw(50) << "新用户名" << endl;
                                cin >> newname;
                                cur_usr->changeName(iptpasswd, newname);
                                json j;
                                if (cur_usr->getUserType() == client)
                                    j = *(Client *)cur_usr;
                                else if (cur_usr->getUserType() == business)
                                    j = *(Business *)cur_usr;
                                data[usr_ptr] = j;
                                optdata.open("datafile.json");
                                optdata << setw(4) << data;
                                optdata.close();
                                cout << "用户名更改成功" << endl;
                                system("pause");
                            }
                            else
                                throw "密码不匹配";
                            loop_page = true;
                            break;
                        }

                        case 2:
                        {
                            string iptpasswd, newpasswd;
                            cout << "输入" << setw(50) << "账户密码" << endl;
                            cin >> iptpasswd;
                            if (cur_usr->checkpasswd(iptpasswd))
                            {
                                cout << "输入" << setw(50) << "新密码" << endl;
                                cin >> newpasswd;
                                cur_usr->changepasswd(iptpasswd, newpasswd);
                                json j;
                                if (cur_usr->getUserType() == client)
                                    j = *(Client *)cur_usr;
                                else if (cur_usr->getUserType() == business)
                                    j = *(Business *)cur_usr;
                                data[usr_ptr] = j;
                                optdata.open("datafile.json");
                                optdata << setw(4) << data;
                                optdata.close();
                                cout << "密码更改成功" << endl;
                                system("pause");
                            }
                            else
                                throw "密码不匹配";
                            loop_page = true;
                            break;
                        }

                        case 3:
                        {
                            string iptpasswd;
                            double money;
                            cout << "输入" << setw(50) << "账户密码" << endl;
                            cin >> iptpasswd;
                            if (cur_usr->checkpasswd(iptpasswd))
                            {
                                cout << "输入" << setw(50) << "充值金额" << endl;
                                cin >> money;
                                cur_usr->changeBalance(iptpasswd, money);
                                json j;
                                if (cur_usr->getUserType() == client)
                                    j = *(Client *)cur_usr;
                                else if (cur_usr->getUserType() == business)
                                    j = *(Business *)cur_usr;
                                data[usr_ptr] = j;
                                optdata.open("datafile.json");
                                optdata << setw(4) << data;
                                optdata.close();
                                cout << "充值成功" << endl;
                                system("pause");
                            }
                            else
                                throw "密码不匹配";
                            loop_page = true;
                            break;
                        }

                        case 4:
                        {
                            string iptpasswd;
                            double money;
                            cout << "输入" << setw(50) << "账户密码" << endl;
                            cin >> iptpasswd;
                            if (cur_usr->checkpasswd(iptpasswd))
                            {
                                cout << "输入" << setw(50) << "提取金额" << endl;
                                cin >> money;
                                cur_usr->changeBalance(iptpasswd, -money);
                                json j;
                                if (cur_usr->getUserType() == client)
                                    j = *(Client *)cur_usr;
                                else if (cur_usr->getUserType() == business)
                                    j = *(Business *)cur_usr;
                                data[usr_ptr] = j;
                                optdata.open("datafile.json");
                                optdata << setw(4) << data;
                                optdata.close();
                                cout << "提款成功" << endl;
                                system("pause");
                            }
                            else
                                throw "密码不匹配";
                            loop_page = true;
                            break;
                        }

                        case 5:
                        {
                            int acc_ptr = 0;
                            bool shelves_page_state = true;
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
                                    for (int mer_ptr = 0; mer_ptr < (*(acc_tmp.getMyShelves())).size() && mer_ptr > -1 && shelves_page_state;)
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
                                                shelves_page_state = false;
                                                input_bad = false;
                                                break;
                                            default:
                                                system("cls");
                                                cout << "错误：输入不合法" << endl;
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
                                            cout << "没有更多了！" << endl;
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
                                            cout << "没有更多了！" << endl;
                                            system("pause");
                                            acc_ptr = acc_ptr_bkp;
                                            system("cls");
                                        }
                                    }
                                    }
                                } while (shelves_page_state);
                                if (ipt == 0)
                                {
                                    cout << "没有商品可以展示。" << endl;
                                    system("pause");
                                    system("cls");
                                    shelves_page_state = false;
                                }
                            }
                            else
                            {
                                cout << "没有商品可以展示。" << endl;
                                system("pause");
                                system("cls");
                                shelves_page_state = false;
                            }
                            loop_page = true;
                            break;
                        }

                        case 6:
                        {
                            string iptpasswd;
                            cout << "输入" << setw(50) << "账户密码" << endl;
                            cin >> iptpasswd;
                            if (cur_usr->checkpasswd(iptpasswd))
                            {
                                bool shelves_page_state = true;
                                int ipt = 0;
                                do
                                {
                                    for (int mer_ptr = 0; mer_ptr < (*(((Business *)cur_usr)->changeMyShelves(iptpasswd))).size() && mer_ptr > -1 && shelves_page_state;)
                                    {
                                        bool input_bad;
                                        do
                                        {
                                            cout << "**********************我的商品**********************" << endl;
                                            switch ((*(((Business *)cur_usr)->changeMyShelves(iptpasswd)))[mer_ptr]["type"].get<int>())
                                            {
                                            case food:
                                            {
                                                Food mer_tmp = (*(((Business *)cur_usr)->changeMyShelves(iptpasswd)))[mer_ptr];
                                                mer_tmp.optItemDes();
                                                break;
                                            }
                                            case clothing:
                                            {
                                                Clothing mer_tmp = (*(((Business *)cur_usr)->changeMyShelves(iptpasswd)))[mer_ptr];
                                                mer_tmp.optItemDes();
                                                break;
                                            }
                                            case book:
                                            {
                                                Book mer_tmp = (*(((Business *)cur_usr)->changeMyShelves(iptpasswd)))[mer_ptr];
                                                mer_tmp.optItemDes();
                                                break;
                                            }
                                            }
                                            cout << "输入1" << setw(50) << "下一个" << endl;
                                            cout << "输入2" << setw(50) << "上一个" << endl;
                                            cout << "输入3" << setw(50) << "退出" << endl;
                                            cout << "输入4" << setw(50) << "上架商品" << endl;
                                            cout << "输入5" << setw(50) << "下架商品" << endl;
                                            cout << "输入6" << setw(50) << "修改名称" << endl;
                                            cout << "输入7" << setw(50) << "修改详情" << endl;
                                            cout << "输入8" << setw(50) << "修改价格" << endl;
                                            cout << "输入9" << setw(50) << "修改折扣" << endl;
                                            cout << "输入10" << setw(50) << "修改库存" << endl;
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
                                                shelves_page_state = false;
                                                input_bad = false;
                                                break;

                                            case 4:
                                            {
                                                json j;
                                                int ipt1 = 0;
                                                do
                                                {
                                                    system("cls");
                                                    cout << "输入1" << setw(50) << "食品" << endl;
                                                    cout << "输入2" << setw(50) << "衣服" << endl;
                                                    cout << "输入3" << setw(50) << "书籍" << endl;
                                                    cout << "输入4" << setw(50) << "取消" << endl;
                                                    cin >> ipt1;
                                                    switch (ipt1)
                                                    {
                                                    case 1:
                                                        j["type"] = food;
                                                        break;
                                                    case 2:
                                                        j["type"] = clothing;
                                                        break;
                                                    case 3:
                                                        j["type"] = book;
                                                        break;
                                                    case 4:
                                                        break;
                                                    default:
                                                        system("cls");
                                                        cout << "错误：输入不合法" << endl;
                                                        system("pause");
                                                        ipt1 = 0;
                                                        system("cls");
                                                    }
                                                } while (!ipt1);
                                                system("cls");
                                                if (ipt1 < 4)
                                                {
                                                    string ipttitle, iptdes;
                                                    double iptpricing;
                                                    float iptdiscount;
                                                    unsigned long long iptstock;
                                                    cout << "输入" << setw(50) << "商品名称" << endl;
                                                    cin >> ipttitle;
                                                    j["title"] = ipttitle;
                                                    cout << "输入2" << setw(50) << "商品详情" << endl;
                                                    cin >> iptdes;
                                                    j["description"] = iptdes;
                                                    cout << "输入3" << setw(50) << "商品标价" << endl;
                                                    cin >> iptpricing;
                                                    j["pricing"] = iptpricing;
                                                    cout << "输入1" << setw(50) << "商品折扣" << endl;
                                                    cin >> iptdiscount;
                                                    j["discount"] = iptdiscount;
                                                    cout << "输入2" << setw(50) << "商品库存" << endl;
                                                    cin >> iptstock;
                                                    j["stock"] = iptstock;
                                                    (*(((Business *)cur_usr)->changeMyShelves(iptpasswd))).push_back(j);
                                                    if (cur_usr->getUserType() == client)
                                                        j = *(Client *)cur_usr;
                                                    else if (cur_usr->getUserType() == business)
                                                        j = *(Business *)cur_usr;
                                                    data[usr_ptr] = j;
                                                    optdata.open("datafile.json");
                                                    optdata << setw(4) << data;
                                                    optdata.close();
                                                    cout << "添加商品成功" << endl;
                                                    system("pause");
                                                }
                                            }

                                            case 5:

                                            case 6:

                                            case 7:

                                            case 8:

                                            case 9:

                                            case 10:

                                            default:
                                                system("cls");
                                                cout << "错误：输入不合法" << endl;
                                                system("pause");
                                                input_bad = true;
                                                system("cls");
                                            }
                                        } while (input_bad);
                                        system("cls");
                                    }
                                } while (shelves_page_state);
                                if (ipt == 0)
                                {
                                    int ipt2 = 0;
                                    do
                                    {
                                        cout << "货架里没有商品。" << endl;
                                        cout << "输入1" << setw(50) << "上架商品" << endl;
                                        cout << "输入2" << setw(50) << "退出" << endl;
                                        cin >> ipt2;
                                        switch (ipt2)
                                        {
                                        case 1:
                                        {
                                            json j;
                                            int ipt1 = 0;
                                            do
                                            {
                                                system("cls");
                                                cout << "输入1" << setw(50) << "食品" << endl;
                                                cout << "输入2" << setw(50) << "衣服" << endl;
                                                cout << "输入3" << setw(50) << "书籍" << endl;
                                                cout << "输入4" << setw(50) << "取消" << endl;
                                                cin >> ipt1;
                                                switch (ipt1)
                                                {
                                                case 1:
                                                    j["type"] = food;
                                                    break;
                                                case 2:
                                                    j["type"] = clothing;
                                                    break;
                                                case 3:
                                                    j["type"] = book;
                                                    break;
                                                case 4:
                                                    break;
                                                default:
                                                    system("cls");
                                                    cout << "错误：输入不合法" << endl;
                                                    system("pause");
                                                    ipt1 = 0;
                                                    system("cls");
                                                }
                                            } while (!ipt1);
                                            system("cls");
                                            if (ipt1 < 4)
                                            {
                                                string ipttitle, iptdes;
                                                double iptpricing;
                                                float iptdiscount;
                                                unsigned long long iptstock;
                                                cout << "输入" << setw(50) << "商品名称" << endl;
                                                cin >> ipttitle;
                                                j["title"] = ipttitle;
                                                cout << "输入2" << setw(50) << "商品详情" << endl;
                                                cin >> iptdes;
                                                j["description"] = iptdes;
                                                cout << "输入3" << setw(50) << "商品标价" << endl;
                                                cin >> iptpricing;
                                                j["pricing"] = iptpricing;
                                                cout << "输入1" << setw(50) << "商品折扣" << endl;
                                                cin >> iptdiscount;
                                                j["discount"] = iptdiscount;
                                                cout << "输入2" << setw(50) << "商品库存" << endl;
                                                cin >> iptstock;
                                                j["stock"] = iptstock;
                                                (*(((Business *)cur_usr)->changeMyShelves(iptpasswd))).push_back(j);
                                                if (cur_usr->getUserType() == client)
                                                    j = *(Client *)cur_usr;
                                                else if (cur_usr->getUserType() == business)
                                                    j = *(Business *)cur_usr;
                                                data[usr_ptr] = j;
                                                optdata.open("datafile.json");
                                                optdata << setw(4) << data;
                                                optdata.close();
                                                cout << "添加商品成功" << endl;
                                                system("pause");
                                            }
                                        }

                                        case 2:
                                        {
                                        }
                                        default:
                                        {
                                        }
                                        }
                                    } while (!ipt2);
                                }
                                loop_page = true;
                                break;
                            }

                            else
                                throw "密码不匹配";
                            loop_page = true;
                            break;
                        }

                        case 7:
                            loop_page = false;
                            content_page_state = false;
                            break;

                        default:
                            system("cls");
                            cout << "错误：输入不合法" << endl;
                            system("pause");
                            loop_page = true;
                            system("cls");
                        }
                    } while (loop_page);
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
                                        cout << "错误：输入不合法" << endl;
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
                                    cout << "没有更多了！" << endl;
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
                                    cout << "没有更多了！" << endl;
                                    system("pause");
                                    acc_ptr = acc_ptr_bkp;
                                    system("cls");
                                }
                            }
                            }
                        } while (content_page_state);
                        if (ipt == 0)
                        {
                            cout << "没有商品可以展示。" << endl;
                            system("pause");
                            system("cls");
                            content_page_state = false;
                        }
                    }
                    else
                    {
                        cout << "没有商品可以展示。" << endl;
                        system("pause");
                        system("cls");
                        content_page_state = false;
                    }
                }
                }
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                system("pause");
            }
        }
        start_page_state = true;
    }
}
