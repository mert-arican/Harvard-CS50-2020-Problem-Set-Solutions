// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH  + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
//    printf("check\n");
    int hashValue = hash(word);
    for (node *head = table[hashValue]; head != NULL; head = head->next) {
        if (strlen(head->word) == strlen(word)) {
            if (strcasecmp(head->word, word) == 0) {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
//    printf("hash\n");
    return ((int) tolower(word[0])) % 26;
}

int wordCount = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    
    if (f == NULL) {
        return false;
    }
    
    for (int i = 0; i < N; i++) {
        node *point = malloc(sizeof(node));
        point->next = NULL;
        strcpy(point->word, " ");
        /* If I don't initialize then terrible unguessable ridicolusly enormous errors occur. Please initialize your node fully before assigning them to an array. */
        table[i] = point;
    }
        
    while (true) {
        char word[LENGTH+1];
        
        if (fscanf(f, "%s", word) == EOF) {
            break;
        }
        
        wordCount++;
        
        node *wordNode = malloc(sizeof(node));
        if (wordNode == NULL) { return false; }
        strcpy(wordNode->word, word);
        
        int hashValue = hash(word);
        if (table[hashValue] == NULL) {
            table[hashValue] = wordNode;
        } else {
            wordNode->next = table[hashValue];
            table[hashValue] = wordNode;
        }
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
//    printf("size\n");
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
//    printf("unload\n");
//        for (int i = 0; i < N; i++) {
//            for (node *list = table[i]; list == NULL; list = list->next) {
//                node *tmp = list->next;
//                free(list); list = tmp;
//               printf("PPP\n");
//            }
//        }
    
    for (int index = 0; index < N; index++) {
        node *list = table[index];
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    
    return true;
}
