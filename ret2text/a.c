#include <stdio.h>
#include <stdlib.h>

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void)
{
    char buf[40];
    init();
    puts("welcome to NEXctf!");
    gets(buf);
    return 0;
}

void backdoor(void)
{
    puts("hacker!");
    system("/bin/sh");
}