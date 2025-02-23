#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t uint64;

int main() {
    uint64 max_chunks = 2048*8;
    uint64* a = (uint64*)malloc(sizeof(uint64)*2*(max_chunks+1));
    const uint64 LSD = (~((uint64)(0)))<<(sizeof(uint64)*8-1);

    a[0]=1;

    uint64 tmp;
    uint64 chunks = 1;
    for (uint64 j = 0; j < 200000; ++j) {
        for (uint64 i = 0; i < chunks*2; i+=2) {
            if (a[i]>=LSD && a[i+1]>=LSD) {
                for (uint64 x = 2; (a[i+1+x]++)<0; x+=2) {}
            }
            tmp = a[i];
            a[i] += a[i+1];
            a[i+1] = tmp;
        }
        if (a[chunks*2+1]) {a[chunks*2+1]=0; a[chunks*2]=1; chunks++;}
    }

    bool leading_null = true;
    for (int i = chunks*2-2; i>=0; i-=2) {
        if (a[i] || !leading_null) {
            printf("%lu", a[i]);
            leading_null = false;
        }
    }
    printf("\n");

    free(a);
}
