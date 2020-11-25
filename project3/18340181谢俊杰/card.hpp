#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

void Re_file_inf();//读取信息
void Wr_file_inf();//写入信息
void Re_file_rec(char s[], int a);//读取流水账

//获取系统时间
string get_time();

//卡基类
class card{
    public:
        card(){balance = 0; amount = 0;}
        ~card(){}
        virtual void pay(double amount){}//支付函数
        virtual void inquire(int a){}//查询函数
        virtual void Wr_file_rec(char s[], string operation){}//写入流水账
        long id;//学号或卡号
        string date;//建卡日期
        string password;//密码
        string name;//姓名
        double balance;//余额
        double amount;//收入（+）或支出（-）
};

#endif 