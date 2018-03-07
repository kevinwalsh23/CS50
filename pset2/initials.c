#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i;
int main (void)
{
    string s = get_string();
    printf("%c", toupper(s[0]));
    for (i = 0; i < strlen(s); i++)
    {
     
     
  if (s[i] == ' ')
        {
            printf("%c", toupper(s[i +1]));
    }
    
     
        
      
    }
     {
    printf("\n");
    } 
}
    

