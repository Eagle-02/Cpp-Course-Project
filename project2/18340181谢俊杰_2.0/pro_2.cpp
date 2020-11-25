#include "pro_2.hpp"

int main()
{
    int flag = 1;
    while (flag) {
        menu();
        cin >> flag;
        switch (flag) {
            case 1: add(); break;
            case 2: subtract(); break;
            case 3: multiply(); break;
            case 4: assign(); break;
            case 5: show(); break;
            case 6: isEqual(); break;
            case 7: derivation(); break;
            case 8: flag = 0; break;
        }
    }
    return 0;
}


Polynomial::Polynomial()//构造函数
{
    head = NULL;
}
Polynomial::Polynomial(const Polynomial &other)//拷贝构造函数
{
    head = NULL;
    term *p = other.head;
    while (p) {
        this->insert(p->coef, p->exp);
        p = p->next;
    }
}
Polynomial::~Polynomial()//析构函数
{
    clear();
}
void Polynomial::insert(double _coef, double _exp)//插入多项式的一个项
{
    term *p = head, *q;
    term *temp = new term(_coef, _exp, NULL);
    if (p == NULL) {
        head = temp;
    }
    else {
        while (p) {
            q = p;
            p = p->next;
        }
        q->next = temp;
    }
}
void Polynomial::display()//打印出多项式
{
    term *p = head;
    while (p) {
        if (p == head) {
            if (p->coef == 1.0) {
                if (p->exp == 1.0)
                    cout << "x";
                else if(p->exp == 0)
                    cout << p->coef;
                else 
                    cout << "x^" << p->exp;
            }
            else if (p->coef == -1.0) {
                if (p->exp == 1.0)
                    cout << "-x";
                else if(p->exp == 0)
                    cout << p->coef;
                else
                    cout << "-x^" << p->exp;
            }
            else if (p->coef == 0)
                cout << 0;
            else {
                if (p->exp == 1.0)
                    cout << p->coef << "x";
                else if(p->exp == 0)
                    cout << p->coef;
                else
                    cout << p->coef << "x^" << p->exp;
            }
        }
        else {
            if (p->coef == 1.0) {
                if (p->exp == 1.0)
                    cout << "+x";
                else if(p->exp == 0)
                    cout  << "+" << p->coef;
                else
                    cout << "+x^" << p->exp;
            }
            else if (p->coef == -1.0) {
                if (p->exp == 1)
                    cout << "-x";
                else if(p->exp == 0)
                    cout << p->coef;
                else
                    cout << "-x^" << p->exp;
            }
            else if (p->coef > 0) {
                if (p->exp == 1) 
                    cout << "+" << p->coef << "x";
                else if(p->exp == 0)
                    cout << "+" << p->coef;
                else 
                    cout << "+" << p->coef << "x^" << p->exp;
            }
            else if (p->coef < 0) {
                if (p->exp == 1.0) 
                    cout << p->coef << "x";
                else if(p->exp == 0)
                    cout << p->coef;
                else 
                    cout << p->coef << "x^" << p->exp;
            }
        }
        p = p->next;
    }
    cout << endl;
}
Polynomial Polynomial::operator=(const Polynomial &other)
{
    if (this->head == other.head) 
        return *this;
    clear();
    term *p = other.head;
    while (p) {
        this->insert(p->coef, p->exp);
        p = p->next;
    }
    return *this;
}
Polynomial Polynomial::operator+(const Polynomial &other)//多项式相加
{
    Polynomial temp;
    term *p = head, *q = other.head, *r; 
    while (p && q) {
        if (p->exp < q->exp) {//确保相加时新的多项式是以指数降序排列
            temp.insert(q->coef, q->exp);
            q = q->next;
        }
        else if (p->exp > q->exp) {
            temp.insert(p->coef, p->exp);
            p = p->next;
        }
        else {
            if (p->coef + q->coef == 0) {//相加后系数为0时不需在新多项式添加该项
                p = p->next;
                q = q->next;
                continue;
            }
            temp.insert(p->coef + q->coef, p->exp);
            p = p->next;
            q = q->next;
        }
    }
    r = q ? q : p;//判断p、q中哪个多项式还有余下未相加的项
    while (r) {//若有余下项，对于余下项添加至temp中
        temp.insert(r->coef, r->exp);
        r = r->next;
    }
    if (temp.head == NULL) {//如果相加后全部系数为0时仍要有0项
        temp.insert(0, 0);
    }
    return temp;
}
Polynomial Polynomial::operator-(const Polynomial &other)//多项式相减
{
    Polynomial temp(other), ans;
    term *p = temp.head;
    while (p) {//即加上other中系数取相反数的多项式
        p->coef *= -1.0;
        p = p->next;
    }
    ans = *this + temp;
    return ans;
}
Polynomial Polynomial::operator*(const Polynomial &other)//多项式相乘
{
    term *p = head, *q, *r;
    Polynomial temp;
    while (p) {
        q = other.head;
        while (q) {
            r = temp.at(p->exp + q->exp);//寻找temp中是否已存在该指数项
            if (temp.head && r)
                r->coef += p->coef * q->coef;//若存在则系数相加
            else 
                temp.insert(p->coef * q->coef, p->exp + q->exp);//否则添加
            q = q->next;
        }
        p = p->next;
    }
    temp.remove_zero();//若系数为0则需清0
    temp.sort();//按指数降序排列
    return temp;
}
bool Polynomial::operator==(const Polynomial &other)//判断两多项式是否相等
{
    if (other.head == head) 
        return true;
    term *temp1 = head, *temp2 = other.head;
    while (temp1 && temp2) {
        if (temp1->exp != temp2->exp || temp1->coef != temp2->coef) 
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if (temp1 != temp2) 
        return false;
    return true;
}
void Polynomial::erase(double _exp)//删除某一项
{
    term *p = head, *q, *r;
    while (p) {
        r = p->next;
        if (p->exp == _exp) {
            if (p == head) {
                delete p;
                head = r;
            }
            else {
                delete p;
                q->next = r;
            }
            return ;
        }
        q = p;
        p = p->next;
    }
}
void Polynomial::remove_zero()//若其中某一项系数变为0时，删除其对应项
{
    term *p = head;
    while (p) {
        if (p->coef == 0) {
            erase(p->exp);
        }
        p = p->next;
    }
    if (head == NULL) 
        head = new term();
}
double Polynomial::assign(double value)//赋值
{
    double sum = 0;
    term *p = head;
    while (p) {
        sum += p->coef * pow(value, p->exp);
        p = p->next; 
    }
    return sum;
}
void Polynomial::sort()//将多项式按指数降序排序
{
    if (head == NULL || head->next == NULL)
        return ;
    term *p = head->next;
    term *pstart = new term, *pend = head, *temp, *pre;
    pstart->next = head;
    while (p != NULL) {
        temp = pstart->next, pre = pstart;
        while (temp != p && p->exp <= temp->exp) {
            temp = temp->next;
            pre = pre->next;
        }
        if (temp == p) 
            pend = p;
        else {
            pend->next = p->next;
            p->next = temp;
            pre->next = p;
        }
        p = pend->next;
    }
    head = pstart->next;
    delete pstart;
}
Polynomial::term* Polynomial::at(double _exp)//寻找是否存在某一指数项
{
    term *p = head;
    while (p) {
        if (p->exp == _exp) 
            return p;
        p = p->next;
    }
    return NULL;
}
void Polynomial::derivation()//求导
{
    term *temp = head, *pre;
    if (temp->exp == 0) {
        head->exp = 0, head->coef = 0;
        head->next = NULL;
    }
    else {
        while (temp) {
            if (temp->exp == 0) {
                pre->next = NULL;
                delete temp;
            }
            else {
                temp->coef *= temp->exp;
                temp->exp -= 1.0;
            }
            pre = temp;
            temp = temp->next;
        }
    }
}
void Polynomial::clear()//清空相应多项式
{
    term *p = head, *q;
    while (p) {
        q = p->next;
        delete p;
        p = q;
    }
    head = NULL;
}

/*********************************************************/

void menu()//打印菜单
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << "~                                                                 ~" << endl
         << "~    Welcome to Polynomial v1.0.0                                 ~" << endl
         << "~    Menu:                                                        ~" << endl
         << "~         1.+                                                     ~" << endl
         << "~         2.-                                                     ~" << endl
         << "~         3.*                                                     ~" << endl
         << "~         4.assign                                                ~" << endl
         << "~         5.show the polynomials saved                            ~" << endl
         << "~         6.judge whether two polynomials are equal               ~" << endl
         << "~         7.derivation                                            ~" << endl
         << "~         8.Exit                                                  ~" << endl
         << "~                                                                 ~" << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << "Please enter what you want to do next:";
}
void in(string s, int num)//输入处理
{
    int n = s.length(), flag = 0;
    int flag3 = 0, flag4 = 0, flag5 = 0, flag7 = 0;
    double num1 = 0, num2 = 0;
    int count = 0;
    flag2 = 0;
    string s1;
    for (int i = 0; i < n; i++) {//判断输入的是否仅是多项式的名字
        if(s[i] == '(') {
            flag = 1;
        }
    }
    if (flag == 1) {//判断输入的格式部分是否正确
        for (int i = 0; i < n; i++) {
            switch (s[i]) {
                case '(': flag3++; break;
                case ')': flag4++; break;
            }
            if (flag4 > flag3) {
                flag5 = 1;
                break;
            }
        }
        if (s[n - 1] != ')')
            flag5 = 1;
        if (flag5 == 1 || flag4 != flag3) {
            cout << "Your input is in a wrong form. Please check it again. " << endl;
            return ;
        }
    }
    if (flag == 1) {//若输入的不是仅为名字
        flag2 = 1;
        int flag6 = 0;
        double sum = 0, coef = 0, exp = 0;
        int count1 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '-' && (s[i - 1] == '(' || s[i - 1] == ',')) //判断系数正负
                flag6 = 1;
            else if (s[i] >= '0' && s[i] <= '9' && flag7 == 0) {//计算并记录整数部分
                num1 *= 10;
                num1 += s[i] - '0';
            }
            else if (s[i] == ',') {//以,为系数边界
                num2 *= pow(10,count1);
                count1 = 0;
                sum = num1 + num2;
                if (flag6) 
                    sum *= -1.0;
                coef = sum;
                count++;
                if (sum == 0) {
                    count--;
                }
                sum = 0;
                flag6 = 0;
                num1 = 0, num2 = 0, flag7 = 0;
            }
            else if (s[i] == '.') {//判断整数部分和小数部分的分界
                if ((!isdigit(s[i - 1]) || !isdigit(s[i + 1])) || flag7 == 1) {
                    flag2 = 0;
                    cout << "Your input is in a wrong form. Please check it again. " << endl;
                    return ;
                }
                flag7 = 1;
            }
            else if (s[i] >= '0' && s[i] <= '9' && flag7 == 1) {//计算并记录小数部分
                num2 *= 10;
                num2 += s[i] -'0';
                count1--;
            }
            else if (s[i] == ')') {//以)为指数边界
                num2 *= pow(10,count1);
                count1 = 0;
                sum = num1 + num2;
                if (flag6)
                    sum *= -1.0;
                exp = sum;
                sum = 0;
                count++;
                if(s[i - 1] == ',')
                    count--;
                if (num == 1)
                    p1.insert(coef, exp);
                else if (num == 2)
                    p2.insert(coef, exp);
                else if (num == 3)
                    p3.insert(coef, exp);
                coef = 0, exp = 0, flag6 = 0;
                num1 = 0, num2 = 0, flag7 = 0;
            }
        }
        if (count % 2 == 1) {//利用count来判断系数指数是否成对，继续判断格式正确与否
            flag2 = 0;
            cout << "Your input is in a wrong form. Please check it again. " << endl;
            return ;
        }
        if (s[0] == '(') {//若输入的多项式不用储存则return，否则进入存储步骤
            return ;
        }
        else {
            flag2 = 1;
            for (int i = 0; i < n; i++) {
                if (s[i] != '=') 
                    s1 += s[i];
                else 
                    break;
            }
            list *p = hpoly;
            while (p) {
                if (p->name == s1) {//需要判断计算器内是否已存储了该名字
                    flag2 = 0;
                    cout << "there is a name of " << s1 << endl
                         << "Please enter another name." << endl;
                    return ;
                }
                else 
                    p = p->next;
            }
            list *temp = new list;
            if (num == 1)
                temp->storage = p1;
            else if (num == 2)
                temp->storage = p2;
            else if (num == 3) 
                temp->storage = p3;
            temp->next = hpoly;
            temp->name = s1;
            hpoly = temp;
        }
    }
    else {//若输入仅为名字，则直接在存储的链表中查找
        list *temp = hpoly;
        while (temp) {
            if (temp->name == s) {
                flag2 = 1;
                if (num == 1) 
                    p1 = temp->storage;
                else if (num == 2)
                    p2 = temp->storage;
                else if (num == 3)
                    p3 = temp->storage;
                break;
            }
            else 
                temp = temp->next;
        }
        if (flag2 == 0) {//若查找失败则反馈并返回
            cout << "There is no such name of polynomial saved here." << endl
                 << "Please check it again." << endl;
        }
    }
}
void save()//询问是否存储相应计算结果
{
    string s;
    int flag = 0;
    cout << "Do you want to save this result?" << endl;
    cout << "1.Yes              2.No" << endl;
    int ans;
    cin >> ans;
    while (ans == 1) {//需要存储多项式时
        flag = 0;
        cout << "please name the polynomial, and the name must be characters: " << endl;
        cin >> s;
        list *p = hpoly;
        while (p) {//检查名字是否已存在
            if (p->name == s) {
                flag = 1;
                cout << "there is a name of " << s << endl
                        << "Please enter another name." << endl;
                break ;
            }
            else 
                p = p->next;
        }
        if (flag == 1) {
            continue ;
        }
        list *temp = new list;
        temp->storage = p3;
        temp->name = s;
        temp->next = hpoly;
        hpoly = temp;
        ans = 0;
    }
}
void add()//多项式相加
{
    p1.clear();
    p2.clear();
    p3.clear();
    string s1, s2;
    cout << "please enter two polynomials: " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cout << "the first one is(Or enter 0 to return to the menu): " << endl;
    cin >> s1;
    if (s1[0] == '0')
        return ;
    in(s1, 1);
    if (flag2 == 0) {
        p1.clear();
        return ;
    }
    p1.sort();
    cout << "the second one is(Or enter 0 to return to the menu): " << endl;
    cin >> s2;
    if (s2[0] == '0') {
        p1.clear();
        p2.clear();
        return ;
    }
    in(s2, 2);
    if (flag2 == 0) {
        p2.clear();
        return ;
    }
    p2.sort();
    // p1.display(), p2.display();
    p3 = p1 + p2;
    cout << "the result is: " << endl;
    p3.display();
    save();
    p1.clear();
    p2.clear();
    p3.clear();
}
void subtract()//多项式相减
{
    p1.clear();
    p2.clear();
    p3.clear();
    string s1, s2;
    cout << "please enter two polynomials: " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cout << "the first one is(Or enter 0 to return to the menu): " << endl;
    cin >> s1;
    if (s1[0] == '0')
        return ;
    in(s1, 1);
    if (flag2 == 0) {
        p1.clear();
        return ;
    }
    p1.sort();
    cout << "the second one is(Or enter 0 to return to the menu): " << endl;
    cin >> s2;
    if (s2[0] == '0')
        return ;
    in(s2, 2);
    if (flag2 == 0) {
        p1.clear();
        p2.clear();
        return ;
    }
    p2.sort();
    // p1.display(), p2.display();
    p3 = p1 - p2;
    cout << "the result is: " << endl;
    p3.display();
    save();
    p1.clear();
    p2.clear();
    p3.clear();
}
void multiply()//多项式相乘
{
    p1.clear();
    p2.clear();
    p3.clear();
    string s1, s2;
    cout << "please enter two polynomials: " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cout << "the first one is(Or enter 0 to return to the menu): " << endl;
    cin >> s1;
    if (s1[0] == '0')
        return ;
    in(s1, 1);
    if (flag2 == 0) {
        p1.clear();
        return ;
    }
    p1.sort();
    cout << "the second one is(Or enter 0 to return to the menu): " << endl;
    cin >> s2;
    if (s2[0] == '0')
        return ;
    in(s2, 2);
    if (flag2 == 0) {
        p1.clear();
        p2.clear();
        return ;
    }
    p2.sort();
    // p1.display(), p2.display();
    p3 = p1 * p2;
    cout << "the result is: " << endl;
    p3.display();
    save();
    p1.clear();
    p2.clear();
    p3.clear();
}
void assign()//赋值求值
{
    p1.clear();
    string s;
    cout << "please enter the polynomial(Or enter 0 to return to the menu): " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cin >> s;
    if (s[0] == '0')
        return ;
    in(s, 1);
    if (flag2 == 0) {
        p1.clear();
        return ;
    }
    p1.sort();
    cout << "please enter the value you want to assign: " << endl;
    double value;
    cin >> value;
    cout << "the result is: ";
    cout << p1.assign(value) << endl;
    p1.clear();
}
void show()//打印出相应已存储的多项式及对应名字
{
    cout << "the polynomials you have saved are as follow: " << endl;
    cout << left << setw(10) << "Name"
         << left << setw(20) << "Polynomial" << endl;
    list *temp = hpoly;
    while (temp) {
        cout << left << setw(10) << temp->name;
        temp->storage.display();
        temp = temp->next;
    }
}
void isEqual()//判断两多项式是否相等
{
    p1.clear();
    p2.clear();
    cout << "plesse enter two polynomials: " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cout << "the first one is(Or enter 0 to return to the menu): " << endl;
    string s1, s2;
    cin >> s1;
    if (s1[0] == '0')
        return ;
    in(s1, 1);
    if (flag2 == 0) {
        p1.clear();
        return ;
    }
    p1.sort();
    cout << "the second one is(Or enter 0 to return to the menu): " << endl;
    cin >> s2;
    if (s2[0] == '0')
        return ;
    in(s2, 2);
    if (flag2 == 0) {
        p1.clear();
        p2.clear();
        return ;
    }
    p2.sort();
    if (p1 == p2) 
        cout << "They are equal." << endl;
    else 
        cout << "They are not equal." <<endl;
    p1.clear();
    p2.clear();
}
void derivation()//对多项式求导
{
    p3.clear();
    string s;
    cout << "please enter the polynomial(Or enter 0 to return to the menu): " << endl;
    cout << "(If you want to enter x^2+2x+1, "
         << "the form of the polynomial must be (1,2)(2,1)(1,0) or name=(1,2)(2,1)(1,0) or name, and the name must be characters.)" << endl;
    cin >> s;
    if (s[0] == '0')
        return ;
    in(s, 3);
    if (flag2 == 0) {
        p3.clear();
        return ;
    }
    p3.sort();
    p3.derivation();
    cout << "the result is: " << endl;
    p3.display();
    save();
    p3.clear();
}