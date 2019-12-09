#ifndef _UTILITY
#define _UTILITY

//vm code
#define EXITT 0x00
#define PUSHI 0x8
#define PUSHC 0x12
#define PUSHL 0x15
#define ADD 0x21
#define ADDC 0x26
#define POP10 0x28
#define SUB 0x30
#define COPY 0X34
#define ZERO 0x38
#define Ddouble 0x42
#define INC 0x51
#define DEC 0X52
#define CHANGE 0x56
typedef struct {
    long long *sp;
    long long *bp;
    unsigned int len;
}Stack;

void dd_init();
int stack_vm(char *code, long long* ip, Stack *p, long long* flag);
int read_until(char *buff, int size, char end_char);
int stack_pushl(Stack *p, long long num);
int stack_addc(Stack *p, char num);
int stack_add(Stack *p);
int stack_pop10(Stack *p, long long* flag);
int stack_sub(Stack *p, char num);
int stack_pushi(Stack *p, int num);
int stack_pushc(Stack *p, char num);
int stack_copy(Stack *p);
int stack_zero(Stack *p);
int stack_double(Stack *p);
int stack_inc(Stack *p);
int stack_dec(Stack *p);
int stack_change(Stack *p ,int a);

#endif /* _UTILITY */