#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>
 
#define NUMLETTERS 26
#define BUFSIZE 4096
#define KEYS "bacon"
 
char *cipher(char *user_password){
    char sign = 1; 
    bool encrypt = true;
    int opt;

 
    // Converting Key
    char const *const restrict key = KEYS;
    size_t const keylen = strlen(key);
    char shifts[keylen];
 
    char const *restrict plaintext = NULL; 
    for (size_t i = 0; i < keylen; i++) {
        char const charcase = (isupper(key[i])) ? 'A' : 'a';
        // If decrypting, shifts will be negative.
        // This line would turn "bacon" into {1, 0, 2, 14, 13}
        shifts[i] = (key[i] - charcase) * sign;
    }
 
     plaintext = user_password;
 
    size_t const plainlen = strlen(plaintext);
 
    char* const restrict ciphertext = calloc(plainlen + 1, sizeof *ciphertext);
    for (size_t i = 0, j = 0; i < plainlen; i++) {
        // Skip non-alphabetical characters
        if (!(isalpha(plaintext[i]))) {
            ciphertext[i] = plaintext[i];
            continue;
        }
        // Check case
        char const charcase = (isupper(plaintext[i])) ? 'A' : 'a';
        // Wrapping conversion algorithm
        ciphertext[i] = ((plaintext[i] + shifts[j] - charcase + NUMLETTERS) % NUMLETTERS) + charcase;
        j = (j+1) % keylen;
    }
    ciphertext[plainlen] = '\0';
 	return ciphertext;
    free(ciphertext);
    // Silence warnings about const not being maintained in cast to void*
    free((char*) plaintext);
}
