#ifndef DEP_HPP
#define DEP_HPP

#include "card.hpp"
using namespace std;

//继承卡类的deposit_card类
class deposit_card: virtual public card{
    public:
        deposit_card();
        void pay(double amount);//支付
        void inquire(int a);//查询
        void Wr_file_rec(char s[], string operation);//写入
        void deposit(double amount);//存储
        bool transfer_out(double amount);//转账到另一卡
        void setUsed_q(double num);//设置已用额度
        void setSpare_q(double num);//设置剩余额度
        double getUsed_q();//获取已用额度
        double getSpare_q();//获取剩余额度
        void repay();//还款
    private:
        double total_quota;//总透支额度
        double used_quota;//已使用透支额度
        double spare_quota;//剩余透支额度
};

#endif