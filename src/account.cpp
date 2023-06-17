#include "account.h"


namespace OSA5{
    account::account(){
        logq = 800; ///< Ciphertext Modulus
	    logp = 30; ///< Real message will be quantized by multiplying 2^40
	    logn = 8; ///< log2(The number of slots)

        Ring ring;
	    secretKey = new SecretKey(ring);
	    scheme_ptr = new Scheme(*secretKey, ring);
    };

    account::~account(){
        free(scheme_ptr);
    };
}