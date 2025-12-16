#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <openssl/aes.h>

#define NUM_ROUNDS 4 // 定义总关卡数
#define BUFFER_SIZE 256 // 定义缓冲区大小以存储用户输入
#define FLAG_SIZE 256 // 定义flag大小
#define AES_KEY_LENGTH 16 // AES 密钥长度（128位）

// 全局变量：目标字符串
char target_string[] = "Pwn_I_love_you"; // 目标字符串定义在 BSS 段

// 加密后的flag（示例密文）
unsigned char flag_encrypted[FLAG_SIZE] = {0x40, 0x3B, 0x5A, 0x85, 0x6E, 0x1C, 0x05, 0x81, 0x1F, 0xA1, 0xC3, 0xB6, 0xE9, 0x68, 0xFC, 0xA2}; // NOTE: 你可以根据实际的 AES 加密结果进行替换

// 成功提示函数
void success_function(int round) {
    printf("Round %d Success!\n", round);
}

// AES 加密函数
void aes_encrypt(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, AES_KEY_LENGTH * 8, &encryptKey);
    AES_encrypt(plaintext, ciphertext, &encryptKey);
}

// AES 解密函数
void aes_decrypt(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext) {
    AES_KEY decryptKey;
    AES_set_decrypt_key(key, AES_KEY_LENGTH * 8, &decryptKey);
    AES_decrypt(ciphertext, plaintext, &decryptKey);
}

// 第一关：随机数比较
int compare_with_random() {
    uint64_t random_value = rand() % UINT64_MAX; // 生成一个随机数
    uint64_t input_value; // 用于存储用户输入的值

    // 在内联汇编中将随机数存储到 r12
    asm volatile ("mov %0, %%r12" : : "r" (random_value));

    printf("Round 1: A random number has been generated.\nIt's in the r12.Can you find it and please enter it as a hexadecimal integer value (e.g., 0x1A2B3C4D5E6F): ");
    
    // 使用%lx读取unsigned long格式，这通常适用于 uint64_t
    scanf("%lx", (unsigned long *)&input_value); // 获取用户输入

    // 在内联汇编中比较输入值与随机数
    asm volatile (
        "cmp %%r12, %[input];"      // 比较 r12 和输入值
        "je success;"                // 如果相等，跳转到成功处理
        "jmp exit;"                  // 如果不相等，跳转到退出程序
        "success:"                   // 成功标签
        :                            // 输出操作数为空
        : [input] "r" (input_value) // 输入操作数
        : "%r12"                    // 指明 r12 寄存器可能被修改
    );

    // 调用成功函数，如果第一关通过
    success_function(1); // 直接调用成功函数
    // 返回成功状态
    return 1; // 返回1表示第一关通过
}

// 第二关：字符串比较
void compare_strings() {
    char input_string[BUFFER_SIZE]; // 用于存储用户输入字符串

    printf("Round 2: The address of the target string is: %p\n", (void *)target_string);
    
    // 获取用户输入
    printf("Enter the string to match the target string: ");
    scanf("%s", input_string); // 读取用户输入字符串

    // 比较输入值与目标字符串
    if (strcmp(input_string, target_string) == 0) {
        success_function(2); // 输入匹配，调用成功函数
    } else {
        printf("Incorrect! The input does not match the target string.\n");
        exit(1); // 输入不匹配，退出程序
    }
}

// 第三关：数字比较
void compare_numbers() {
    int num1 = 42; // 第一个变量
    int num2 = 24; // 第二个变量，与第一个变量不同

    printf("Round 3: Comparing two numbers,if they are same you can pass game3\n");

    // 提示用户进行尝试性修改
    printf("Address of num1: %p\n", (void *)&num1);
    printf("Value of num2: %d\n", num2);
    printf("now try to change one of them to make thme same.\n");
    // 比较
    if (num1 == num2) {
        success_function(3); // 如果相等，调用成功函数
    } else {
        printf("The two numbers are not equal. You have failed Round 3.\n");
        exit(1); // 输入不匹配，退出程序
    }
}

// 第四关：提示flag在堆空间中
void reveal_flag() {
    // 申请堆空间
    unsigned char *heap_flag = (unsigned char *)malloc(FLAG_SIZE);
    if (heap_flag == NULL) {
        printf("Failed to allocate memory.\n");
        exit(1); // 内存分配失败，退出程序
    }

    unsigned char key[AES_KEY_LENGTH] = "thisisaverysecre"; // AES 密钥

    // 解密并存储在堆中
    aes_decrypt(key, flag_encrypted, heap_flag);

    // 提示信息
    printf("Round 4: The flag has been decrypted and stored in heap memory.\n");
    printf("The flag is stored in heap memory. try to find it.\n");

    // 输出 flag
    //printf("Flag: %s\n", heap_flag); // 可以解注释以显示flag内容

    // 释放堆内存
    free(heap_flag); // 成功后释放堆内存
}

int main() {
    // 设置随机数种子
    srand(time(NULL));

    // 第一关
    if (!compare_with_random()) { // 如果第一关没有通过
        printf("You failed at Round 1.\n");
        exit(1); // 退出程序
    }
    
    // 第二关
    compare_strings(); // 调用字符串比较

    // 第三关
    compare_numbers(); // 调用数字比较

    // 第四关
    reveal_flag(); // 调用输出flag的功能

    // 所有关卡结束，输出提示
    printf("Congratulations! You have passed all rounds. Welcome to PWN\n");

    return 0; // 程序正常结束
}
