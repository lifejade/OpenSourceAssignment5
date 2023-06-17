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
    int n = cin.get();
    while(cin.get() != '\n')
        continue;
    n -= '0';

    switch(n){
        case 1: selectDB(&conn_ptr); break;
        case 2: createDB(&conn_ptr); break;
    }
    
    
    cout << "please log-in or create key" <<endl;
    //TODO : log-in or create HEAAN account
    account ac;

    /*
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
    }*/

    cout << "temp : create tables" << endl;
    TableUtils::createTable(&conn_ptr);
    

    return 0;
}

void selectDB(MYSQL* conn_ptr){
    while(true){
        cout << "databases list : " << endl;
        MYSQL_RES* res = mysql_list_dbs(conn_ptr,"%");
        MYSQL_ROW row;
        
        while((row = mysql_fetch_row(res)))
        {
            cout << row[0] << endl;
        }
        cout << "input database name" << endl;
        string tmp;
        getline(cin,tmp);

        if(mysql_query(conn_ptr,("USE " + tmp).c_str()))
            printf("%s\n", mysql_error(conn_ptr));
        else
            break;
    }
}

void createDB(MYSQL* conn_ptr){
    cout << "input name" << endl;
    string name;
    getline(cin,name);
    if(mysql_query(conn_ptr,("CREATE DATABASE "+ name + " ").c_str())){
        mysql_query(conn_ptr,("USE "+name).c_str());
    } else{
        printf("%s\n", mysql_error(conn_ptr));
    }
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
