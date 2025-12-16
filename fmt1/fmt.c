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
    char buffer[100];
    int flagfd;
    char word[25];
    char ans[40];
    char *str=&buffer;

    flagfd = open("secret.txt", O_RDONLY);
    if (flagfd == -1) {
        perror("无法打开文件");
        return EXIT_FAILURE;
    }

    ssize_t bytesRead = read(flagfd, buffer, sizeof(buffer) - 1);

    if (bytesRead == -1) {
        perror("读取文件失败");
        close(flagfd);
        return EXIT_FAILURE;
    }

    buffer[bytesRead] = '\0';

    if (close(flagfd) == -1) {
        perror("关闭文件失败");
        return EXIT_FAILURE;
    }

    puts("请帮助卡卡西使用写轮眼");
    ssize_t inputRead = read(STDIN_FILENO,word,25);
    if (inputRead == -1) {
        perror("读取输入失败");
        return EXIT_FAILURE;
    }
    printf(word);

    puts("告诉我敌人的招式");
    inputRead = read(STDIN_FILENO,ans,30);
    if (inputRead == -1) {
        perror("读取输入失败");
        return EXIT_FAILURE;
    }

    if (strcmp(buffer, ans) == 0) {
        printf("你看穿了宇智波鼬的招式!\n");
        system("/bin/sh");
    } else {
        printf("你中了宇智波鼬的月读\n");
    }
    return 0;
}
