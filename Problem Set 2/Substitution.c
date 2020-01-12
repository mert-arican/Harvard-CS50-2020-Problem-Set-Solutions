//
//  Substitution.c
//  Problem Set 2
//
//  Created by Mert Arıcan on 13.10.2019.
//  Copyright © 2019 Mert Arıcan. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ALPHABET[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

int isValidKey(char * key) {
    if (strlen(key) != 26) {
        printf("Key must be length 26.\n");
        return 0;
    }
    for (int i = 0; i < 26; i++) {
        if (isalpha(key[i]) == 0) {
            printf("There is a non-character element.\n");
            return 0;
        }
    }
    for (int i = 0; i < 26; i++) {
        char c = key[i];
        for (int j = 0; j < 26; j++) {
            if (c == key[j] && i != j) {
                printf("Dublicate character error.\n");
                return 0;
            }
        }
    }
    return 1;
}

int findIndex(char c, char *string) {
    for (int i = 0; i < strlen(string); i++) {
        if (tolower(string[i]) == tolower(c)) {
            return i;
        }
    }
    return 0;
}

void cipher(char *plaintText, char *key, char *cipherText) {
    for (int i = 0; i < strlen(plaintText); i++) {
        int index = findIndex(plaintText[i], alphabet);
        cipherText[i] = isupper(plaintText[i]) ? toupper(key[index]) : key[index];
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    char key[27];
    char plainText[1000];
    printf("Enter key: \n");
    scanf("%s", key);
    if (!isValidKey(key)) {
        return 1;
    }
    printf("Enter a text: \n");
    scanf("%s", plainText);
    char cipherText[strlen(plainText)];
    cipher(plainText, key, cipherText);
    printf("Plain Text: %s\n", plainText);
    printf("Cipher Text: %s\n", cipherText);
    return 0;
}
