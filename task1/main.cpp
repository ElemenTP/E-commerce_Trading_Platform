#include "global.hpp"
using namespace std;
using json = nlohmann::json;

int main(void)
{
    json data;
    Account *cur_usr;
    vector<const json *> allShelves;
    ifstream iptdata("datafile.json");
    ofstream optdata("datafile.json");
    if (iptdata)
        iptdata >> data;
START:
    system("cls");
    cout << "**********************电商交易平台**********************" << endl;
    try
    {
        cout << setw(20) << "输入1" << setw(40) << "注册新账户" << endl;
        if (!data.empty())
        {
            cout << setw(20) << "输入2" << setw(40) << "登录已有账户" << endl;
            cout << setw(20) << "输入3" << setw(40) << "以游客身份浏览货架" << endl;
        }
        int ipt;
        cin >> ipt;
        system("cls");
        switch (ipt)
        {
        case 1:
            cout << setw(20) << "输入1" << setw(40) << "注册新客户账户" << endl;
            cout << setw(20) << "输入2" << setw(40) << "注册新商家账户" << endl;
            int ipt;
            cin >> ipt;
            system("cls");
            switch (ipt)
            {
            case 1:
            {
                string iptname, iptpasswd;
                cout << setw(20) << "输入" << setw(40) << "新账户的名称" << endl;
                cin >> iptname;
                cout << setw(20) << "输入" << setw(40) << "新账户的密码" << endl;
                cin >> iptpasswd;
                if (iptpasswd.empty())
                {
                    throw "错误：密码不能为空\n";
                    break;
                }
                cur_usr = new Client(iptname, iptpasswd);
                json j = *(Client *)cur_usr;
                data.push_back(j);
                optdata << setw(4) << data;
                break;
            }
            case 2:
            {
                string iptname, iptpasswd;
                cout << setw(20) << "输入" << setw(40) << "新账户的名称" << endl;
                cin >> iptname;
                cout << setw(20) << "输入" << setw(40) << "新账户的密码" << endl;
                cin >> iptpasswd;
                if (iptpasswd.empty())
                {
                    throw "错误：密码不能为空\n";
                    break;
                }
                cur_usr = new Business(iptname, iptpasswd);
                json j = *(Business *)cur_usr;
                data.push_back(j);
                optdata << setw(4) << data;
                break;
            }

            default:
                throw "错误:输入不合法\n";
            }
            break;

        case 2:
        {
            if (data.empty())
                break;
            string iptname, iptpasswd;
            cout << setw(20) << "输入" << setw(40) << "账户的名称" << endl;
            cin >> iptname;
            cout << setw(20) << "输入" << setw(40) << "账户的密码" << endl;
            cin >> iptpasswd;
            if (iptpasswd.empty())
            {
                throw "错误：密码不能为空\n";
                break;
            }
            for (int it = 0; it < data.size(); it++)
            {
                if (data[it]["name"].get<string>() == iptname && data[it]["passwd"].get<string>() == iptpasswd)
                {
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
            break;
        }

        case 3:
            if (!data.empty())
                break;

        default:
            throw "错误:输入不合法\n";
            break;
        }
    }
    catch (const char *msg)
    {
        cout << *msg << endl;
        goto START;
    }
}
