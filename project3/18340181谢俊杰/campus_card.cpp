#include "campus_card.hpp"

//构造函数
campus_card::campus_card(): card()
{}
//campus_card支付函数
void campus_card::pay(double num)
{
    if (balance - num < 0) {
        cout << "You don't have enough money to pay." << endl;
        return ;
    }
    balance -= num;
    amount = -num;
    char s1[64];
    sprintf(s1, "%ld.txt", id);
    Wr_file_rec(s1, "pay");
    cout << "You have paid it successfully! " <<endl;
}
//查询信息或流水帐
void campus_card::inquire(int a)
{
    if (a == 1) {//查询校园卡的信息
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
//将流水账写入以学号为名的txt文件中
void campus_card::Wr_file_rec(char s[], string operation)
{
    ofstream out1(s, ios::binary | ios::app | ios::in | ios::out);
    out1 << left << setw(20) << operation
         << left << setw(20) << amount
         << left << setw(20) << get_time()
         << left << setw(20) << balance << endl;
    out1.close();
}
//转入函数
void campus_card::transfer_in(double num)
{
    balance += num;
    amount = num;
    char s1[64];
    sprintf(s1, "%ld.txt", id);
    Wr_file_rec(s1, "transfer_in");
    cout << "You have transfer in your card successfully! " <<endl;
}
//set college
void campus_card::setCollege(string college)
{
    this->college = college;
}
//get college
string campus_card::getCollege()
{
    return college;
}