#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_KEY_LENGTH 16 // AES 密钥长度（128位）
#define AES_BLOCK_SIZE 16  // AES 块大小（128位）

// AES 加密函数
void aes_encrypt(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, AES_KEY_LENGTH * 8, &encryptKey);
    AES_encrypt(plaintext, ciphertext, &encryptKey);
}

// 打印密文
void print_ciphertext(const unsigned char *ciphertext, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("0x%02X, ", ciphertext[i]);
    }
    printf("\n");
}

// 填充数据到 AES 块大小
void pad_plaintext(unsigned char *text, size_t length) {
    size_t padding = AES_BLOCK_SIZE - (length % AES_BLOCK_SIZE);
    for (size_t i = length; i < length + padding; i++) {
        text[i] = (unsigned char)padding; // 用填充值填充
    }
}

int main() {
    unsigned char key[AES_KEY_LENGTH] = "thisisaverysecre"; // AES 密钥
    unsigned char plaintext[AES_BLOCK_SIZE * 4]; // 增加明文缓冲区大小，支持多个块
    unsigned char ciphertext[AES_BLOCK_SIZE]; // 密文缓冲区

    // 输入 flag
    printf("Enter the flag to encrypt: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn((char *)plaintext, "\n")] = 0; // 移除换行符

    size_t plaintext_length = strlen((char *)plaintext);

    // 填充明文到 AES 块大小
    pad_plaintext(plaintext, plaintext_length);
    
    // 进行多个 AES 块加密
    for (size_t i = 0; i < (AES_BLOCK_SIZE + plaintext_length - 1) / AES_BLOCK_SIZE; i++) {
        aes_encrypt(key, plaintext + i * AES_BLOCK_SIZE, ciphertext);
        printf("Encrypted block %zu: ", i + 1);
        print_ciphertext(ciphertext, AES_BLOCK_SIZE);
    }

    return 0;
}
