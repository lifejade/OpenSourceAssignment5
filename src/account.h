#ifndef OSA5_ACCOUNT_H
#define OSA5_ACCOUNT_H

#include <mysql/mysql.h>
#include </HEAAN/HEAAN/src/HEAAN.h>

using namespace heaan;

namespace OSA5{
    class account{
        public:
        
        long logq; ///< Ciphertext Modulus
	    long logp; ///< Real message will be quantized by multiplying 2^40
	    long logn; ///< log2(The number of slots)

        
        Ring ring;
	    SecretKey* secretKey;
	    Scheme* scheme_ptr;
        
        account();
        ~account();
    };
}

#endif