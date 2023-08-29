#ifndef BUYER_H
#define BUYER_H

#include<iostream>
#include<string>
#include<fstream>
#include<limits>
#include<map>
using namespace std;

extern bool loggedIn;

class buyer{
    public:
        void BloginMenu();
        void login();
        void registration();
        void forgot();
        void changepassw();
        void showacc();
        void logout();
        void deleteacc();
        void addtocart(string, int);
        void viewitems();
        void viewcart();
        void buycart();
        void showbill();
        void emptycart();
        string getprodname(string);

    protected:

    private:
        string username;
        string password;
        int cartValue = 0;
        map<string, pair<int, int>> cart;
};

#endif // BUYER_H
