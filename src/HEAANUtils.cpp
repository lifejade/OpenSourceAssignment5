#include "HEAANUtils.h"

namespace OSA5{
    static Ciphertext test;
    ZZ* HEAANUtils::Encrypt(account* ac, complex<double>* vec, int len){
        Ciphertext cipher;
        int slot = 1<<(ac->logn);
        ac->scheme_ptr->encrypt(cipher,vec,slot,ac->logp,ac->logq);
        ZZ* result = new ZZ[len];
        long gap = ceil((float)N/len);
        for(int i = 0;i<len;i++){
            result[i] = ZZ(0);

            for(int j=0;j<gap;j++){
                if(j + i*gap >= N)
                    break;
                result[i] <<= 64;
                result[i] += cipher.ax[j + i*gap];
                result[i] <<= 64;
                result[i] += cipher.bx[j + i*gap];


                if(j + i*gap == 0)
                    cout << cipher.ax[j + i*gap] << " | " << cipher.bx[j + i*gap] <<  endl;
            }
        }
        test.copy(cipher);
        return result;
    }

    
    complex<double>* HEAANUtils::Decrypt(account* ac, MYSQL_ROW row, unsigned long* length, int degree){
        ZZ mod(1);
        mod <<= 64;
        
        
        
        Ciphertext cipher;

        cipher.logp = ac->logp;
        cipher.logq = ac->logq;
        cipher.n = 1 << ac->logn;
        long gap = ceil((float)N/cipher.n);
        for(long i = 0;i < degree;i++){
            ZZ z = char_arrToNumber(row[i], length[i]);
            for(long j = 0;j<gap;j++){
                //cout << "test" << z << endl;
                long tmp = N - ((degree - i - 1) * gap + j) - 1;
                if(tmp < 0)
                    break;
                
                cipher.bx[tmp] = z % mod;
                z >>= 64;
                if(cipher.bx[tmp] > (mod / 2)){
                    cipher.bx[tmp] -= mod;
                    z+=1;
                }

                cipher.ax[tmp] = z % mod;
                z >>= 64;
                if(cipher.ax[tmp] > (mod / 2)){
                    cipher.ax[tmp] -= mod;
                    z+=1;
                }
                if(tmp == 0)
                    cout << cipher.ax[tmp] << " | " << cipher.bx[tmp] <<  endl;
            }

        }
        
        for(int i =0;i<N;i++){
            if(test.ax[i] != cipher.ax[i] || test.bx[i] != cipher.bx[i]){
                cout << "ERIIR : " << i  << endl;
                for(int j = 0;j<10;j++){
                int tmp = i + j - 5;
                if(tmp < 0 || tmp >= N)
                    continue;
                cout << tmp << endl;
                cout << test.ax[tmp] << " | " << test.bx[tmp] <<  endl;
                cout << cipher.ax[tmp] << " | " << cipher.bx[tmp] <<  endl << endl;

                }
                break;
            }
        }
        return ac->scheme_ptr->decrypt(*(ac->secretKey), cipher);
    }

    ZZ HEAANUtils::char_arrToNumber(char* str, int len)
    {
        ZZ number = conv<ZZ>((int)str[0] + 128);
        for(long i = 1; i < len; i++)
        {
            number *= 256;
            number += conv<ZZ>((int)str[i] + 128);
        }
        return number;
    }

    char* HEAANUtils::numberTochar_arr(ZZ num, int* lenptr)
    {
    long len = ceil(log(num)/log(ZZ(256)));
    char* str = (char*)malloc(sizeof(char) * len);
    for(long i = len - 1; i >= 0; i--)
    {
        str[i] = conv<int>((num % 256) - 128);
        num /= 256;
    }
    cout << endl;
    *lenptr = len;
    return str;
    }
}