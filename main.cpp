#include <iostream>
#include"buyer.h"
#include"admin.h"
using namespace std;

int main(){
    int n;
    while(1){
        system("cls");
        cout<<"\t    ____________________________________________________________________________________"<<endl;
        cout<<"\t -------------------------------------               --------------------------------------"<<endl;
        cout<<"\t------------------------------------    STARTUP PAGE    ------------------------------------"<<endl;
        cout<<"\t -------------------------------------               --------------------------------------"<<endl;
        cout<<"\t    ************************************************************************************\n\n"<<endl;

        cout<<"\t\t\t1.\tLOGIN as ADMIN"<<endl;
        cout<<"\t\t\t2.\tLOGIN as BUYER"<<endl;
        cout<<"\t\t\t3.\tEXIT"<<endl;
	    cout<<"\n\n\t\t\t\t\t\t\tEnter your choice:\t";
        cin>>n;
        switch(n){
            case 1:{
                admin ob;
                cout<<"\n\t\tEntering ADMIN MENU"<<endl<<endl;
                system("pause");
                ob.Amenu();
                break;
            }
            case 2:{
                buyer ob;
                cout<<"\n\t\tEntering BUYER MENU"<<endl<<endl;
                system("pause");
                ob.BloginMenu();
                break;
            }
            case 3:{
                exit(0);
            }
            default:{
                break;
            }
        }
    }
}
