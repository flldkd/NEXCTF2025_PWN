#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <seccomp.h>
#include <linux/seccomp.h>

void init()
{       
    scmp_filter_ctx ctx;
    ctx = seccomp_init(SCMP_ACT_ALLOW);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
    seccomp_load(ctx);
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
    puts("我们用沙箱ban掉了The shy的英雄，我想这次应该能打败他了");
}

void pick()
{
    puts("我是Daney，这次英雄被ban掉了，还有没有别的操作能赢呢？");
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
