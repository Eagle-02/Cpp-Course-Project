#include "goods.hpp"

int main()
{
    int flag = 1;
    Re_file();  //读取仓库中原有数据goods_data.txt
    while (flag) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "~                                          ~" << endl
             << "~    Welcome to STORE v1.0.0               ~" << endl
             << "~    Menu:                                 ~" << endl
             << "~         1.Add some goods                 ~" << endl
             << "~         2.Delete some goods              ~" << endl  //打印菜单
             << "~         3.Show the goods                 ~" << endl
             << "~         4.Find a goods                   ~" << endl
             << "~         5.Exit                           ~" << endl
             << "~                                          ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Please enter what you want to do next:";
        cin >> flag;//输入要进行的功能
        switch (flag) {
            case 1: _add(); break;
            case 2: _delete(); break;
            case 3: show_goods(); break;
            case 4: find(); break;
            case 5: Wr_file(); exit(0); flag = 0; break;//退出前将仓库数据写入goods_data.txt
        }
    }
    
    return 0;
}

void Re_file()
{
    int N = 0;                                                            //读入goods_data.txt文件储存的数据
    ifstream in("goods_data.txt", ios::binary | ios::app | ios::in | ios::out);//且防止读入时清空数据
    while (!in.eof()) {
        in >> goods[N].name >> goods[N].count;
        if (goods[N].name != "\0")
            N++;
    }
    in.close();
    P = N;
}

void Wr_file()
{
    ofstream out("goods_data.txt");//写入goods_data.txt，且在写入时清空原有数据，防止重复写入
    for (int i = 0; i < P; i++) {
        out << goods[i].name << " "     //写入时需有空格 以下次启动读入
            << goods[i].count << endl;
    }
    out.close();
}

void _add()
{
    int flag1 = 1, count = 0;
    string name;
    while (flag1) {
        cout << "Please enter the name of goods:";
        cin >> name;//进货商品的名称
        cout << "Please enter the quantity of goods:";
        cin >> count;//对应进货商品数量
        add_goods(name, count);//仓库进货
        cout << "Do you want to continue stocking with goods?" << endl
             << "1.yes       2.no" << endl;
        cin >> flag1;     
        if (flag1 != 1) //若不继续进货则退出进货功能
            break;
    }
}

void add_goods(string name, int count)
{
    int i = P, j = 0;
    for (j = 0; j < i; j++) {
        if (name == goods[j].name) { //仓库中有该商品时增加库存量
            time_t t = time(0);     //获取当前时间
            char _time[64];
            strftime(_time, sizeof(_time), "%Y/%m/%d %X %A %z", localtime(&t));
            goods[j].count += count;
            ofstream out("goods_record.txt", ios::binary | ios::app | ios::in | ios::out);
            out << "add:" << left << setw(20) << name 
                << left <<setw(20) << count << _time << "\r\n";//将操作写入日志goods_record.txt
            out.close();
            return ;
        }
    }
    if (j == i) {
        add_to_list(name, count);   //若没有此商品，则新增项目
    }
}

void add_to_list(string name, int count)
{
    time_t t = time(0);     //获取当前时间
    char _time[64];
    strftime(_time, sizeof(_time), "%Y/%m/%d %X %A %z", localtime(&t));
    goods[P].name = name;   //新增商品名称
    goods[P++].count = count;//新增商品库存
    ofstream out("goods_record.txt", ios::binary | ios::app | ios::in | ios::out);
    out << "create:" << left << setw(20) << name 
        << left << setw(20) << count << _time << "\r\n";//将操作写入日志goods_record.txt
    out.close();  
}

void _delete()
{
    int flag1 = 1, count = 0;
    string name;
    while (flag1) {
        cout << "Please enter the name of goods:";
        cin >> name;//出货商品名称
        cout << "Please enter the quantity of goods:";
        cin >> count;//对应出货商品数量
        delete_goods(name, count);//仓库出货
        cout << "Do you want to continue deleting some goods?" << endl
             << "1.yes       2.no" << endl;
        cin >> flag1;     
        if (flag1 != 1) //若不继续出货则退出进货功能
            break;
    }
}

void delete_goods(string name, int count)
{
    int i = P, j = 0;
    for (j = 0; j < i; j++) {
        if (name == goods[j].name) {    //从仓库中找出所要出货的商品
            goods[j].count -= count;
            if (goods[j].count > 0) {
                time_t t = time(0);     //获取当前时间
                char _time[64];
                strftime(_time, sizeof(_time), "%Y/%m/%d %X %A %z", localtime(&t));
                ofstream out("goods_record.txt", ios::binary | ios::app | ios::in | ios::out);
                out << "decrease:" << left << setw(20) << name 
                    << left << setw(20) << count << _time << "\r\n";//将操作写入日志goods_record.txt
                out.close();
            }
            else if (goods[j].count == 0) {  //若出货成功，出货后库存为0，则删除仓库目录中此商品项目
                delete_from_list(goods[j].name);
                time_t t = time(0);     //获取当前时间
                char _time[64];
                strftime(_time, sizeof(_time), "%Y/%m/%d %X %A %z", localtime(&t));
                ofstream out("goods_record.txt", ios::binary | ios::app | ios::in | ios::out);
                out << "decrease and delete from the list:" << left << setw(20) << name 
                    << left << setw(20) << count << _time << "\r\n";//将操作写入日志goods_record.txt
                out.close();
            }
            else if (goods[j].count < 0) {   //若库存不足，则出货失败
                cout << "Failing to sell them for you don't have enough stocks" <<endl;
                goods[j].count +=count;
                time_t t = time(0);      //获取当前时间
                char _time[64];
                strftime(_time, sizeof(_time), "%Y/%m/%d %X %A %z", localtime(&t));
                ofstream out("goods_record.txt", ios::binary | ios::app | ios::in | ios::out);
                out << "try to decrease but fail:" << left << setw(20) << name  //将操作写入日志goods_record.txt
                    << left << setw(20) << count << _time << "\r\n";
                out.close();
            }
            return ; 
        }
    }
}

void delete_from_list(string name)
{
    for (int i = 0; i < P; i++) {
        if (goods[i].name == name) {
            if (i != P - 1) {   //出货的此商品若非仓库目录最后一项，则其后面的商品往前移动填补空缺
                goods[i].name = goods[i + 1].name;
                goods[i].count = goods[i + 1].count;
            }
            else {      //若为最后一项，则直接删除
                goods[i].name = '\0';
                goods[i].count = 0;
            }
            P--;
        }
    }
}

void show_goods()
{
    cout << left << setw(20) << "name" 
         << left << setw(20) << "quantity" <<endl;
    for (int i = 0; i < P; i++) {       //打印仓库目录中的商品名称及库存
        cout << left << setw(20) << goods[i].name
             << left << setw(20) << goods[i].count << endl;
    }
}

void find()
{
    string name;
    struct Goods p;
    cout << "Enter the name of goods that you find:";
    cin >> name;//输入所要寻找的商品名称
    p = find_goods(name);
    if (p.name == "\0") {
        cout << "There is no such thing." << endl;//不存在此商品
    }
    else {
        cout << left << setw(20) << "name" 
             << left << setw(20) << "quantity" <<endl;
        cout << left << setw(20) << p.name//打印所要寻找的商品名称及库存
             << left << setw(20) << p.count << endl;
    }
}

struct Goods find_goods(string name)
{
    for (int i = 0; i < P; i++) {
        if (goods[i].name == name) {    //若寻找到该商品并返回
            return goods[i];
        }
    }
    return goods[P]; 
}