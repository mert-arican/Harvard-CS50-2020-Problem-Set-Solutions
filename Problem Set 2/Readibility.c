//
//  main.c
//  Problem Set 2
//
//  Created by Mert Arıcan on 13.10.2019.
//  Copyright © 2019 Mert Arıcan. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

float per100Words(float wordCount, float x) {
    return (float) 100.0 * (float) x / (float) wordCount;
}

int getTotalNumberOfLetters(char *text) {
    int total = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            total++;
        }
    }
    return total;
}

int getTotalNumberOfWords(char *text) {
    int total = 1;
    char space = ' ';
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == space) {
            total++;
        }
    }
    return total;
}

int getTotalNumberOfSentences(char *text) {
    int total = 0;
    char enders[] = "?!.";
    for (int i = 0; i < strlen(text); i++) {
        if (strchr(enders, text[i])) {
            total++;
        }
    }
    return total;
}

int readability(char *text) {
    float letterCount = getTotalNumberOfLetters(text);
    float wordCount = getTotalNumberOfWords(text);
    float sentenceCount = getTotalNumberOfSentences(text);
    float L = per100Words(wordCount, letterCount);
    float S = per100Words(wordCount, sentenceCount);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index - floorf(index) > (ceilf(index) - index) ? (int) ceilf(index) : (int) floorf(index) ;
}

int main(int argc, const char * argv[]) {
    printf("Enter a text to compute it's readibility \n");
    char *text = malloc(sizeof(char)*1000);
    fgets(text, 1000, stdin);
    printf("%i\n", readability(text));
    return 0;
}
