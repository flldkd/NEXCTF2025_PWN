#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void init()
{   
    setlocale(LC_ALL, "zh_CN.UTF-8");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}
void Tsukuyomi(){
    system("/bin/sh");
}

void func(){
    char word[25];
    ssize_t inputRead;
    while(1){
        puts("请帮我使用月读来控制卡卡西");
        memset(word,0,sizeof(word));
        inputRead = read(STDIN_FILENO,word,25);
        if (inputRead == -1) {
            perror("读取输入失败");
            return EXIT_FAILURE;
        }
        if (strcmp(word, "1") == 0) {
            printf("您选择退出！\n");
            break; // 退出循环
        }
        printf(word);
    }
}

int main()
{
    init();
    func();

    return 0;
}
