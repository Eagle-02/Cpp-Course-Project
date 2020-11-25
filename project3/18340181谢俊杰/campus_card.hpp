#ifndef CAM_HPP
#define CAM_HPP

#include "card.hpp"
using namespace std;

//继承card类的campus_card类
class campus_card: virtual public card{
    public:  
        campus_card();
        void pay(double amount);//支付
        void inquire(int a);//查询
        void Wr_file_rec(char s[], string operation);//写入
        void transfer_in(double amount);//只能通过储蓄卡转账存入
        void setCollege(string college);//设置学院
        string getCollege();//获取学院
    private:
        string college;//学院
};

#endif