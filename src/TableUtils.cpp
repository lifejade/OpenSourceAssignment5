#include "TableUtils.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace heaan;

namespace OSA5 {
    //create table, domain  = domain * 2 (because of complex number)
    int TableUtils::createTable(MYSQL* conn_ptr){
        string input;
        getline(cin, input);

        istringstream ss(input);
        string stringBuffer;
        vector<string> vec;
        vec.clear();
        int firstidx = -1;

        while (getline(ss, stringBuffer, ' ')){
        vec.push_back(stringBuffer);
        if(stringBuffer.front() == '('){
            firstidx = vec.size() - 1;
        }
        }
        

        //mysql_query(conn_ptr, input.c_str());

        return 1;
    }
}