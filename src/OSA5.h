#ifndef OSA5_OSA5_H
#define OSA5_OSA5_H

#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>
#include <string>
#include "account.h"
#include "TableUtils.h"

using namespace std;
using namespace heaan;

namespace OSA5{
int start_menu();
int switchCase(int n);
int excute_exit();
void selectDB(MYSQL* conn_ptr);
void createDB(MYSQL* conn_ptr);
}

#endif