#include "admin.h"
using namespace std;

bool adminloggedIn = 0;

void admin::Amenu(){
    do{
        system("cls");
        cout<<"\t    __________________________________________________________________________________"<<endl;
        cout<<"\t -------------------------------------              -------------------------------------"<<endl;
        cout<<"\t------------------------------------    LOGIN MENU    ------------------------------------"<<endl;
        cout<<"\t -------------------------------------              -------------------------------------"<<endl;
        cout<<"\t    **********************************************************************************\n\n"<<endl;
        int a;
        cout<<"\t\t\tPRESS 1 to LOGIN"<<endl;
        cout<<"\t\t\tPRESS 2 to LOGOUT"<<endl;
        cout<<"\t\t\tPRESS 3 to show stocks"<<endl;
        cout<<"\t\t\tPRESS 4 to update stocks"<<endl;
        cout<<"\t\t\tPRESS 5 to register stock"<<endl;
        cout<<"\t\t\tPRESS 6 to show account details"<<endl;
        cout<<"\t\t\tPRESS 7 to EXIT to previous menu"<<endl;
	    cout<<"\n\n\t\t\t\t\t\t\tEnter your choice:\t";
	    cin>>a;
        switch(a){
            case 1:{
                login();
                break;
            }
            case 2:{
                logout();
                break;
            }
            case 3:{
                showstocks();
                break;
            }
            case 4:{
                updatestocks();
                break;
            }
            case 5:{
                registerstock();
                break;
            }
            case 6:{
                showacc();
                break;
            }
            case 7:{
                cout<<"\n\t\t\t\t\tSee you again!"<<endl;   //**************changes required to return to prev menu
                adminloggedIn=0;
                return;
                break;
            }
            default:{
                cout<<"\n\t\t\t\t\tPlease enter a valid option!"<<endl;
            }
        }
    }while(1);
}

void admin::login()
{
    system("cls");
    cout<<"\t    ___________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t------------------------------------    ADMIN LOGIN    ------------------------------------"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t    ***********************************************************************************\n\n"<<endl;

    cout<<"\n\n\t\t\tEnter PASSWORD (\"admin@2024\"):\t";
    string passw;
    cin>>passw;
    if(passw==password){
        cout<<"\n\n\t\t\tYou have successfully LOGGED IN."<<endl;
        adminloggedIn=1;
    }
    else{
        cout<<"\n\n\t\t\tWRONG PASSWORD. Please try again."<<endl;
    }
    system("pause");
}

void admin::logout()
{
    system("cls");
    cout<<"\t    ___________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t------------------------------------    LOGOUT PAGE    ------------------------------------"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t    ***********************************************************************************\n\n"<<endl;

    char y;
    cout<<"\t\t\tWARNING\n\tDo you want to logout? Press Y to confirm:\t";
    cin>>y;
    if(y!='y' && y!='Y'){
        cout<<"\n\n\tUnable to logout. Returning to login menu\n";
        system("pause");
        return;
    }
    if(adminloggedIn==1){
        cout<<"\n\n\t\t\tYou are now logged out...\n\n";
        adminloggedIn=0;
    }
    else{
        cout<<"\t\t\t\n\nYou are NOT logged in."<<endl;
    }
    system("pause");
}

void admin::showacc(){
    system("cls");
    if(adminloggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to continue\n\n";
        system("pause");
        return;
    }
    ifstream file("AdminAccount.txt");
    string usern;
    int payment;
    cout<<"User\t\tPayment"<<endl;
    while(file>>usern>>payment){
        cout<<usern<<"\t\t"<<payment<<endl;
    }
    file.close();
    system("pause");
}

void admin::showstocks()
{
    system("cls");
    if(adminloggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to continue\n\n";
        system("pause");
        return;
    }
    cout<<"\t    _____________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------               --------------------------------------"<<endl;
    cout<<"\t------------------------------------    SHOW STOCKS    -------------------------------------"<<endl;
    cout<<"\t -------------------------------------               --------------------------------------"<<endl;
    cout<<"\t    *************************************************************************************\n\n"<<endl;
    string prodId,prodName;
    int prodPrice,n,exist=0;
    ifstream file("Stocks.txt");
    if(!file){
        cout<<"\t\t\tFile doesn't exist"<<endl;
    }
    else{
        cout<<"\t\tProduct ID\t\tProduct Name\t\tPrice\t\tNo. of Stocks"<<endl;
        while(file>>prodId>>prodPrice>>n)
        {
            exist=1;
            cout<<"\t\t"<<prodId<<"\t\t\t"<<getprodname(prodId)<<"\t\t"<<prodPrice<<"\t\t"<<n<<endl;
        }
    }
    file.close();
    if(exist==0){
        cout<<"\n\n\t\tThere is no product in the stock!!!!"<<endl;
    }
    system("pause");
}

void admin::updatestocks(){
    system("cls");
    if(adminloggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to continue\n\n";
        system("pause");
        return;
    }
    cout<<"\t    ______________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------                 --------------------------------------"<<endl;
    cout<<"\t------------------------------------    UPDATE STOCKS    -------------------------------------"<<endl;
    cout<<"\t -------------------------------------                 --------------------------------------"<<endl;
    cout<<"\t    **************************************************************************************\n\n"<<endl;

    int a;
    cout<<"\t\t\tPRESS 1 to ADD stocks"<<endl;
    cout<<"\t\t\tPRESS 2 to UPDATE stocks"<<endl;
    cout<<"\t\t\tPRESS 3 to DELETE stocks"<<endl;
    cout<<"\t\tEnter your choice:\t";
    cin>>a;

    switch(a){
        case 1:{
            addstocks();
            break;
        }
        case 2:{
            changestocks();
            break;
        }
        case 3:{
            deletestocks();
            break;
        }
        default:{
            cout<<"\t\t\tEnter the correct choice"<<endl<<endl;
        }
    }
    system("pause");
}

void admin::deletestocks(){
    system("cls");
    string prodIdd,prodId,prodName;
    int prodPrice,n,exist=0;
    cout<<"\t\t\tEnter PRODUCT ID of the item:\t";
    cin>>prodIdd;
    ifstream file("Stocks.txt");
    ofstream file1("Stocks1.txt", ios::app);
    if(!file){
        cout<<"\t\t\tFile doesn't exist"<<endl;
    }
    else{
        while(file>>prodId>>prodPrice>>n){
            if(prodIdd==prodId){
                exist=1;
            }
            else{
                file1<<prodId<<' '<<prodPrice<<' '<<n<<endl;
            }
        }
        file.close();
        file1.close();
        remove("Stocks.txt");
        rename("Stocks1.txt", "Stocks.txt");
        if(exist==0){
            cout<<"\t\t\tProduct doesn't exist"<<endl;
        }
        system("pause");
    }
}

void admin::changestocks(){
    system("cls");
    string prodIdd, prodId, prodName, prodNname;
    int prodPrice, prodPprice, n, nn, exist=0;
    cout<<"\t\t\tEnter PRODUCT ID of the item:\t";
    cin>>prodIdd;
    ifstream file("Stocks.txt");
    ofstream file1("Stocks1.txt", ios::app);
    if(!file){
        cout<<"\t\t\tFile doesn't exist"<<endl;
    }
    else{
        while(file>>prodId>>prodPrice>>n){
            if(prodIdd==prodId){
                exist=1;
                cout<<"\t\t\tUPDATE the details of the product"<<endl;
                cout<<"\t\t\tEnter PRODUCT PRICE:\t";
                cin>>prodPprice;
                cout<<"\t\t\tEnter NUMBER of Stocks:\t";
                cin>>nn;
                file1<<prodIdd<<' '<<prodPprice<<' '<<nn<<endl;
            }
            else{
                file1<<prodId<<' '<<prodPrice<<' '<<n<<endl;
            }
        }
    }
    file.close();
    file1.close();
    remove("Stocks.txt");
    rename("Stocks1.txt", "Stocks.txt");
    if(exist==0){
        cout<<"\t\t\tProduct doesn't exist"<<endl;
        cout<<"\n\t\t\tDo you want to add the product now? (If yes, Press y)";
        char a;
        cin>>a;
        if(a=='y' || a=='Y'){
            addstocks();
        }
        else{
            return;
        }
    }
    system("pause");
}

void admin::addstocks(){
    system("cls");
    string prodId, prodName;
    int prodPrice, n;
    cout<<"\tEnter PRODUCT ID:\t";
    cin>>prodId;
    if(!stockregistered(prodId)){
        cout<<"\t\tThe product is not registered\n";
        system("pause");
        return;
    }
    cout<<"\tEnter PRODUCT PRICE:\t";
    cin>>prodPrice;
    cout<<"\tEnter NUMBER of Stocks:\t";
    cin>>n;
    ofstream file("Stocks.txt", ios::app);
    file<<prodId<<' '<<prodPrice<<' '<<n<<endl;
    file.close();
    system("pause");
}

void admin::registerstock(){
    system("cls");
    if(adminloggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to continue\n\n";
        system("pause");
        return;
    }
    string prodID, prodName;
    cout<<"\tEnter the PRODUCT ID:\t";
    cin>>prodID;
    cin.ignore();
    cout<<"\tEnter the PRODUCT Name:\t";
    getline(cin, prodName);
    ofstream file("RegisteredGoods.csv", ios::app);
    file<<prodID<<","<<prodName<<endl;
    file.close();
    cout<<"\n\n\t\tProduct ID "<<prodID<<" registered"<<endl;
    system("pause");
}

bool admin::stockregistered(string prodId){
    string prodID, prodName;
    fstream file("RegisteredGoods.csv", ios::in);
    while(getline(file, prodID, ',')){
        getline(file, prodName, '\n');
        if(prodID==prodId){
            return true;
        }
    }
    return false;
}

string admin::getprodname(string prodId){
    string prodID, prodName;
    fstream file("RegisteredGoods.csv", ios::in);
    while(getline(file, prodID, ',')){
        getline(file, prodName, '\n');
        if(prodID==prodId){
            return prodName;
        }
    }
    return "error404";
}
