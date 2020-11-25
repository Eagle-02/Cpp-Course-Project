#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Goods {
    string name; //记录货物名
    int count;  //记录货物数量
};
int P;//记录仓库中已有商品数量
struct Goods goods[10001];//仓库总容量

void Re_file();//读取文件
void Wr_file();//写入文件

//进货
void _add();//菜单功能1

void add_goods(string name, int count);//进货，对应进货模块，表示当前进货一批数量为count的name商品

void add_to_list(string name, int count); //更新库存列表，对应新增商品子功能，新增name商品且初始数量为count

//出货
void _delete();//菜单功能2

void delete_goods(string name, int count);//出货，对应出货模块，表示当前出货一批数量为count的name商品

void delete_from_list(string name);//更新库存列表，对应删除商品子功能，删除商品列表中name商品

//查询
void show_goods(); //菜单功能3，显示当前库存列表，包括商品名及其库存量

void find();//菜单功能4，查找商品是否存在库存及库存量

struct Goods find_goods(string name);//查看仓库中的name商品