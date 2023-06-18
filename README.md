#OpenSourceAssignment5
오픈소스 과제5 : mysql +  HEAAN, 데이터 베이스 관리 프로그램 By Using GITHUBFLOW

## HOW TO COMPILE
g++ -g3 /OpenSourceAssignment5/*.cpp /OpenSourceAssignment5/src/*.cpp -o /OpenSourceAssignment5/run.dg -L /usr/local/lib ../../HEAAN/HEAAN/lib/libHEAAN.a -l ntl -l gmp -I ../../HEAAN/HEAAN/lib/src -I /usr/include/mysql -I /usr/local/include/NTL -L /usr/lib/x86_64-linux-gnu -l mysqlclient

## HOW TO USE
./run.dg

CREATE DB, TABLE, INSERT VALUE, SELECT * is available

but, make account, encrypt, and decrypt is not yet...



## dependency
<https://libntl.org/>

<https://github.com/snucrypto/HEAAN>

<https://gmplib.org/>

<https://github.com/mysql>
