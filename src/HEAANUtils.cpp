#include "HEAANUtils.h"

namespace OSA5{
    ZZ* HEAANUtils::Encrypt(account* ac, complex<double>* vec){
        Ciphertext cipher;
        int slot = 1<<(ac->logn);
        ac->scheme_ptr->encrypt(cipher,vec,slot,ac->logp,ac->logq);
        
        ZZ* result = new ZZ[slot];
        long gap = Nh / (slot);
        for(int i = 0;i<slot;i++){
            result[i] = cipher.ax[i * slot];
            result[i] = result[i] << 100;
            result[i] += cipher.ax[Nh +i * slot];
            result[i] = result[i] << 100;

            result[i] += cipher.bx[i*slot];
            result[i] = result[i] << 100;
            result[i] += cipher.bx[Nh + i*slot]; 
        }

        return result;
    }

    
    complex<double>* HEAANUtils::Decrypt(account* ac, complex<double>* vec){
        return NULL;
    }

    ZZ HEAANUtils::stringToNumber(string str)
    {
    ZZ number = conv<ZZ>(str[0]);
    long len = str.length();
    for(long i = 1; i < len; i++)
    {
        number *= 10;
        number += conv<ZZ>(str[i]);
    }

    return number;
    }

    string HEAANUtils::numberToString(ZZ num)
    {
    long len = ceil(log(num)/log(10));
    char str[len];
    for(long i = len-1; i >= 0; i--)
    {
        str[i] = conv<int>(num % 10);
        num /= 10;
    }

    return (string) str;
    }
}