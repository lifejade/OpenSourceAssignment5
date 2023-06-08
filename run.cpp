#include <string>
#include <cmath>
#include </HEAAN/HEAAN/src/HEAAN.h>

using namespace std;
using namespace heaan;



int main(){
    Ring ring;
	SecretKey secretKey(ring);
	Scheme scheme(secretKey, ring);
    cout << secretKey.sx << endl;
}