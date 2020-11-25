#include "binding_card.hpp"

binding_card::binding_card(): campus_card(), deposit_card()
{}
//支付
void binding_card::pay(double n)
{
    if (balance - n < 0) {
        cout << "You don't have enough money to pay." << endl;
        while (1) {//余额不足时选择一已绑定的储蓄卡进行支付
            cout << "Please enter the id of your deposit_card to pay.(or enter 0 to quit)" << endl;
            long _id;
            int flag = 0;
            cin >> _id;
            if (_id == 0) 
                break;
            for (int i = 0; i < num; i++) {
                if (_id == binding_id[i].id) {
                    flag = 1;
                    binding_id[i].pay(n);
                    break;
                }
            }
            if (flag == 0) {
                cout << "There is no such card binding yours. Please check it again." << endl;
                continue;
            }
            else if (flag == 1) {
                break;
            }
        }
        return ;
    }
    balance -= n;
    amount = -n;
    char s1[64];
    sprintf(s1, "%ld.txt", id);
    Wr_file_rec(s1, "pay");
    cout << "You have paid it successfully! " <<endl;
}
//查询
void binding_card::inquire(int a)
{
    if (a == 1) {//查询信息
        cout << left << setw(20) << "id" 
             << left << setw(20) << "date"
             << left << setw(12) << "name" 
             << left << setw(12) << "college"
             << left << setw(12) << "balance" << endl;
        cout << left << setw(20) << id 
             << left << setw(20) << date
             << left << setw(12) << name 
             << left << setw(12) << getCollege()
             << left << setw(12) << balance << endl;
    }
    else if (a == 2) {//查询流水账
        char s1[64];
        sprintf(s1, "%ld.txt", id);
        Re_file_rec(s1, 1);
    }
}
//写入
void binding_card::Wr_file_rec(char s[], string operation)
{
    ofstream out1(s, ios::binary | ios::app | ios::in | ios::out);
    out1 << left << setw(20) << operation
         << left << setw(20) << amount
         << left << setw(20) << get_time()
         << left << setw(20) << balance << endl;
    out1.close();
}
void binding_card::setBinding_card(long _id)
{
    binding_id[num].id = _id;
    binding_id[num].name = name;
    binding_id[num].date = date;
    num++;
}
//打印出已绑定的储蓄卡
void binding_card::show_cards()
{
    for (int i = 0; i < num; i++) {
        binding_id[i].inquire(1);
    }
}
//获取对应id的绑定储蓄卡
deposit_card& binding_card::getdeposit_card(long _id)
{
    for (int i = 0; i < num; i++) {
        if (_id = binding_id[i].id) 
            return binding_id[i];
    }
}
//判断是否存在该储蓄卡
bool binding_card::isd_card(long _id)
{
    for (int i = 0; i < num; i++) {
        if (_id = binding_id[i].id) 
            return true;
    }
    return false;
}
//获取储蓄卡数目
int binding_card::getNum()
{
    return num;
}
//获取储蓄卡id
string binding_card::getId()
{
    string s, s1;
    stringstream ss;
    for (int i = 0; i < num; i++) {
        ss << binding_id[i].id;
        ss >> s1;
        s += s1;
        s += " ";
    }
    return s;
}