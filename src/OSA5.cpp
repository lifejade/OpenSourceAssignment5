#include <string>
#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>
#include "OSA5.h"

using namespace std;
using namespace heaan;


namespace OSA5{
int start_menu(){
    cout << "OpenSourceAssignment5(OSA5) - by 20011759 ParkSuMin" << endl;
    cout << "mysql + HEAAN project, github flow" << endl;
    
    cout << "connect db..." <<endl << "input your user name, password and database" << endl;

    MYSQL conn_ptr;
    mysql_init(&conn_ptr);    //mssql initialize
    while(true){
        string name;
        string password;
        
        cout << "user name (recommend - root) : ";
        getline(cin,name);
        cout << "password (recommend - ) : ";
        getline(cin,password);
        
        if(!mysql_real_connect(&conn_ptr, "localhost", name.c_str(), password.c_str(), NULL, 0, NULL, 0))
        {
        printf("%s\n", mysql_error(&conn_ptr));
        }else{
            break;
        }
    }
    

    cout << "select or create your db" << endl;
    cout << "1 : select, 2 : create" << endl;
    int temp = cin.get();
    while(cin.get() != '\n')
            continue;
    
    switch(temp){
        case 1: break;
        case 2: cout << "sorry i didn't make create yet...";break;
    }
    while(true){
        cout << "databases list : " << endl;
        MYSQL_RES* res = mysql_list_dbs(&conn_ptr,"%");
        MYSQL_ROW row;
        
        while((row = mysql_fetch_row(res)))
        {
            cout << row[0] << endl;
        }
        cout << "input database name" << endl;
        string tmp;
        getline(cin,tmp);
        if(mysql_select_db(&conn_ptr,tmp.c_str()))
            break;
        cout << "error - does not exist database" << endl;
    }
    
    
    cout << "please log-in or create key" <<endl;
    //TODO : log-in or create HEAAN account

    int n = -1;
    while(true) {
        cout << "input number to act" << endl;
        cout << "0 : change account" << endl;
        cout << "1 : create table" << endl;
        cout << "2 : input values" << endl;
        cout << "3 : show table" << endl;
        cout << "4 : User input-DQL statement" << endl;
        cout << "5 : exit" << endl;

        n = cin.get();
        while(cin.get() != '\n')
            continue;
        n -= '0';

        if(switchCase(n) == 1)
            return 0;
        cout << endl << endl;
    }
    

    return 0;
}

//if select exit prgram case, return 1, else return 0
int switchCase(int n){
        switch(n){
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: return excute_exit();
        break;
        default: cout << "input error, please input again" << endl; break;
        }
}

int excute_exit(){
    cout << endl << "you input \"exit\" and..." << endl;
    cout << "0 or else : redo" << endl;
    cout << "1 : exit database" << endl;
    cout << "2 : exit program" << endl;

    int n = -1;
    n = cin.get();
    while(cin.get() != '\n')
         continue;
    n = n - '0';

    switch(n){
        case 1: switchCase(1); return 0;
        case 2: return 1;
        default : return 0;
    }
}
}
