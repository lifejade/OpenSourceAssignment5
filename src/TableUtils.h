#ifndef OSA5_TABLEUTILS_H
#define OSA5_TABLEUTILS_H

#include <string>
#include <vector>
#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>
#include "HEAANUtils.h"
#include <sstream>
#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace heaan;
using namespace NTL;


namespace OSA5 {
    class TableUtils{
    public :
        static int insertValues(MYSQL* conn_ptr, account* ac);
        static int createTable(MYSQL* conn_ptr);
        static vector<string> splitString(string str, char dl);
    };
}
#endif