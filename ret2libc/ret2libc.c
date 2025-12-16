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

int main()
{
    init();
    char word[16];
    puts("我看到了！他躲在雾气的西南方：");
    printf("%p\n",&printf);
    ssize_t inputRead = read(STDIN_FILENO,word,272);
    if (inputRead == -1) {
        perror("读取输入失败");
        return EXIT_FAILURE;
    }

    return 0;
}
