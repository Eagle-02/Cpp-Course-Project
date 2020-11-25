#ifndef SUB_HPP
#define SUB_HPP

#include "binding_card.hpp"

//存储campus_card的链表
struct campus_list {
    campus_card user;
    campus_list *next;
};
//存储deposit_card的链表
struct deposit_list {
    deposit_card user;
    deposit_list *next;
};
//存储binding_card的链表
struct binding_list {
    binding_card user;
    binding_list *next;
};


//campus_card支付
void _pay1(campus_card &temp);
//campus_card查询信息
void _inquire_inf1(campus_card &temp);
//campus_card查询流水账
void _inquire_rec1(campus_card &temp);
//campus_card转入
void _transfer_in1(campus_card &temp);
//campus_card的子菜单
void submenu1(campus_card &temp);
//校园卡
void in1();

//deposit_card支付
void _pay2(deposit_card &temp);
//deposit_card查询信息
void _inquire_inf2(deposit_card &temp);
//deposit_card查询流水账
void _inquire_rec2(deposit_card &temp);
//deposit_card转入
void _transfer_in2(deposit_card &temp);
//deposit_card转账（出）
void _transfer_out2(deposit_card &temp);
//deposit_card还款
void _repay2(deposit_card &temp);
//deposit_card子菜单
void submenu2(deposit_card &temp);
//储蓄卡
void in2();

//binding_card支付
void _pay3(binding_card &temp);
//binding_card查询信息
void _inquire_inf3(binding_card &temp);
//binding_card查询流水账
void _inquire_rec3(binding_card &temp);
//binding_card转入到校园卡或储蓄卡
void _transfer_in3(binding_card &temp);
//binding_card从校园卡中转出
void _transfer_out3(binding_card &temp);
//binding_card打印出绑定的储蓄卡
void _show(binding_card &temp);
//binding_card还款
void _repay3(binding_card &temp);
//绑定储蓄卡
void _bind(binding_card &temp);
//binding_card子菜单
void submenu3(binding_card &temp);
//binding_card
void in3();


//主菜单
void menu();

#endif