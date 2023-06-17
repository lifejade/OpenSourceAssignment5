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
            cout << stringBuffer << endl;
        }

        string result;
        for(int i=0;i<firstidx;i++){
            result += (vec[i] + ' ');
        }

        
        vec[firstidx] = vec[firstidx].erase(0,1);
        vec.back() = vec.back().erase(vec.back().size() - 2,2);
        
        result += "(";

        for(int i=firstidx; i<vec.size(); i++){
            result += (vec[i++] + "_r ");
            result += (vec[i] + " ");
        }
        result += ',';
        for(int i=firstidx; i<vec.size(); i++){
            result += (vec[i++] + "_i ");
            result += (vec[i] + " ");
        }

        result += ")";

        cout << "result_temp" << result << endl;

        if(!mysql_query(conn_ptr, result.c_str()));
            printf("%s\n", mysql_error(conn_ptr));
        
        return 1;
    }
}