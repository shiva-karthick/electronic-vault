#include <stdio.h>
#include <stdlib.h>

unsigned int concatenate(unsigned x, unsigned y);
unsigned int security_key_code_1;
unsigned int security_key_code_2;
unsigned int security_key_code_result;

int main()
{
    security_key_code_1 = concatenate(1, 2);
    security_key_code_2 = concatenate(4, 3);
    security_key_code_result = concatenate(security_key_code_1, security_key_code_2);
    printf("%d", security_key_code_result);
    return 0;
}

unsigned int concatenate(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}