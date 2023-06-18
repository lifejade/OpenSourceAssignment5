#include "HEAANUtils.h"

namespace OSA5{
    ZZ* HEAANUtils::Encrypt(account* ac, complex<double>* vec, int len){
        Ciphertext cipher;
        int slot = 1<<(ac->logn);
        ac->scheme_ptr->encrypt(cipher,vec,slot,ac->logp,ac->logq);
        ZZ* result = new ZZ[len];
        
        for(int i = 0;i<len;i++){
            long gap = ceil((float)N/len);
            result[i] = 0;

            for(int j=0;j<gap;j++){
                if(j + i*gap >= N)
                    break;
                result[i] <<= 12;
                result[i] += cipher.ax[j + i*gap];
                result[i] <<= 12;
                result[i] += cipher.bx[j + i*gap];
            }

            if(i < 3){
                cout << cipher.ax[i] << " : " << cipher.bx[i] << endl;
            }
            
        }
        //cout << "test : " << result[0] << endl;
        return result;
    }

    
    complex<double>* HEAANUtils::Decrypt(account* ac, MYSQL_ROW row, int len){
        ZZ mod(1);
        mod <<= 12;
        //cout << "mod : " << mod << endl; 

        long gap = ceil((float)N/len);
        
        Ciphertext cipher;

        cipher.logp = ac->logp;
        cipher.logq = ac->logq;
        cipher.n = 1 << ac->logn;

        for(int i = 0;i < len;i++){
            ZZ z = stringToNumber(row[i]);
            //cout << "test : " << z << endl;
            for(int j = 0;j<gap;j++){
                //cout << "test" << z << endl;
                int tmp = N - (i * gap + j) - 1;
                if(tmp < 0)
                    break;

                cipher.bx[tmp] = z % mod;
                z >>= 12;
                cipher.ax[tmp] = z % mod;
                z >>= 12;
            }

            if(i < 3){
                cout << cipher.ax[i] << " : " << cipher.bx[i] << endl;
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