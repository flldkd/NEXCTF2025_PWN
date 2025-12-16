#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void)
{
    int pwd;
    int ans;
    char buf[40];
    int seed;


    init();
    seed = time(0);
    srand(seed);
    pwd=rand()%100+1;

    puts("welcome to NEXctf!");
    puts("There is a question");
    puts("Please give me your anwser");
    scanf("%d",ans);
    if(ans == pwd){
        gets(buf);       
    }
    puts("bye bye~");
    return 0;
}

void backdoor(void)
{
    puts("hacker!");
    system("/bin/sh");
}