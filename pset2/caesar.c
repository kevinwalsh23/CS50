#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int z = 65;
int y = 97;
string s;
int main (int argc, string argv[])
{

    if (argc == 2)
    {
        printf("plaintext:");
         s = get_string();
         //x = argv[1];
         int k = atoi(argv[1]);
       
       
        printf("ciphertext:");
    
    
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            
        
            //if (s[i] == ' ')
            //{
              //  printf(" ");
            //}
            //if (s[i] == ',')
            //{
             //   printf(",");
           // }
             if (s[i] >= 65 && s[i]<=90)
            {
        
            printf("%c", (((s[i] + k - z) % 26) + z));
            }
            else if (s[i] >= 97 && s[i]<=122)
            {
        
            printf("%c", (((s[i] + k - y) % 26) + y));
            }
            else
            {
                printf("%c", s[i]);
            }
        }
    
        printf("\n");
    }
    
        
    else
    {
        printf("Usage: ./caesars k\n");
        return 1;
    }
}
