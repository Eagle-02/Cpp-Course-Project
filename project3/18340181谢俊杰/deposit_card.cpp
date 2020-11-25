#include "deposit_card.hpp"

deposit_card::deposit_card(): card()
{
    total_quota = 250;
    used_quota = 0;
    spare_quota = 250;
}
//支付
void deposit_card::pay(double num)
{   
    char s1[64];
    if (balance - num < 0) {//优先使用余额，后考虑透支额度
        if (balance + spare_quota - num < 0) {
            cout << "You don't have enough money and overdraft to pay." << endl;
            return ;
        }
        else {
            if (balance == 0) {
                spare_quota -= num;
                used_quota += num;
                amount = -num;
                sprintf(s1, "%ld.txt", id);
                Wr_file_rec(s1, "pay");
            }
            else {
                amount = num;
                num -= balance;
                balance = 0;
                spare_quota -= num;
                used_quota += num;
                sprintf(s1, "%ld.txt", id);
                Wr_file_rec(s1, "pay");
            }
        }
    }
    else {
        balance -= num;
        amount = -num;
        sprintf(s1, "%ld.txt", id);//将该操作记录
        Wr_file_rec(s1, "pay");
    }
    cout << "You have paid it successfully! " <<endl;
}
//查询
void deposit_card::inquire(int a) 
{
    if (a == 1) {//查询信息
        cout << left << setw(20) << "id" 
             << left << setw(20) << "date"
             << left << setw(12) << "name" 
             << left << setw(12) << "balance"
             << left << setw(12) << "used_quota" << endl;
        cout << left << setw(20) << id 
             << left << setw(20) << date
             << left << setw(12) << name 
             << left << setw(12) << balance
             << left << setw(12) << getUsed_q() << endl;
    }
    else if (a == 2) {//查询流水账
        char s1[64];
        sprintf(s1, "%ld.txt", id);
        Re_file_rec(s1, 2);
    }
}
//将流水账写入txt
void deposit_card::Wr_file_rec(char s[], string operation)
{
    ofstream out1(s, ios::binary | ios::app | ios::in | ios::out);
    out1 << left << setw(20) << operation
         << left << setw(20) << amount
         << left << setw(20) << get_time()
         << left << setw(20) << balance
         << left << setw(12) << used_quota
         << left << setw(12) << spare_quota << endl;
    out1.close();
}
//存钱
void deposit_card::deposit(double num)
{
    balance += num;
    amount = num;
    char s1[64];
    sprintf(s1, "%ld.txt", id);
    Wr_file_rec(s1, "deposit");
    cout << "You have deposit successfully! " <<endl;
}
//转帐
bool deposit_card::transfer_out(double num)
{
    char s1[64];
    if (balance - num < 0) {
        if (balance + spare_quota - num < 0) {
            cout << "You don't have enough money to transfer out." << endl;
            return false;
        }
        else {
            if (balance == 0) {
                spare_quota -= num;
                used_quota += num;
                amount = -num;
                sprintf(s1, "%ld.txt", id);
                Wr_file_rec(s1, "transfer_out");
            }
            else {
                amount = num;
                num -= balance;
                balance = 0;
                spare_quota -= num;
                used_quota += num;
                sprintf(s1, "%ld.txt", id);
                Wr_file_rec(s1, "transfer_out");
            }
        }
    }
    else {
        balance -= num;
        amount = -num;
        sprintf(s1, "%ld.txt", id);
        Wr_file_rec(s1, "transfer_out");
    }
    cout << "You have transfered out successfully! " << endl;
    return true;
}
void deposit_card::setUsed_q(double num)
{
    used_quota = num;
}
void deposit_card::setSpare_q(double num)
{
    spare_quota = num;
}
double deposit_card::getUsed_q()
{
    return used_quota;
}
double deposit_card::getSpare_q()
{
    return spare_quota;
}
void deposit_card::repay()
{
    if (balance - used_quota < 0) {
        cout << "You don't have enough money to repay." << endl;
    }
    else {
        amount = -used_quota;
        balance -= used_quota;
        used_quota = 0;
        spare_quota = 250;
        char s1[64];
        sprintf(s1, "%ld.txt", id);
        Wr_file_rec(s1, "repay");
        cout << "You have repayed successfully! " << endl;
    }
}