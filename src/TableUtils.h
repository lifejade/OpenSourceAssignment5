#include <string>
#include <vector>
#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>


namespace OSA5 {
    class TableUtils{
    public :
        static int createTable(MYSQL* conn_ptr);
    };
}