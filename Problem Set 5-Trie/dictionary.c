// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    struct node *parent;
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;
int count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    root->parent = NULL;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }
    
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }
    
    // Buffer for a word
    char word[LENGTH + 1];
    
    node *source = root;
    node *temp = source;
    int hash = 0;
    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        for (int i = 0; i < strlen(word); i++) {
            hash = tolower(word[i]) % 26;
            if (!isalnum(word[i])) { hash = 26; }
            temp = source->children[hash];
            if (temp == NULL) {
                node *new_row = malloc(sizeof(node));
                for (int j = 0; j < N; j++) {
                    new_row->children[j] = NULL;
                }
                //                printf("id added: %d\n", id);
                new_row->is_word = false;
                new_row->parent = source;
                temp = new_row;
                source->children[hash] = temp;
            }
            source = temp;
        }
        source->is_word = true;
        source = root;
        count++;
    }
    
    // Close dictionary
    fclose(file);
    
    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *point = root;
    for (int i = 0; i < strlen(word); i++) {
        int hash = tolower(word[i]) % 26;
        //        if word[i] == '''
        if (!isalnum(word[i])) { hash = 26; }
        point = point->children[hash];
        if (point == NULL) {
            return false;
        }
    }
    if (point->is_word) {
        //        printf("%s AHA PİÇ", word);
    }
    return point->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *current = root;
    while (current != NULL) {
        bool hasChild = false;
        for (int i = 0; i < N; i++) {
            if (current->children[i] != NULL) {
                current = current->children[i];
                hasChild = true;
                break;
            }
        }
        if (!hasChild) {
            if (current->parent != NULL) {
                for (int i = 0; i < N; i++) {
                    // Why the heck free(current) doesn't work?
                    if (current == current->parent->children[i]) {
                        //                        printf("id removed: %d\n", current->parent->children[i]->id);
                        current->parent->children[i] = NULL;
                        free(current->parent->children[i]);
                    }
                }
            }
            current = current->parent;
        }
    }
    free(root);
    //    printf("MERABALAR AQ!\n %d---%d", appCount, delCount);
    return true;
}
