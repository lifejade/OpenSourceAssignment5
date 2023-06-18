#include "TableUtils.h"


namespace OSA5 {
    //create table
    int TableUtils::createTable(MYSQL* conn_ptr){
        string input;
        getline(cin, input);

        vector<string> vec = splitString(input, ' ');
        int firstidx = -1;
        for(string v : vec){
            firstidx++;
            if(v[0] == '('){
                break;
            }
        }

        string result;
        for(int i=0;i<firstidx;i++){
            result += (vec[i] + ' ');
        }

        
        vec[firstidx] = vec[firstidx].erase(0,1);
        vec.back() = vec.back().erase(vec.back().size() - 2,2);
        
        result += "(";

        for(int i=firstidx; i<vec.size(); i++){
            result += (vec[i++] + ' ');
            //modulus = 100bit
            //ax, bx, and imaginary each other => *4,
            //100*4/8 = 50byte 
            result += "BLOB(60)";
            if(i != vec.size() - 1)
                result += ", ";
        }
        result += ")";

        cout << "result_temp" << result << endl;

        if(!mysql_query(conn_ptr, result.c_str()));
            printf("%s\n", mysql_error(conn_ptr));
        
        return 1;
    }

    int TableUtils::insertValues(MYSQL* conn_ptr, account* ac){
        string input;
        getline(cin, input);

        vector<string> vec = splitString(input,' ');
        int firstidx = -1;

        for(string v : vec){
            firstidx++;
            if(v[0] == '(')
                break;
        }
        
        string result;
        for(int i=0;i<firstidx;i++){
            result += (vec[i] + ' ');
        }

        vec[firstidx] = vec[firstidx].erase(0,1);
        vec.back() = vec.back().erase(vec.back().size() - 2,2);
        string store_tmp;
        for(int i=firstidx;i<vec.size();i++){
            store_tmp += vec[i];
        }
        result += "(";

        vec.clear();
        vec = splitString(store_tmp,',');
        //encrypt vec
        complex<double>* vec_c = new complex<double>[1<<ac->logn];
        for(int i=0;i<1<<(ac->logn);i++){
            if(i < vec.size()){
                vec_c[i] = complex<double>(stod(vec[i]),0);
            }else{
                vec_c[i] = complex<double>(0,1);
            }
            //cout << vec_c[i] << endl;
        }
        ZZ* cyphertext = HEAANUtils::Encrypt(ac,vec_c);
        
        //input query
        for(int i = 0;i<vec.size(); i++){
            result += "BINARY \"" + HEAANUtils::numberToString(cyphertext[i]) + "\"";
            if(i != vec.size() -1){
                result += ", ";
            }
        }
        result += ")";
        if(!mysql_query(conn_ptr,result.c_str()));
            printf("%s\n", mysql_error(conn_ptr));
        
        delete [] cyphertext;
    }
    int TableUtils::selectFrom(MYSQL* conn_ptr, account* ac){
        string input;
        getline(cin, input);
        if(mysql_query(conn_ptr,input.c_str())){
            printf("%s\n", mysql_error(conn_ptr));
            return 0;
        }
        MYSQL_RES* result;
        result = mysql_store_result(conn_ptr);

        MYSQL_ROW row;
        
        while((row = mysql_fetch_row(result)) != NULL){
            for(int i=0;i < result->row_count;i++){
                cout << row[i] << "   |   ";
            }
            cout << '\n';
        }


        mysql_free_result(result);
    }
    vector<string> TableUtils::splitString(string str, char dl){
        istringstream ss(str);
        string stringBuffer;
        vector<string> vec;
        vec.clear();

        while (getline(ss, stringBuffer, dl)){
            vec.push_back(stringBuffer);
            cout << stringBuffer << endl;
        }

        return vec;
    }
}