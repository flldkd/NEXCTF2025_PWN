#include <stdio.h>
#include <unistd.h>
#include <locale.h>


void init()
{   
    setlocale(LC_ALL, "zh_CN.UTF-8");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}
void menu()
{
    puts("1.查看对手bp\n2.询问教练意见\n3.告诉the shy你的选择\nyour choice >>");
}
void ban()
{
    puts("我们不用ban The shy的英雄，我能应付他");
}

void pick()
{
    puts("我是Daney，我建议选择英雄能打出execve连招的英雄");
}

void combo()
{
    char code[100];

    puts("我是IG The shy，请告诉我如何操作");
    read(0, code, 100);
    (*(void (*)())code)();
}

int main()
{
    init();

    int choice;
    puts("你好召唤师，我是IG The shy，你能帮我击败T1 Doran吗");
    while(1){
        scanf("%d",&choice);
        switch(choice){
            case 1:
                ban();
                break;
            case 2:
                pick();
                break;
            case 3:
                combo();
                break;
        }

    }
    return 0;
}
