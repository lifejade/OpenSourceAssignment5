#include "HEAANUtils.h"

namespace OSA5{
    ZZ* HEAANUtils::Encrypt(account* ac, complex<double>* vec){
        Ciphertext cipher;
        int slot = 1<<(ac->logn);
        ac->scheme_ptr->encrypt(cipher,vec,slot,ac->logp,ac->logq);
        ZZ* result = new ZZ[slot];
        long gap = Nh / (slot);
        for(int i = 0;i<slot;i++){
            
            result[i] = cipher.ax[i * gap];
            result[i] <<= 100;

            result[i] += cipher.ax[Nh +i * gap];
            result[i] <<= 100;

            result[i] += cipher.bx[i*gap];
            result[i] <<= 100;

            result[i] += cipher.bx[Nh + i*gap]; 
            //cout << "test" << result[i] << endl;
            if(i < 3){
                cout << cipher.ax[i*gap] << " : " << cipher.ax[Nh + i*gap] << endl;
            }
        }

        return result;
    }

    
    complex<double>* HEAANUtils::Decrypt(account* ac, MYSQL_ROW row, int len){
        int slot = 1<<(ac->logn);        
        ZZ* result = new ZZ[slot];
        ZZ mod(1);
        mod <<= 100;
        //cout << "mod : " << mod << endl; 

        long gap = Nh / (slot);
        
        Ciphertext cipher;

        cipher.logp = ac->logp;
        cipher.logq = ac->logq;
        cipher.n = 1 << ac->logn;

        for(int i = 0;i<len;i++){
            ZZ z = stringToNumber(row[i]);
            //cout << "test" << z << endl;
            cipher.bx[Nh + i * gap] = z % mod;
            z >>= 100;

            cipher.bx[i*gap] = z%mod;
            z >>= 100;

            cipher.ax[Nh + i*gap] = z%mod;
            z>>=100;

            cipher.ax[i*gap] = z%mod;
            if(i < 3){
                cout << cipher.ax[i*gap] << " : " << cipher.ax[Nh + i*gap] << endl;
            }
            
        }
        
        return ac->scheme_ptr->decrypt(*(ac->secretKey), cipher);
    }

    ZZ HEAANUtils::stringToNumber(string str)
    {
        ZZ number = conv<ZZ>(str[0] - '0');
        long len = str.length();
        for(long i = 1; i < len; i++)
        {
            ZZ temp = conv<ZZ>(str[i] - '0');
            if(temp < 0 || temp > 9){
                str.resize(i);
                break;
            }
            number *= 10;
            number += conv<ZZ>(str[i] - '0');
        }
        return number;
    }

    string HEAANUtils::numberToString(ZZ num)
    {
    long len = ceil(log(num)/log(ZZ(10)));
    char str[len] = {0,};
    for(long i = len-1; i >= 0; i--)
    {
        
        str[i] = conv<int>((num % 10) + '0');
        num /= 10;
    }
    cout << endl;

    return (string) str;
    }
}