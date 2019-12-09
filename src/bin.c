#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

Stack mystack;
char code[0x100] = {0};
long long  ip = 0;
long long flag = 0;

int main()
{
    dd_init();
    read_until(code, 0x100, '\n');
    stack_vm(code, &ip, &mystack, &flag);
    exit(0);
}
