#include "account.h"
#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>

namespace OSA5{
int start_menu();
int switchCase(int n);
int excute_exit();
void selectDB(MYSQL* conn_ptr);
void createDB(MYSQL* conn_ptr);
}
