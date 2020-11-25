#ifndef BIN_HPP
#define BIN_HPP

#include "campus_card.hpp"
#include "deposit_card.hpp"
using namespace std;

//继承campus_card和deposit_card类的binding_card类
class binding_card: public campus_card, public deposit_card{
    public:
        binding_card();
        void pay(double amount);//特殊支付功能
        void inquire(int a);//查询
        void Wr_file_rec(char s[], string operation);//写入
        void setBinding_card(long _id);//设置绑定储蓄卡的id
        void show_cards();//打印出已绑定的储蓄卡
        deposit_card& getdeposit_card(long _id);//获取对应id的储蓄卡
        bool isd_card(long _id);//判断是否存在该储蓄卡
        int getNum();//获取储蓄卡数目
        string getId();//获取储蓄卡id
    private:
        deposit_card binding_id[20];//绑定的储蓄卡
        int num;//储蓄卡的数目
};

#endif