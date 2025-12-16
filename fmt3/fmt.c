#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char buf[256];

void Tsukuyomi(){
    system("/bin/sh");
}

void init()
{   
    setlocale(LC_ALL, "zh_CN.UTF-8");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}





int main()
{
    init();
    int inputRead;
    printf("他要使用月读了，这是最后的机会，我看到了:%p",&inputRead);
    inputRead = read(STDIN_FILENO,buf,256);
    printf(buf);
    exit(0);
    return 0;
}
