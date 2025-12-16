#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>

void aes_encrypt(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext);
void aes_decrypt(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext);

#endif // ENCRYPTION_H
