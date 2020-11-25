#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

class Polynomial {//多项式类
    public:
        struct term {
            double coef;
            double exp;
            term* next;
            term() {coef = 0; exp = 0; next = NULL;}
            term(double _coef, double _exp, term* p = NULL) 
            {coef = _coef; exp = _exp; next = p;}
        };
        
        Polynomial();//构造函数
        Polynomial(const Polynomial &);//拷贝构造函数
        ~Polynomial();//析构函数

        Polynomial operator=(const Polynomial &);//多项式间赋值
        Polynomial operator+(const Polynomial &);//多项式相加
        Polynomial operator-(const Polynomial &);//多项式相减
        Polynomial operator*(const Polynomial &);//多项式相乘
        bool operator==(const Polynomial &);//判断两多项式是否相等

        void insert(double _coef, double _exp);//插入多项式的一个项
        void erase(double _exp);//删除某一项
        void remove_zero();//若其中某一项系数变为0时，删除其对应项
        double assign(double value);//赋值
        void sort();//将多项式按指数降序排序
        term* at(double _exp);//寻找是否存在某一指数项
        void derivation();//求导
        void display();//打印出多项式
        void clear();//清空相应多项式
    private:
        term* head;//多项式首项
};

struct list {//存储多项式的链表结构
    Polynomial storage;
    string name;
    list *next;
};

int flag2 = 0;//用作判断输入的数据是否有错的标识

list *hpoly = NULL;//全局变量，计算器中存储多项式链表的头

Polynomial p1, p2, p3;//全局变量，用来暂时存储输入和输出的多项式

void menu();//打印菜单
void in(string s, int num);//输入处理
void save();//询问是否存储相应计算结果

void add();//多项式相加
void subtract();//多项式相减
void multiply();//多项式相乘
void assign();//赋值求值
void show();//打印出相应已存储的多项式及对应名字
void isEqual();//判断两多项式是否相等
void derivation();//对多项式求导