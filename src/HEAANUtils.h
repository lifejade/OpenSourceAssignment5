#ifndef OSA5_HEAANUTILS_H
#define OSA5_HEAANUTILS_H

#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>
#include "account.h"
#include "vector"
#include <NTL/ZZ.h>

using namespace NTL;
using namespace std;
using namespace heaan;

namespace OSA5{
    class HEAANUtils{
        public:

        static ZZ* Encrypt(account* ac, complex<double>* vec);
        static complex<double>* Decrypt(account* ac, complex<double>* vec);
        static string numberToString(ZZ num);
        static ZZ stringToNumber(string str);
    };
    
}

#endif