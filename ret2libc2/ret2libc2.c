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
    puts("我被他定住了，请帮帮我");

    ssize_t inputRead = read(STDIN_FILENO,word,272);
    if (inputRead == -1) {
        perror("读取输入失败");
        return EXIT_FAILURE;
    }
    puts(word);
    puts("找到你了，看招!");
    printf("%p\n",&printf);
inputRead = read(STDIN_FILENO,word,272);
    if (inputRead == -1) {
        perror("读取输入失败");
        return EXIT_FAILURE;
    }

    return 0;
}
