#include <string>
#include <cmath>
#include </HEAAN/HEAAN/src/HEAAN.h>
#include "src/OSA5.h"

using namespace std;
using namespace heaan;



int main(){
    cout << "OpenSourceAssignment5 - by 20011759 ParkSuMin" << endl;
    cout << "mysql + HEAAN project, github flow" << endl;
    
    cout << "waiting for connect to db..." << endl;

    cout << "select your db" << endl;

    cout << "please log-in or create key" <<endl;

    int n = -1;
    while(true) {
    cout << "input number to act" << endl;
    cout << "0 : change account" << endl;
    cout << "1 : create table" << endl;
    cout << "2 : input values" << endl;
    cout << "3 : show table" << endl;
    cout << "4 : User input-DQL statement" << endl;
    cout << "5 : exit" << endl;
    cin >> n;
    if(switchCase(n) != 0){
        cout << "input error, please input again" <<endl << endl;
        continue;
    }


    if(n>=0 && n <= 4){
        
    }else if(n == 5){
        cout << endl << "you input \"exit\" and..." << endl;
        cout << "0 : redo" << endl;
        cout << "1 : exit database" << endl;
        cout << "2 : exit program" << endl;
        cin >> n;
        switch(n){
            case 0: continue;
            case 1: break;
            case 2: return;
        }
    }
    
    }
    

    return 0;
}

//if select wrong case, return 1, else return 0
int switchCase(int n){
    switch(n){
        case 0: break;
        case 1: break;
        case 2: break;
        case 4: break;
        default: return;
    }
}