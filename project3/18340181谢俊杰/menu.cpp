#include "menu.hpp"

//各链表的head，用于遍历
campus_list *head1 = NULL;
deposit_list *head2 = NULL;
binding_list *head3 = NULL;

//获取系统时间
string get_time()
{
  char _time[64];
  time_t t = time(0);
  strftime(_time, sizeof(_time), "%Y/%m/%d/%X", localtime(&t));
  string s(_time);
  return _time;
}

//读取信息
void Re_file_inf()
{
    //校园卡
    ifstream in1("campus_card_inf.txt", ios::binary | ios::app | ios::in | ios::out);//防止写入时清空文件
    while (!in1.eof()) {
        string s,s1;
        in1 >> s;
        long _id;
        if (s == "")
            break;
        else {
            _id = atoi(s.c_str());
            campus_list *p = new campus_list;
            p->next = head1;
            p->user.id = _id;
            in1 >> p->user.date >> p->user.name >> s1 >> p->user.balance;
            p->user.setCollege(s1);
            head1 = p;
        }
    }
    in1.close();
    //储蓄卡信息
    ifstream in2("deposit_card_inf.txt", ios::binary | ios::app | ios::in | ios::out);
    while (!in2.eof()) {
        double s2, s3;
        string s1;
        long _id;
        in2 >> s1;
        if (s1 == "")
            break;
        else {
             _id = atoi(s1.c_str());
            deposit_list *p = new deposit_list;
            p->next = head2;
            p->user.id = _id;
            in2 >> p->user.date >> p->user.name >> p->user.balance >> s2;
            p->user.setUsed_q(s2);
            head2 = p;
        }
    }
    in2.close();
    //binding_card
    ifstream in3("binding_card_inf.txt", ios::binary | ios::app | ios::in | ios::out);//防止写入时清空文件
    while (!in3.eof()) {
        string s, s1;
        in3 >> s;
        long _id;
        if (s == "")
            break;
        else {
             _id = atoi(s.c_str());
            binding_list *p = new binding_list;
            p->next = head3;
            p->user.id = _id;
            in3 >> p->user.date >> p->user.name >> s1 >> p->user.balance;
            p->user.setCollege(s1);
            head3 = p;
        }
    }
    in3.close();
}
//写入信息
void Wr_file_inf()
{
    //campus_card
    ofstream out1("campus_card_inf.txt");//写入时清空，防止重复
    campus_list *p = head1;
    while (p != NULL) {
        out1 << left << setw(20) << p->user.id 
             << left << setw(20) << p->user.date
             << left << setw(12) << p->user.name 
             << left << setw(12) << p->user.getCollege()
             << left << setw(12) << p->user.balance << endl;
        p = p->next;
    }
    out1.close();
    //deposit_card
    ofstream out2("deposit_card_inf.txt");//写入时清空，防止重复
    deposit_list *q = head2;
    while (q != NULL) {
        out2 << left << setw(20) << q->user.id 
             << left << setw(20) << q->user.date
             << left << setw(12) << q->user.name 
             << left << setw(12) << q->user.balance
             << left << setw(12) << q->user.getUsed_q() << endl;
        q = q->next;
    }
    out2.close();
    //bidning_card
    ofstream out3("binding_card_inf.txt");//写入时清空，防止重复
    binding_list *r = head3;
    while (r != NULL) {
        out3 << left << setw(20) << r->user.id 
             << left << setw(20) << r->user.date
             << left << setw(12) << r->user.name 
             << left << setw(12) << r->user.getCollege()
             << left << setw(12) << r->user.balance << endl;
        r = r->next;
    }
    out3.close();
}
//读取流水账
void Re_file_rec(char s[], int a)
{
    cout << left << setw(20) << "operation"
         << left << setw(20) << "amount"
         << left << setw(20) << "time" 
         << left << setw(20) << "balance"; 
    if (a == 1) {//campus_crad
        cout << endl;
        ifstream in1(s, ios::binary | ios::app | ios::in | ios::out);
        while (!in1.eof()) {
            string s1;
            in1 >> s1;
            if (s1 == "")
                break;
            for (int i = 0; i < 3; i++) {
                cout << left << setw(20) << s1;
                in1 >> s1;
            }
            cout << left << setw(20) << s1 << endl;
        }
        cout << endl;
        in1.close();
    }
    else if (a == 2) {//deposit_card
        cout << left << setw(12) << "used_quota"
             << left << setw(12) << "spare_quota" << endl; 
        ifstream in2(s, ios::binary | ios::app | ios::in | ios::out);
        while (!in2.eof()) {
            string s1;
            in2 >> s1;
            if (s1 == "")
                break;
            for (int i = 0; i < 5; i++) {
                cout << left << setw(20) << s1;
                in2 >> s1;
            }
            cout << left << setw(20) << s1 << endl;
        }
        cout << endl;
        in2.close();
    }
}
//清空链表释放内存
void clear()
{
    campus_list *p = head1, *q;
    while (p) {
        q = p;
        p = p->next;
        delete q;
    }
    deposit_list *r = head2, *s;
    while (r) {
        s = r;
        r = r->next;
        delete s;
    }
    binding_list *t = head3, *u;
    while (t) {
        u = t;
        t = t->next;
        delete u;
    }
}


//campus_card支付
void _pay1(campus_card &temp)
{
    cout << "Please enter the amount you will pay: " << endl;
    double amount;
    cin >> amount;
    temp.pay(amount);
}
//campus_card查询信息
void _inquire_inf1(campus_card &temp)
{
    temp.inquire(1);
}
//campus_card查询流水账
void _inquire_rec1(campus_card &temp)
{
    temp.inquire(2);
}
//campus_card转入
void _transfer_in1(campus_card &temp)
{
        cout << "Please enter the id of deposit_card you will transfer from: " << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        deposit_list *p = head2;
        deposit_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            if (temp_1.transfer_out(amount)) {
                p->user = temp_1;
                temp.transfer_in(amount);
            }
        }
        else{
            cout << "There is no such id. Please check it again." << endl;
        }
}
//campus_card的子菜单
void submenu1(campus_card &temp)
{
    int flag = 1;
    while (flag) {
        //打印campus_card子菜单
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "~                                                     ~" << endl
             << "~    SubMenu:                                         ~" << endl
             << "~         1.pay                                       ~" << endl
             << "~         2.inquire the information of your card      ~" << endl
             << "~         3.inquire the transactions                  ~" << endl
             << "~         4.deposit                                   ~" << endl
             << "~         5.return to the main menu                   ~" << endl
             << "~                                                     ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Please enter what you want to do next:" << endl;
        cin >> flag;//输入要进行的功能
        switch (flag) {
            case 1: _pay1(temp); break;
            case 2: _inquire_inf1(temp); break;
            case 3: _inquire_rec1(temp); break;
            case 4: _transfer_in1(temp);break;
            case 5: flag = 0; break;
        }
    }
    
}
void in1()//校园卡
{
    cout << "Please enter the id of your card or add your card "
         << "into this system: " << endl;
    long _id;
    cin >> _id;
    campus_list *p = head1;
    campus_card temp;
    int flag = 0;
    while (p != NULL) {
        if (_id == p->user.id) {
            flag = 1;
            temp = p->user;
            break;
        }
        else {
            p = p->next;
        }
    }
    if (flag == 0) {
        cout << "There is no such id in this system. "
             << "To add your id in it, please enter your name "
             << "and your college: " << endl;
        string s1, s2;
        cout << "name: " << endl;
        cin >> s1;
        cout << "college: " << endl;
        cin >> s2;
        campus_list *q = new campus_list;
        q->user.id = _id;
        q->user.name = s1;
        q->user.setCollege(s2);
        q->user.date = get_time();
        q->next = head1;
        head1 = q;
        temp = q->user;
        submenu1(temp);
        q->user = temp;
    }
    else if (flag == 1) {
        submenu1(temp);
        p->user = temp;
    }
}


//deposit_card支付
void _pay2(deposit_card &temp)
{
    cout << "Please enter the amount you will pay: " << endl;
    double amount;
    cin >> amount;
    temp.pay(amount);
}
//deposit_card查询信息
void _inquire_inf2(deposit_card &temp)
{
    temp.inquire(1);
}
//deposit_card查询流水账
void _inquire_rec2(deposit_card &temp)
{
    temp.inquire(2);
}
//deposit_card转入
void _transfer_in2(deposit_card &temp)
{
    cout << "Transfer in by 1.cash      2.deposit_card " << endl;
    int flag;
    cin >> flag;
    if (flag == 2) {
        cout << "Please enter the id of deposit_card you will transfer from: " << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        deposit_list *p = head2;
        deposit_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            if (temp_1.transfer_out(amount)) {
                p->user = temp_1;
                temp.deposit(amount);
            }
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
    else if (flag == 1) {
        cout << "Please enter the amount you will transfer in: " << endl;
        double amount;
        cin >> amount;
        temp.deposit(amount);
    }
}
//deposit_card转账（出）
void _transfer_out2(deposit_card &temp)
{
    cout << "transfer out to 1.campus_card      2.deposit_card" << endl;
    int flag;
    cin >> flag;
    if (flag == 1) {
        cout << "Please enter the id of the campus_card:" << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        campus_list *p = head1;
        campus_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            temp_1.transfer_in(amount);
            p->user = temp_1;
            temp.transfer_out(amount);
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
    else if (flag == 2) {
        cout << "Please enter the id of the deposit_card:" << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        deposit_list *p = head2;
        deposit_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            temp_1.deposit(amount);
            p->user = temp_1;
            temp.transfer_out(amount);
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
}
//deposit_card还款
void _repay2(deposit_card &temp)
{
    temp.repay();
}
//deposit_card子菜单
void submenu2(deposit_card &temp)
{
    int flag = 1;
    while (flag) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "~                                                     ~" << endl
             << "~    SubMenu:                                         ~" << endl
             << "~         1.pay                                       ~" << endl
             << "~         2.inquire the information of your card      ~" << endl
             << "~         3.inquire the transactions                  ~" << endl
             << "~         4.deposit                                   ~" << endl
             << "~         5.transfer out                              ~" << endl
             << "~         6.repay                                     ~" << endl
             << "~         7.return to the main menu                   ~" << endl
             << "~                                                     ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Please enter what you want to do next:" << endl;
        cin >> flag;//输入要进行的功能
        switch (flag) {
            case 1: _pay2(temp); break;
            case 2: _inquire_inf2(temp); break;
            case 3: _inquire_rec2(temp); break;
            case 4: _transfer_in2(temp);break;
            case 5: _transfer_out2(temp);break;
            case 6: _repay2(temp);break;
            case 7: flag = 0; break;
        }
    }
}
void in2()//储蓄卡
{
    cout << "Please enter the id of your card or add your card "
         << "into this system: " << endl;
    long _id;
    cin >> _id;
    deposit_list *p = head2;
    deposit_card temp;
    int flag = 0;
    while (p != NULL) {
        if (_id == p->user.id) {
            flag = 1;
            temp = p->user;
            break;
        }
        else {
            p = p->next;
        }
    }
    if (flag == 0) {
        cout << "There is no such id in this system. "
             << "To add your id in it, please enter your name " << endl;
        string s1;
        cout << "name: " << endl;
        cin >> s1;
        deposit_list *q = new deposit_list;
        q->user.id = _id;
        q->user.name = s1;
        q->user.date = get_time();
        q->next = head2;
        head2 = q;
        temp = q->user;
        submenu2(temp);
        q->user = temp;
    }
    else if (flag == 1) {
        submenu2(temp);
        p->user = temp;
    }
}


//binding_card支付
void _pay3(binding_card &temp)
{
    cout << "Please enter the amount you will pay: " << endl;
    double amount;
    cin >> amount;
    temp.pay(amount);
}
//binding_card查询信息
void _inquire_inf3(binding_card &temp)
{
    temp.inquire(1);
}
//binding_card查询流水账
void _inquire_rec3(binding_card &temp)
{
    temp.inquire(2);
}
//binding_card转入到校园卡或储蓄卡
void _transfer_in3(binding_card &temp)
{
    cout << "Transfer in by 1.cash   2. other deposit_card" << endl;
    int flag;
    cin >> flag;
    if (flag == 2) {
        cout << "Please enter the id of deposit_card you will transfer from: " << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        deposit_list *p = head2;
        deposit_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            cout << "Transfer to 1.my campus_card       2.my deposit_card" << endl;
            int a;
            cin >> a;
            if (a == 1) {
                if (temp_1.transfer_out(amount)) {
                    p->user = temp_1;
                    temp.deposit(amount);
                }
            }
            else if (a == 2) {
                cout << "Please enter the id of deposit_card you will transfer from: " << endl;
                long _id;
                cin >> _id;
                if (temp.isd_card(_id)) {//存在这个id
                    if (temp_1.transfer_out(amount)) {
                        p->user = temp_1;
                        temp.getdeposit_card(_id).deposit(amount);
                    }
                }
                else //不存在时
                    cout << "There is no such id. Please check it again." << endl;
            }
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
    else if (flag == 1) {
        cout << "Please enter the amount you will transfer in: " << endl;
        double amount;
        cin >> amount;
        cout << "Transfer to 1.my campus_card       2.my deposit_card" << endl;
        int a;
        cin >> a;
        if (a == 1) {
            temp.deposit(amount);
        }
        else if (a == 2) {
            cout << "Please enter the id of deposit_card you will transfer from: " << endl;
            long _id;
            cin >> _id;
            if (temp.isd_card(_id)) {//存在这个id
                temp.getdeposit_card(_id).deposit(amount);
            }
            else //不存在时
                cout << "There is no such id. Please check it again." << endl;
        }
    }
}
//binding_card从校园卡中转出
void _transfer_out3(binding_card &temp)
{
    cout << "transfer out to 1.campus_card      2.deposit_card" << endl;
    int flag;
    cin >> flag;
    if (flag == 1) {
        cout << "Please enter the id of the campus_card:" << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        campus_list *p = head1;
        campus_card temp_1;
        while (p != NULL) {
            if (_id == p->user.id) {
                flag1 = 1;
                temp_1 = p->user;
                break;
            }
            else {
                p = p->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            temp_1.transfer_in(amount);
            p->user = temp_1;
            temp.transfer_out(amount);
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
    else if (flag == 2) {
        cout << "Please enter the id of the deposit_card:" << endl;
        long _id;
        cin >> _id;
        int flag1 = 0;
        deposit_list *q = head2;
        deposit_card temp_1;
        while (q != NULL) {
            if (_id == q->user.id) {
                flag1 = 1;
                temp_1 = q->user;
                break;
            }
            else {
                q = q->next;
            }
        }
        if (flag1 == 1) {
            cout << "Please enter the amount you will transfer in: " << endl;
            double amount;
            cin >> amount;
            temp_1.deposit(amount);
            q->user = temp_1;
            temp.transfer_out(amount);
        }
        else {
            cout << "There is no such id. Please check it again." << endl;
        }
    }
}
//binding_card打印出绑定的储蓄卡
void _show(binding_card &temp)
{
    temp.show_cards();
}
//binding_card还款
void _repay3(binding_card &temp)
{
    cout << "Please enter the id of deposit_card you want to repay: " << endl;
    long _id;
    cin >> _id;
    if (temp.isd_card(_id)) 
        temp.getdeposit_card(_id).repay();
    else 
        cout << "There is no such id. Please check it again." << endl;
}
//绑定储蓄卡
void _bind(binding_card &temp)
{
    cout << "Please enter the id of deposit_card you want to bind: " << endl;
    long _id;
    cin >> _id;
    if (temp.isd_card(_id)) 
        cout << "The id you've bound already. " << endl;
    else 
        temp.setBinding_card(_id);
}
//binding_card子菜单
void submenu3(binding_card &temp)
{
    int flag = 1;
    while (flag) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "~                                                     ~" << endl
             << "~    SubMenu:                                         ~" << endl
             << "~         1.pay                                       ~" << endl
             << "~         2.inquire the information of your card      ~" << endl  //打印菜单
             << "~         3.inquire the transactions                  ~" << endl
             << "~         4.deposit                                   ~" << endl
             << "~         5.transfer out                              ~" << endl
             << "~         6.show binding deposit cards                ~" << endl
             << "~         7.repay                                     ~" << endl
             << "~         8.bind deposit_card                         ~" << endl
             << "~         9.return to the main menu                   ~" << endl
             << "~                                                     ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Please enter what you want to do next:" << endl;
        cin >> flag;//输入要进行的功能
        switch (flag) {
            case 1: _pay3(temp); break;
            case 2: _inquire_inf3(temp); break;
            case 3: _inquire_rec3(temp); break;
            case 4: _transfer_in3(temp); break;
            case 5: _transfer_out3(temp); break;
            case 6: _show(temp); break;
            case 7: _repay3(temp); break;
            case 8: _bind(temp); break;
            case 9: flag = 0; break;
        }
    }
}
void in3()//binding_card
{
    cout << "Please enter the id of your card or add your card "
         << "into this system: " << endl;
    long _id;
    cin >> _id;
    binding_list *p = head3;
    binding_card temp;
    int flag = 0;
    while (p != NULL) {
        if (_id == p->user.id) {
            flag = 1;
            temp = p->user;
            break;
        }
        else {
            p = p->next;
        }
    }
    if (flag == 0) {
        cout << "There is no such id in this system. "
             << "To add your id in it, please enter your name "
             << "and your college: " << endl;
        string s1, s2;
        cout << "name: " << endl;
        cin >> s1;
        cout << "college: " << endl;
        cin >> s2;
        binding_list *q = new binding_list;
        q->user.id = _id;
        q->user.name = s1;
        q->user.setCollege(s2);
        q->user.date = get_time();
        cout << "Enter the deposit_card to bind your card(or enter 0 to stop binding): " << endl;
        cin >> _id;
        while (_id) {
            q->user.setBinding_card(_id);
            cout << "Enter the deposit_card to bind your card(or enter 0 to stop binding): " << endl;
            cin >> _id;
        }
        q->next = head3;
        head3 = q;
        temp = q->user;
        submenu3(temp);
        q->user = temp;
    }
    else if (flag == 1) {
        submenu3(temp);
        p->user = temp;
    }
}

//主菜单
void menu()
{
    int flag = 1;
    while (flag) {
        //打印主菜单
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "~                                          ~" << endl
             << "~    Welcome to CARD v1.0.0                ~" << endl
             << "~    Menu:                                 ~" << endl
             << "~         1.campus_card                    ~" << endl
             << "~         2.deposit_card                   ~" << endl 
             << "~         3.binding_card                   ~" << endl
             << "~         4.Exit                           ~" << endl
             << "~                                          ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Please enter what you want to do next:" << endl;
        cin >> flag;//输入要进行的功能
        switch (flag) {
            //选择各序号进入不同功能
            case 1: in1(); break;
            case 2: in2(); break;
            case 3: in3(); break;
            case 4: Wr_file_inf(); clear(); flag = 0; break;//退出前将数据写入txt文件中存储并清空链表释放内存
        }
    }
}