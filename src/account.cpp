#include "account.h"


namespace OSA5{
    account::account(){
        logq = 8; ///< Ciphertext Modulus
	    logp = 2; ///< Real message will be quantized by multiplying 2^40
	    logn = 2; ///< log2(The number of slots)

        
	    secretKey = new SecretKey(ring);
	    scheme_ptr = new Scheme(*secretKey, ring);
    };

    account::~account(){
        free(scheme_ptr);
        free(secretKey);
    };
}