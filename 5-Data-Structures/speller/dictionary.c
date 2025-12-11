// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
#define N 1125 // 25 alpabet letters * 45 max word LENGTH

// Hash table
node *table[N];

int word_count = 0;

// Lowercases a string
void lower(char *string)
{
    while(*string)
    {
        *string = tolower((unsigned char)*string);
        string++;
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char tmp_word[LENGTH+1];
    // Copy the contents of 'word' into 'tmp_word'
    strcpy(tmp_word, word);
    // lowercase the word
    lower(tmp_word);
    
    node *temp = table[hash(tmp_word)];

    while (temp != NULL)
    {
        if (strcmp(temp->word, tmp_word) == 0)
        {
            return true;
        }
        temp = temp->next;
    } 
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long char_sum = 0;
    for (int i = 0; word[i] != '\0'; i++) // itirating until reaching the end of string
    {
        char_sum += tolower(word[i]);
    }

    return char_sum % N; // to make sure the hash is always in the range of buckets N
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    // Handle no dictionary file
    if (file == NULL) 
    {
        return false;
    }

    // initialaze a buffer
    char word[LENGTH+1];

    while(fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory fo new node 
        node *n = malloc(sizeof(node));
        // Handle memory allocation error
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Get the hash of the word
        int x = hash(word);
        // copy the word to the node
        strcpy(n->word, word);
        // set the current node to point to the head of the list in that index in table
        n->next = table[x];
        // set the current node as the head of the list
        table[x] = n;
        // increment the number of words loaded by one 
        word_count++;
    }

    fclose(file); // closing the dictionary file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *list = table[i];
        while(list != NULL)
        {
            node *temp = list->next;
            free(list);
            list = temp;
        }
        table[i] = NULL;
    }
    return true;
}

