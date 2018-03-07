/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <stdint.h>
#include <strings.h>

#include "dictionary.h"

//int count = 0;
/*int getCount()
{
    return count;
}*/

int count = 0;



typedef struct node
        {
            char word[LENGTH + 1];        
            struct node* next;
        }
        node;

node* HASHTABLE_SIZE[65536];

 int hash_it(char* needs_hashing)
    {
        unsigned int hash = 0;
        for (int i=0, n=strlen(needs_hashing); i<n; i++)
            hash = (hash << 2) ^ needs_hashing[i];
        return hash % sizeof(HASHTABLE_SIZE);
    }
//Hash Function thanks to /u/staffdelipity 's husband

/**
 * Returns true if word is in dictionary else false.dddd
 */
bool check(const char *word)
{
    const char * xyz = word;
    // char* def = malloc(sizeof(abc));

    //int abc = strlen(word + 1);
    //char* def = malloc(sizeof(abc));
    //def[strlen(word + 1)] = malloc(sizeof(abc));
    //char* def = malloc(sizeof(char) * LENGTH);
    //strcpy(def->word, word);
    
    //const char *stuff;
    
    char new_word[LENGTH+1];
            for(int i = 0; i < LENGTH+1; i++)
                    new_word[i] = tolower(xyz[i]);

    //for (int z = 0; z > strlen(word); z++) 
    //{
      //  if(isupper(word[z]))
        //     def[z] = tolower(word[z]);
         // else
           // def[z] = word[z];
    //}

//stuff = word;

    // TODO
    
   // int x = hash_it(stuff);
    int x = hash_it(new_word);
    
    node *cursor = HASHTABLE_SIZE[x];
    
    if (HASHTABLE_SIZE[x] == NULL)
        { 
             return false;
        }
    
    while (cursor != NULL)
    {
        //int x = hash_it(word);
       // printf("def: %s", def);
        printf("cursoe -> word: %s", cursor->word);
        if (strcasecmp(new_word, cursor -> word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    
        
    }
    
    
   //free(def);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */

bool load(const char *dictionary)
{
    // TODO
   // int count = 0;
   
     FILE* file = fopen(dictionary, "r");
     if (file == NULL)
     {
         printf("Cannot Load Dictionary\n");
         return false;
     }
      
     for (int i = 0; i < 65536; i++)
        {

            HASHTABLE_SIZE[i] = NULL;
        }
     
    // typedef struct node
      //  {
        //    char word[LENGTH + 1];        
          //  struct node* next;
        //}
        //node;

    //node *HASHTABLE_SIZE[65536];  

//    int hash_it(char* needs_hashing)
  //  {
    //    unsigned int hash = 0;
      //  for (int i=0, n=strlen(needs_hashing); i<n; i++)
        //    hash = (hash << 2) ^ needs_hashing[i];
        //return hash % HASHTABLE_SIZE;
    //}


    char* string = malloc(sizeof(char) * LENGTH);
    while (fscanf(file, "%s", string) != EOF)
    {
       // string word;
       //count++;
       printf("%i\n", count);
        node* new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                unload();
                return false;
            }
        strcpy(new_node->word, string);
        //count++;
        //int a = hash_it(new_node->word); 
        //{
        
        if (HASHTABLE_SIZE[hash_it(new_node->word)] == NULL)
        {
            HASHTABLE_SIZE[hash_it(new_node->word)] = new_node;
            //count++;
        }
        else
        {
            new_node->next = HASHTABLE_SIZE[hash_it(new_node->word)];
            HASHTABLE_SIZE[hash_it(new_node->word)] = new_node;
            //count++;
        }
        free(string);
        
        //}
    
    return true;    
    }
   // free(string);

     
     
    
    
    
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
     for(int x = 0; x < 65536; x++)
    {
        node* cursor = HASHTABLE_SIZE[x];
        
       
            //cursor = (HASHTABLE_SIZE[x]);
                
            while (cursor != NULL)
             {
                // node *temp = cursor;
                 cursor = cursor->next;
                 count++;
                 //free(temp);
             }
        
        
    
    return 1;
    } 
    
  
        return false;
    
}


/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //if (&load)
    //{
    //free(def);
    node* cursor;
    
   //node *cursor = HASHTABLE_SIZE[hash_it(new_node->word)];
   //free(char *string);
    for(int x = 0; x < 65536; x++)
    {
       // node* cursor = HASHTABLE_SIZE[x];
        
        //if (HASHTABLE_SIZE[x] != NULL)
       // {
            cursor = (HASHTABLE_SIZE[x]);
                
            while (cursor != NULL)
             {
                 node *temp = cursor;
                 cursor = cursor->next;
                 free(temp);
             }
       // }
        
    
    return true;
    } 
    
    
    
    return false;
}
