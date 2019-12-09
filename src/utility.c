#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utility.h"



void dd_init()
{
    setvbuf(stdin, 0,_IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
    alarm(100);
}

int read_until(char *buff, int size, char end_char)
{
    int res, i;
    for(i = 0; i < size; ++i){
        res = read(0, buff + i, 1);
        if(res != 1){
            exit(-1);
        }
        if(buff[i] == end_char){
            buff[i] = '\0';
            return i;
        }
    }

    buff[size - 1] = '\0';
    return size - 1;
}

int stack_pushl(Stack *p, long long num)
{
    if(p -> len < 10)
    {   
        p -> sp --;
        *(p->sp) = num;
        p -> len ++;
        return 1;
    }
    else
    {
        exit(0);
    }
}

int stack_addc(Stack *p, char num)
{
    *(p -> sp) = *(p -> sp) + num;
    return 1;
}

int stack_add(Stack *p)
{
    *(p -> sp) = *(p -> sp - 1) + *(p -> sp);
    *(p -> sp - 1) = 0;
    return 1;
}

int stack_pop10(Stack *p, long long *flag)
{
    if(p -> len > 0 || *flag < 2)
    {
        p -> sp = p -> sp + 10;
        p -> len = p -> len - 10;
        *flag = *flag + 1;
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int stack_sub(Stack *p, char num)
{
    *(p -> sp) = *(p -> sp) - num;
    return 1;
}

int stack_pushi(Stack *p, int num)
{
    if(p->len < 10)
    {
        p -> sp --;
        *(p->sp) = num;
        p -> len ++;
        return 1; 
    }
    else
    {
        exit(0);
    }
    
}
int stack_pushc(Stack *p, char num)
{
    if(p->len < 10)
    {
        p -> sp --;
        *(p->sp) = num;
        p -> len ++;
        return 1; 
    }
    else
    {
        exit(0);
    }
    
}

int stack_copy(Stack *p)
{
    p ->len ++;
    p -> sp = p->sp - 1;
    *(p->sp) = *(p->sp + 1);
    *(p->sp + 1) = 0;
    return 1;
   
}

int stack_zero(Stack *p)
{
    *(p->sp + 1) = 0;
    return 1;
}

int stack_double(Stack *p)
{
    if(p -> len < 10)
   { 
    p->len ++;
    p -> sp --;
    *(p->sp) = 2*((*(p->sp + 1)) & 0xffffff);
    return 1;
    }
    else
    {
        exit(0);
    }
    
}

int stack_inc(Stack *p)
{
    *(p ->sp) = *(p ->sp) + 1 ;
    return 1;
}

int stack_dec(Stack *p)
{
    *(p ->sp) = *(p ->sp) - 1;
    return 1;
}

int stack_change(Stack *p ,int a)
{
    *(p -> sp) = a;
    return 1;
}
int stack_vm(char *code, long long *ip, Stack *p, long long *flag)
{
    long long s[10] = {0};
    p->sp = s;
    p->len = 10;
    p->bp = p->sp + 10;
    while(*(code + *ip))
    {
        switch (*(code + *ip))
        {
        case EXITT:
            *ip = 0;
            return 1;
            break;

        case PUSHL:
            *ip = *ip + 1;
            stack_pushl(p ,*(code + (*ip)));
            *ip = *ip + 8;
            break;
        case PUSHI:
            *ip = *ip + 1;
            stack_pushi(p ,*(code + (*ip)));
            *ip = *ip + 4;
            break;

        case PUSHC:
            *ip = *ip + 1;
            stack_pushc(p ,*(code + (*ip)));
            *ip = *ip + 1;
            break;

        case ADD:
            stack_add(p);
            (*ip) ++;
            break;
        
        case ADDC:
            *ip = *ip + 1;
            stack_addc(p, *(char *)(code + (*ip)));
            (*ip) ++;
            break;
            
        case POP10:
            *ip = *ip + 1;
            if(!stack_pop10(p, flag))
            {
                exit(0);
            }
            break;

        case SUB:
            *ip = *ip + 1;
            stack_sub(p,*(char *)(code + *ip));
            (*ip) ++;
            break;


        case COPY:
            (*ip) ++;
            stack_copy(p);
            break;

        case ZERO:
            (*ip) ++;
            stack_zero(p);
            break;

        case Ddouble:
            stack_double(p);
            (*ip) ++;
            break;
        case INC:
            stack_inc(p);
            (*ip) ++;
            break;
        case DEC:
            stack_dec(p);
            (*ip) ++;
            break;
        case CHANGE:
            (*ip) ++;
            stack_change(p, *(int*)(code + *ip));
            *ip = *ip + 4;
            break;
        default:
            exit(0);
            break;
        }
    }
    return 1;
}
