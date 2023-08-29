#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<string>
#include<fstream>
#include<limits>
using namespace std;

extern bool adminloggedIn;

class admin{
    public:
        void Amenu();
        void login();
        void logout();
        void showstocks();
        void updatestocks();
        void addstocks();
        void changestocks();
        void deletestocks();
        void showacc();
        void registerstock();
        string getprodname(string);
        bool stockregistered(string prodId);


    protected:

    private:
        string password = "admin@2024";
};

#endif // ADMIN_H
