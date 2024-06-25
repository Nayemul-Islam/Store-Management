////// Welcome To My Own e-commerce
#include <bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
using namespace std;
#define op()                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define ll long long
const char* host ="localhost";
const char* user = "root";
const char* dbpass = "";
const char* db = "coustomer";
unsigned int port = 3307 ;
const char* unix = NULL;
unsigned long client = 0;
MYSQL* con;
MYSQL* ncon;
ll payable_tk;
int operation_mark;
map<string,vector<pair<string, pair<int, int>>>> product_list;
void Set()
{
    con = ncon;
}
void hypen(ll n)
{
    for(int i = 1 ; i <= 3 ; i++)
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    if(n == 1)
        cout << "------------------------------------------------  Welcome to Bazar  ---------------------------------------------------" << endl;
}
class Product /// Mother Class
{
public:
    string Product_Name, Product_type;
    ll Product_Price,product_quantity;
};

class stock_reading : Product /// Product Stock Reading Class
{
public:
    stock_reading()
    {
        stringstream aa;
        aa << "Select * From Product";
        string qu = aa.str();
        const char* q1 = qu.c_str();
        Set();
        int qstate = mysql_query(con,q1);
        MYSQL_ROW row;
        MYSQL_RES* res;
        res = mysql_store_result(con);
        while(row = mysql_fetch_row(res))
        {
            string a,b;
            a =  row[2];
            b =  row[1];
            ll x,y;
            x = atol(row[3]);
            y = atol(row[4]);
            product_list[a].push_back({b,{x,y}});
        }
    }
};
class update_stock : Product /// Product Updating Class for Admin
{
public:
    void updating ()
    {
        cout << endl << "Product type?" << endl;
        cin >> Product_type;
        cout << endl << "Product name?" << endl;
        cin.ignore();
        getline(cin, Product_Name);
        cout << endl << "Product price?" << endl ;
        cin >> Product_Price;
        cout << endl << "Product quantity?" << endl;
        cin >> product_quantity;
        int qstate = 0;
        stringstream ss;
        ss << "Insert into Product (product_type,product_name, product_price,product_quantity) values ('"+Product_type+"', '"+Product_Name+"','"<<Product_Price << " ' , '"<<product_quantity<<"')";
        string query = ss.str();
        const char* q = query.c_str();
        Set();
        qstate = mysql_query(con,q);
        if(!qstate)
        {
            cout << "Product Update Successfully." << endl;
        }
        else
        {
            cout << "Something Wrong!!! Try again!" << endl;
        }

    }
};
//////////  Book Class /////////

class Book : Product
{
private:
    int book_serial[1000], j = 1;

public:
    Book()
    {

    }
    void buying()
    {
        int i;
        cin >> i;
        payable_tk += book_serial[i];
    }
};

//////////  Mobile Class /////////

class Mobile : Product
{
private:
    int mobile_serial[1000], j = 1;

public:
    Mobile()
    {

        for (auto i : product_list["Mobile"])
        {
            if (i.second.first == 0)
                continue;
            cout << "Mobile Name : " << i.first << endl;
            cout << "Price : " << i.second.second << endl<<endl;
            cout << "To buy this Mobile , press " << j << " later." << endl << endl;
            mobile_serial[j] = i.second.second;
            j++;
        }

    }
    void buying()
    {
        int i;
        cin >> i;
        payable_tk += mobile_serial[i];

    }
};

//////////  PC Class /////////

class PC : Product
{
private:
    int pc_serial[1000], j = 1;

public:
    PC()
    {


        for (auto i : product_list)
        {

        }
    }
    void buying()
    {
        int i;
        cin >> i;
        payable_tk += pc_serial[i];
    }
};

class Admin
{
protected:
    string password,user_mail; ///Real Password,User Name;
    string pass,mail,first_name, last_name,address ;   ///For Terminal
public:
    Admin()
    {
        hypen(2);
        cout << "------------------------------------------------  Admin Login Panel  ---------------------------------------------------" << endl;
        hypen(2);
        cout << endl;
        log_in();
    }
    void log_in ()
    {
        cout << "Enter Your Email Id : " << endl;
        cin >> mail;
        cout << "Enter Password : " << endl;
        cin >> pass;
        cout << endl;
        log_in_cheack ();
    }
    void log_in_cheack ()
    {

        stringstream aa,bb;
        aa << "Select * From admin where email_id = '"+mail+"' AND pass = '"+pass+"' ";
        string qu = aa.str();
        const char* q1 = qu.c_str();
        Set();
        int qstate = mysql_query(con,q1);
        MYSQL_ROW row;
        MYSQL_RES* res;
        res = mysql_store_result(con);
        bool flag = false;
        while(row = mysql_fetch_row(res))
        {
            flag = true;
        }
        if(flag)
        {
            admin_menu ();
        }
        else
        {
            cout << "Ooops !! Invalid Email Id or Password !! Try again." << endl << endl;
            log_in();
        }

    }

    void add_new_admin()
    {
        cout << endl << "Enter Admin First Name : " << endl;
        cin >> first_name ;
        cout << endl << "Enter Admin Last Name : " << endl;
        cin >> last_name;
        cout << endl << "Enter Admin Home Address: " << endl;
        cin.ignore();
        getline(cin, address);
        cout << endl << "Enter Admin Mail Account : " << endl;
        cin >> mail;
        cout << endl  << "Set a Password : " << endl;
        cin >> pass;
        cout << endl;
        int qstate = 0;
        stringstream ss;
        ss << "Insert into admin (first_name,last_name, email_id ,pass,address) values ('"+first_name+"', '"+last_name+"','"+mail+"','"+pass+"','"+address+"')";
        string query = ss.str();
        const char* q = query.c_str();
        Set();
        qstate = mysql_query(con,q);
        if(!qstate)
        {
            cout << "                   Registered Successfully." << endl << endl;
            admin_menu();
        }
        else
        {
            stringstream aa;
            aa << "Select * From admin where email_id = '"+mail+"'";
            string qu = aa.str();
            const char* q1 = qu.c_str();
            Set();
            int qstate = mysql_query(con,q1);
            MYSQL_ROW row;
            MYSQL_RES* res;
            res = mysql_store_result(con);
            bool flag = false;
            while(row = mysql_fetch_row(res))
            {
                flag = true;
            }
            if(flag)
            {
                cout << endl << "This email already used. Try again" << endl;
            }
            else
            {
                cout << endl << "The minimum length of a password should be 4.Try Again" << endl;
            }
            cout << endl << "                       Try Again Press 1." << endl;
            cout  << "                      Admin Menu Press 2." << endl;
            cout << "                       To exit Application Press 0" << endl;
            cin >> operation_mark ;
            if(operation_mark == 1)
            {
                add_new_admin();
            }
            else if(operation_mark == 2)
            {
                admin_menu();
            }

        }
    }

    void admin_menu ()
    {
        hypen(2);
        cout << "------------------------------------------------ Welcome Admin Panel ---------------------------------------------------" << endl;
        hypen(2);
operation3:
        cout << "                                          Product Add Press 1." << endl;
        ///cout << "To See Profit Press 2 " << endl; Coming soon
        ///cout << "To See Order Details Press 3" << endl; Coming soon
        cout << "                                          Add New Admin Press 4." << endl;
        cout << "                                          Changing Password Press 5." << endl;
        cout  << "                                          To exit Application Press 0" << endl << endl;
        cin >> operation_mark ;
        if(operation_mark == 1)
        {
            while(operation_mark)
            {
                update_stock New_products;
                New_products.updating();
                cout << "                       Again Add Product Press 1" << endl;
                cout << "                       Go Back Press 0" << endl;
                cin >> operation_mark;
            }
            if(!operation_mark)
            {
                goto operation3;
            }
        }
        else if (operation_mark == 5)
        {
            cout << "Enter New Password" << endl;
            cin >> pass;
            cout << "Password Change Successfully" << endl << endl;
        }
        else if (operation_mark == 4)
        {
            cout << "Note Only First Admin can add New Admin" << endl << endl;
            cout << "Enter Your Email Id : " << endl;
            cin >> mail;
            cout << "Enter Password : " << endl;
            cin >> pass;
            cout << endl;
            stringstream aa,bb;
            aa << "Select * From admin where email_id = '"+mail+"' AND pass = '"+pass+"' AND admin_id = '1' ";
            string qu = aa.str();
            const char* q1 = qu.c_str();
            Set();
            int qstate = mysql_query(con,q1);
            MYSQL_ROW row;
            MYSQL_RES* res;
            res = mysql_store_result(con);
            bool flag = false;
            while(row = mysql_fetch_row(res))
            {
                flag = true;
            }
            if(flag)
            {
                add_new_admin ();
            }
            else
            {
                cout << "Ooops !! Invalid Email Id or Password !! Try again." << endl << endl;
                admin_menu();
            }

        }
        else if(operation_mark != 0)
        {
            goto operation3;
        }

    }

};

class Coustomer /// Coustomer Class
{
protected:
    string password,user_mail; ///Real Password,User Name;
    string pass,mail,first_name, last_name,address ;   ///For Terminal
public:
    void product_buying();
    void menu_table();
    Coustomer ()
    {
        cout << endl << "Sign in Press 1." << endl;
        cout << "Sign up Press 2." << endl;
        cin >> operation_mark ;
        if(operation_mark == 1)
        {
            log_in();
        }
        else
        {
            add_coustomer();
        }
    }
    void add_coustomer ()
    {
        cout << endl << "Enter Your First Name : " << endl;
        cin >> first_name ;
        cout << endl << "Enter Your Last Name : " << endl;
        cin >> last_name;
        cout << endl << "Enter Your Home Address: " << endl;
        cin.ignore();
        getline(cin, address);
        cout << endl << "Enter Your Mail Account : " << endl;
        cin >> mail;
        cout << endl  << "Set a Password : " << endl;
        cin >> pass;
        cout << endl;
        int qstate = 0;
        stringstream ss;
        ss << "Insert into coustomer (coust_first_name, coust_last_name, email_id ,pass,address) values ('"+first_name+"', '"+last_name+"','"+mail+"','"+pass+"','"+address+"')";
        string query = ss.str();
        const char* q = query.c_str();
        Set();
        qstate = mysql_query(con,q);
        if(!qstate)
        {
            cout << "Registered Successfully." << endl;
            log_in();
        }
        else
        {
            stringstream aa;
            aa << "Select * From coustomer where email_id = '"+mail+"'";
            string qu = aa.str();
            const char* q1 = qu.c_str();
            Set();
            int qstate = mysql_query(con,q1);
            MYSQL_ROW row;
            MYSQL_RES* res;
            res = mysql_store_result(con);
            bool flag = false;
            while(row = mysql_fetch_row(res))
            {
                flag = true;
            }
            if(flag)
            {
                cout << endl << "This email already used. Try again" << endl;
            }
            else
            {
                cout << endl << "The minimum length of a password should be 4.Try Again" << endl;
            }
            cout << endl << "Again Sign up Press 1." << endl;
            cout  << "Sign in Press 2." << endl;
            cout << "To exit Application Press 0" << endl;
            cin >> operation_mark ;
            if(operation_mark == 1)
            {
                add_coustomer();
            }
            else if(operation_mark == 2)
            {
                log_in();
            }
        }

    }
    void log_in ()
    {
        cout << "Enter Your Email Id : " << endl;
        cin >> mail;
        cout << "Enter Password : " << endl;
        cin >> pass;
        cout << endl;
        log_in_cheack ();
    }
    void log_in_cheack ()
    {

        stringstream aa,bb;
        aa << "Select * From coustomer where email_id = '"+mail+"' AND pass = '"+pass+"' ";
        string qu = aa.str();
        const char* q1 = qu.c_str();
        Set();
        int qstate = mysql_query(con,q1);
        MYSQL_ROW row;
        MYSQL_RES* res;
        res = mysql_store_result(con);
        bool flag = false;
        while(row = mysql_fetch_row(res))
        {
            flag = true;
        }
        if(flag)
        {
            cout << "Successfully Logged in your account." << endl << endl;
            product_buying();
        }
        else
        {
            cout << "Ooops!! Invalid Email Id or Password !! Try again." << endl;
            log_in();
        }
    }
};

void Coustomer ::menu_table()
{
    cout << "If you want to buy a Book press 1." << endl;
    cout << "If you want to buy a Mobile press 2." << endl;
    cout << "If you want to buy a PC press 3. " << endl;

    cin >> operation_mark;
    if (operation_mark == 1)
    {
        Book new_item;
        new_item.buying();
    }
    if (operation_mark == 2)
    {
        Mobile new_item;
        new_item.buying();
    }
    if (operation_mark == 3)
    {
        PC new_item;
        new_item.buying();
    }
}
void Coustomer::product_buying ()
{
    stock_reading read;
operation:
    if (payable_tk)
        cout << "Your Total bill is : " << payable_tk << endl << endl
             << "Do you by another thing? if you buy anything press 1 otherwise press 0"
             << endl;
    else
        cout << "Do you want to buy any thing? if you buy anything press 1 otherwise press 0"
             << endl;

    cin >> operation_mark;
    if (!operation_mark)
    {
        if (payable_tk)
        {
            cout << "Your Total Bill is : " << payable_tk << endl;
            cout << "Thank You Sir. Have a good Day" << endl;
        }
        return;
    }
    menu_table();
    goto operation;
}
void mysqlconnect()
{
    con = mysql_init(0);
    con = mysql_real_connect(con,host,user,dbpass,db,port,unix,client);
    ncon = con;

}
int main()
{
    op();
    mysqlconnect();
    if(ncon == 0)
    {
        cout<<"Sorry Application cannot be run. try again later."<<endl;
        return 0;
    }
    hypen(1);
    hypen(2);
    cout << endl << "1.                          Shop Admin.                          " << endl;
    cout << "2.                          Customer.                          " << endl;
    cout << "3.                          Exit.                          "<< endl << endl << endl << endl;
    cin >> operation_mark ;
operation:
    if(operation_mark == 1)
    {
        Admin admin;
        cout << "Thanks Admin !!" << endl;
        return 0;
    }
    else if (operation_mark == 2)
    {
        Coustomer coustomer;
    }
    else if(operation_mark != 3)
    {
         cout << "                           Oppss!! Wrong Option,Please Try again.                          " << endl;
        goto operation;
    }
    else
    {
        cout <<  "                           Thanks.                           " << endl;
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    return 0;

}
