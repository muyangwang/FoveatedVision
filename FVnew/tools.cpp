#include "tools.h"

#include<cstdlib>

int pow(int a, int b) {
    if (b == 0) return 1;
    int res = 1;
    while (b != 0) {
        res *= a;
        --b;
    }
    return res;
}

int randomNumberGen(int a) {
    return rand() % a;
}
