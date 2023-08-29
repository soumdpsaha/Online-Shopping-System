#include "buyer.h"
#include<stdlib.h>
using namespace std;

bool loggedIn = 0;

void buyer::BloginMenu(){
    do{
        system("cls");
        cout<<"\t    __________________________________________________________________________________"<<endl;
        cout<<"\t -------------------------------------              -------------------------------------"<<endl;
        cout<<"\t------------------------------------    LOGIN MENU    ------------------------------------"<<endl;
        cout<<"\t -------------------------------------              -------------------------------------"<<endl;
        cout<<"\t    **********************************************************************************\n\n"<<endl;
        int a;
        cout<<"\t\t\tPRESS 1 to LOGIN"<<endl;
        cout<<"\t\t\tPRESS 2 to SIGN UP"<<endl;
        cout<<"\t\t\tPRESS 3 if you FORGOT PASSWORD"<<endl;
        cout<<"\t\t\tPRESS 4 to show account details"<<endl;
        cout<<"\t\t\tPRESS 5 to CHANGE PASSWORD"<<endl;
        cout<<"\t\t\tPRESS 6 to LOGOUT"<<endl;
        cout<<"\t\t\tPRESS 7 to delete account"<<endl;
        cout<<"\t\t\tPRESS 8 to View items"<<endl;
        cout<<"\t\t\tPRESS 9 to View cart"<<endl;
        cout<<"\t\t\tPRESS 10 to BUY CART"<<endl;
        cout<<"\t\t\tPRESS 11 to RETURN to previous menu "<<endl;
	    cout<<"\n\n\t\t\t\t\t\t\tEnter your choice:\t";
	    cin>>a;
        switch(a){
            case 1:{
                login();
                break;
            }
            case 2:{
                registration();
                break;
            }
            case 3:{
                forgot();
                break;
            }
            case 4:{
                showacc();
                break;
            }
            case 5:{
                changepassw();
                break;
            }
            case 6:{
                logout();
                break;
            }
            case 7:{
                deleteacc();
                break;
            }
            case 8:{
                viewitems();
                break;
            }
            case 9:{
                viewcart();
                break;
            }
            case 10:{
                buycart();
                break;
            }
            case 11:{
                cout<<"\n\t\t\t\t\tSee you again!"<<endl;
                loggedIn=0;
                return;
                break;
            }
            default:{
                cout<<"\n\t\t\t\t\tPlease enter a valid option!"<<endl;
            }
        }
    }while(1);
}

string buyer::getprodname(string prodId){
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

void buyer::viewitems(){
    system("cls");
    cout<<"\t    ___________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t------------------------------------    VIEW ITEMS    -------------------------------------"<<endl;
    cout<<"\t -------------------------------------              --------------------------------------"<<endl;
    cout<<"\t    ***********************************************************************************\n\n"<<endl;
    string prodId;
    int prodPrice,n,exist=0;
    ifstream file("Stocks.txt");
    if(!file){
        cout<<"\t\t\tShop closed"<<endl;
    }
    else{
        cout<<"\t\tProduct ID\t\tProduct Name\t\tPrice"<<endl;
        while(file>>prodId>>prodPrice>>n){
            exist=1;
            cout<<"\t\t"<<prodId<<"\t\t\t"<<getprodname(prodId)<<"\t\t"<<prodPrice;
            if(n==0){
                cout<<"\t\tNo stocks left"<<endl;
            }
            else if(n<=2){
                cout<<"\t\tOnly "<<n<<" stocks left"<<endl;
            }
            else{
                cout<<endl;
            }
        }
    }
    file.close();
    if(exist==0){
        cout<<"\n\n\t\tThere is no product in the stock!!!!"<<endl;
        return;
    }
    int a;
    char ans;
    cout<<"\n\t\t\tDo you want add any item to cart?(y)\t";
    cin>>ans;
    if(ans=='y' || ans=='Y') a=1;
    else a=0;
    while(a){
        string eprodid;
        int m;
        cout<<"\n\t\t\t\tAdd to cart:\n";
        cout<<"\n\t\t\tEnter Product ID:\t";
        cin>>eprodid;
        cout<<"\n\t\t\tEnter quantity:\t";
        cin>>m;
        addtocart(eprodid, m);
        cout<<"\n\t\t\tDo you want another item? If yes press 1:\t";
        int b;
        cin>>b;
        if(b!=1) a=0;
    }
    system("pause");
}

void buyer::addtocart(string prodId, int n){
    int nn, prodP, exist=0;
    string prodIdd;

    ifstream file("Stocks.txt");
    while(file>>prodIdd>>prodP>>nn){
        if(prodIdd==prodId){
            exist=1;
            if(n<=nn){
                cart[prodId]={prodP*n, n};
            }
            else{
                cout<<"\tNot enough stock!!!";
            }
        }
    }
    file.close();

    int totalSum=0;
    for(auto it: cart){
        totalSum+=it.second.first;
    }
    cartValue=totalSum;
    if(exist==0){
        cout<<"\tWrong PROD ID"<<endl;
    }
}

void buyer::viewcart(){
    system("cls");
    if(cart.empty()){
        cout<<"\t\tCart is empty!"<<endl;
        system("pause");
        return;
    }
    cout<<"PRODUCT ID\t\tPRODUCT NAME\t\tPRICE\t\tQUANTITY"<<endl;
    for(auto it: cart){
        cout<<it.first<<"\t\t\t"<<getprodname(it.first)<<"\t\t"<<it.second.first<<"\t\t"<<it.second.second<<endl;
    }
    cout<<"\t\tFINAL PRICE:\t"<<cartValue<<endl<<endl;

    cout<<"Do you want to BUY NOW? (y)\t";
    char a;
    cin>>a;
    if(a=='y' || a=='Y'){
        cout<<"\n\n\t\tProceeding to BUY CART menu..."<<endl<<endl;
        system("pause");
        buycart();
        return;
    }
    else{
        cout<<"\t\tReturning to BUYER menu..."<<endl<<endl;
    }
    system("pause");
}

void buyer::showbill(){
    system("cls");
    if(loggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to proceed\n\n";
        system("pause");
        login();
    }
    if(cart.empty()){
        cout<<"\t\tCart is empty!"<<endl;
        system("pause");
        return;
    }
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"PRODUCT ID\t\tPRODUCT NAME\t\tPRICE\t\tQUANTITY"<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    for(auto it: cart){
        cout<<it.first<<"\t\t\t"<<getprodname(it.first)<<"\t\t"<<it.second.first<<"\t\t"<<it.second.second<<endl;
    }
    cout<<"_______________________________________________________________________________"<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"\t\t\t\t\t\tFINAL PRICE:\t"<<cartValue<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
}

void buyer::buycart(){
    system("cls");
    if(loggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to proceed\n\n";
        system("pause");
        login();
    }
    showbill();
    char a;
    cout<<"\t\tDo you want to CONFIRM payment?(y)";
    cin>>a;
    if(a=='y' || a=='Y'){
        cout<<"\t\t\tPayment confirmed"<<endl<<endl;
        ofstream file("AdminAccount.txt", ios::app);
        file<<username<<' '<<cartValue<<endl;
        cartValue=0;
        file.close();
        cart.clear();
    }
    else{
        cout<<"\t\t\tReturning to main menu"<<endl<<endl;
    }
    system("pause");
}

void buyer::emptycart(){
    system("cls");
    cout<<"\t\t\tDo you want to confirm EMPTY CART? (y/n)"<<endl<<endl;
    char a;
    cin>>a;
    if(a=='Y' || a=='y'){
        cart.clear();
        cout<<"\t\t\tCart emptied!"<<endl<<endl;
    }
    else{
        cout<<"\t\t\tReturning to main menu"<<endl<<endl;
    }
    system("pause");
}

void buyer::changepassw(){
    system("cls");
    if(loggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to change your password\n\n";
        system("pause");
        login();
    }
    else{
        string usern, passw;
        ifstream file("LoginData.txt");
        ofstream file1("LoginData1.txt", ios::app);
        while(file>>usern>>passw){
            if(usern==username){
                cout<<"\t\t\tEnter the new password:\t";
                cin>>password;
                file1<<usern<<' '<<password<<endl;
            }
            else{
                file1<<usern<<' '<<passw<<endl;
            }
        }
        file.close();
        file1.close();
        remove("LoginData.txt");
        rename("LoginData1.txt", "LoginData.txt");
        cout<<"\t\t\tPassword changed\n\n";
        system("pause");
        //loginMenu();
    }
}

void buyer::deleteacc(){
    system("cls");
      if(loggedIn==0){
        cout<<"\n\n\t\t\tYou are NOT logged in...\n\t\t\t...Please LOGIN to delete your account\n\n";
        system("pause");
        login();
    }
    else{
        string usern, passw;
        int exist=0;
        ifstream file("LoginData.txt");
        ofstream file1("LoginData1.txt", ios::app);
        while(file>>usern>>passw){
            if(usern==username){
                exist=1;
            }
            else{
                file1<<usern<<' '<<passw<<endl;
            }
        }
        if(exist==0)
        {
            cout<<"Account does not exist!!!"<<endl;
        }
        file.close();
        file1.close();
        remove("LoginData.txt");
        rename("LoginData1.txt", "LoginData.txt");

        exist=0;
        ifstream file2("RegistrationData.txt");
        ofstream file3("RegistrationData1.txt", ios::app);
        string fname, lname;
        string age;
        string phone;
        while(file2>>usern>>phone>>age>>fname>>lname){
            if(usern==username){
                exist=1;
            }
            else{
                file3<<usern<<' '<<phone<<' '<<age<<' '<<fname<<' '<<lname<<' '<<endl;
            }
        }
        if(exist==0)
        {
            cout<<"Account does not exist!!!"<<endl;
        }
        file2.close();
        file3.close();
        remove("RegistrationData.txt");
        rename("RegistrationData1.txt","RegistrationData.txt");
        cout<<"\t\t\tAccount deleted\n\n";
        loggedIn=0;
        system("pause");
    }
}

void buyer::logout(){
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
    if(loggedIn==0){
        cout<<"\n\n\t\t\tERROR!!! You are NOT logged in...\n\n";
    }
    else{
        cout<<"\n\n\t\t\tYou are now logged out...\n\n";
        loggedIn=0;
    }
    system("pause");
    //loginMenu();
}

void buyer::login(){
    system("cls");
    cout<<"\t    __________________________________________________________________________________"<<endl;
    cout<<"\t -------------------------------------              -------------------------------------"<<endl;
    cout<<"\t------------------------------------    LOGIN PAGE    ------------------------------------"<<endl;
    cout<<"\t -------------------------------------              -------------------------------------"<<endl;
    cout<<"\t    **********************************************************************************\n\n"<<endl;
    string usern, passw;
    int flag=0;
    cout<<"\n\n\t\t\tEnter USERNAME:\t";
    cin>>usern;
    cout<<"\t\t\tEnter PASSWORD:\t";
    cin>>passw;

    ifstream file("LoginData.txt");
    while(file>>username>>password){
        if(usern==username){
            if(passw==password){
                cout<<"\n\n\t\t\tLogin SUCCESSFUL\n\n"<<endl;
                flag = 1;
            }
            else{
                cout<<"\n\n\t\t\tINCORRECT Password!!!"<<endl;
                cout<<"\n\t\t\tRe-enter Password:\t";
                cin>>passw;
                if(passw==password){
                    cout<<"\n\n\t\t\tLogin SUCCESSFUL\n\n"<<endl;
                    flag = 1;
                }
                else{
                    cout<<"\n\n\t\t\tINCORRECT Password!!!"<<endl;
                    cout<<"\n\t\t\tClick on FORGOT PASSWORD to retrieve password"<<endl;
                    flag = 2;
                }
            }
            break;
        }
    }
    file.close();
    if(flag == 0){
        cout<<"\n\n\t\t\tUsername DOES NOT EXIST!!!"<<endl;
        cout<<"\n\n\t\t\tPlease enter correct Username\n\n"<<endl;
        //system("pause");
        cout<<"\n\n\t\tReturning to the Login Menu..."<<endl;
        system("pause");
    }
    else if(flag == 1){
        loggedIn=true;
        system("pause");
    }
    else if(flag == 2){
        cout<<"\n\t\t\tReturning to the Login Menu...\n\n"<<endl;
        system("pause");
    }
    //loginMenu();
}

void buyer::registration(){
    system("cls");
    cout<<"\t    ___________________________________________________________________________________"<<endl;
    cout<<"\t ----------------------------------                     ----------------------------------"<<endl;
    cout<<"\t---------------------------------    REGISTRATION PAGE    ---------------------------------"<<endl;
    cout<<"\t ----------------------------------                     ----------------------------------"<<endl;
    cout<<"\t    ***********************************************************************************\n\n"<<endl;
    int flag = 0;
    string ruser, usern, pass, rpass;
    cout<<"\t\t\tEnter a new username:\t";
    cin>>ruser;
    ifstream file("LoginData.txt");
    while(file>>usern>>pass){
        if(usern==ruser){
            flag=1;
            break;
        }
    }
    file.close();
    if(flag == 1){
        cout<<"\t\t\tThe username is already registered!!!!!!!!!"<<endl;
        cout<<"\t\t\tPlease login using this username or register using a new username."<<endl;
    }
    else{
        cout<<"\t\t\tSet a password:\t";
        cin>>rpass;

        ofstream file("LoginData.txt", ios::app);
        file<<ruser<<' '<<rpass<<endl;
        system("cls");
        cout<<"\t\t\tREGISTRATION SUCCESSFULL"<<endl;
        file.close();

        system("pause");
        system("cls");
        string fname, lname;
        string Phoneno;
        string age;
        cin.ignore();
        cout<<"\n\n\t\t\t\tEnter your First Name:\t";
        cin>>fname;
        cout<<"\n\n\t\t\t\tEnter your Last Name:\t";
        cin>>lname;
        cout<<"\n\n\t\t\t\tEnter your Mobile Number:\t";
        cin>>Phoneno;
        cout<<"\n\n\t\t\t\tEnter your age:\t";
        cin>>age;
        ofstream rfile("RegistrationData.txt", ios::app);
        rfile<<ruser<<' '<<Phoneno<<' '<<age<<' '<<fname<<' '<<lname<<endl;
        rfile.close();
    }
    //loginMenu();
}

void buyer::showacc(){
    system("cls");
    if(loggedIn==true){
        string usern, fname, lname;
        string age;
        string phone;
        ifstream file("RegistrationData.txt");
        while(file>>usern>>phone>>age>>fname>>lname){
            if(usern==username){
                cout<<"\t\t\tName:  \t"<<fname<<' '<<lname<<endl;
                cout<<"\t\t\tMobile:\t"<<phone<<endl;
                cout<<"\t\t\tAge:   \t"<<age<<endl;
            }
        }
        system("pause");
        //loginMenu();
    }
    else{
        cout<<"\n\n\t\t\tPlease LOGIN and try again..."<<endl;
        system("pause");
        cout<<"\n\n\t\t\tDo you want to Login now? (y/n)\t";
        char ans;
        int n=0;
        do{
            cin>>ans;
            if(ans=='y'||ans=='Y'){
                login();
            }
            else if(ans=='n'||ans=='N'){
                cout<<"\n\n\t\t\tRedirecting to the Login Menu...\n\n";
                system("pause");
                //loginMenu();
            }
            else{
                cout<<"\n\n\t\t\tPlease enter a valid character (y/n):\t";
                n=1;
            }
        }while(n);
    }
}

void buyer::forgot(){
    system("cls");
    cout<<"\t    _______________________________________________________________________________"<<endl;
    cout<<"\t ---------------------------------                   ---------------------------------"<<endl;
    cout<<"\t--------------------------------    FORGOT PASSWORD    --------------------------------"<<endl;
    cout<<"\t ---------------------------------                   ---------------------------------"<<endl;
    cout<<"\t    *******************************************************************************\n\n"<<endl;
    int a;
    cout<<"\t\t\tPRESS 1 to search username"<<endl;
    cout<<"\t\t\tPRESS 2 to return to Login Menu"<<endl;
    cout<<"\t\tEnter your choice:\t";
    cin>>a;

    int found=0;
    string usern, passw, fuser, keyc;
    switch(a){
        case 1:{
            cout<<"\t\t\tEnter your username:\t";
            cin>>fuser;
            ifstream file("LoginData.txt");
            while(file>>usern>>passw){
                if(usern == fuser){
                    found=1;
                    cout<<"\n\n\t\t\tUsername found";
                    cout<<"\n\n\t\t\tEnter the secret key (\"customer\"):\t";
                    cin>>keyc;
                    if(keyc == "customer"){
                        cout<<"\n\t\t\tYou entered the correct Key"<<endl;
                        cout<<"\n\t\t\tYour Password is:\t"<<passw<<endl<<endl;
                    }
                    else{
                        cout<<"\n\t\t\tYou entered the wrong key"<<endl<<"\n\t\tPlease try again later..."<<endl<<endl;
                    }
                    system("pause");
                }
            }
            if(found==0){
                cout<<"\n\n\t\t\tUsername does not exist"<<endl<<"\t\tPlease try again later";
                system("pause");
            }
        }
        case 2:{
            return;
            break;
        }
        default:{
            cout<<"\n\n\t\tInvalid option! Try again";
            forgot();
        }
    }
}
