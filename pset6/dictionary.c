/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// define a node type
typedef struct node
{
	char word[LENGTH+1];
	struct node* next;

}
node;

// define a variable to count the words loaded from the dictionary
int words;

// define a hashtable
node* hashtable[HASHTABLE_SIZE] = {NULL}; 

// hashing function
int hashing_function(char* word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // copy the word ( because it is constant type and cannot be used)
    int l = strlen(word);
    char *copy = malloc(l);
    
    // copy the characters and make them lower case
    for (int i = 0; i < l; i++)
        copy[i] = tolower(word[i]);
    
    // add the end of string character
    copy[l] = '\0';

    //  hash the word
    int index = hashing_function(copy);

    // check the table for a node at that index
    node* entry = hashtable[index];
    if (entry)
    {
        // point a cursor node to the head node
        node* cursor = entry;

        // loop through the nodes while a next pointer isn't null
        while (cursor->next != NULL)
            {
                if (strcmp(copy, cursor->word) == 0)
                    return true;

                cursor = cursor->next;
            };

        if (strcmp(copy, cursor->word) == 0)
    		return true;

			cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the input dictionary file
    FILE* fp = fopen(dictionary, "r");

    // check for an unsuccessful open
    if (fp == NULL)
    	{
    		printf("Could not open %s.\n", dictionary);
    		return false;
    	}
    	
    // set a buffer to store an output word of length = LENGTH + 1 for null terminator
    char buffer[LENGTH+2];

    // loop through the dictionary until a null character
    while (fgets(buffer, sizeof(buffer), fp))
    {

        // overwrite the \n with \0
        buffer[strlen(buffer) - 1] = '\0';

    	// create a temporary node
    	node* temp = malloc(sizeof(node));

    	// set the node's pointers to the word and to the next node
        // copies buffer's contents into the location of temp's word pointer
    	strncpy(temp->word, buffer, LENGTH + 1);
    	temp->next = NULL;

    	// hash the word to get the index
    	int index = hashing_function(buffer);
    	// printf("%i" %(index));

    	// if the hashtable contains no value at that index then assign the temp node there
        // (the entry takes the pointers of temp)
    	if (hashtable[index] == NULL)
    	{
    		hashtable[index] = temp;
    	}

    	// otherwise append the node to the end of the linked list
    	else
    	{
    		// point a cursor node to the index, (i.e the first entry in the linked list)
    		node* cursor = hashtable[index];

    		// loop through the nodes while the next pointer isn't null
    		while (cursor->next != NULL)
    		{
    			cursor = cursor->next;
    		}

    	// the end of the linked list has been found, append the node by changing the shared pointer
    		cursor->next = temp;
    	}
        words++;
    }

    // close the file
    fclose(fp);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return the global variable that was updated in load
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // for each node in the hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // check the table for a node at that index
        node* cursor = hashtable[i];
        if (cursor)
        {
            // create a temporary node to save the position of the next node
            node* temp = cursor->next;

            // free the current node
            free(cursor);

            // move the cursor to the next node
            cursor = temp;
        }
    }
    
    return true;
}





