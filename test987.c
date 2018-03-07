#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    printf("s: ");
    string s = get_string();

    printf("t: ");
    string t = get_string();

    for (int i = 0; i < strlen(s); i++)
    {
    
    if (s[i] == t[i])
    {
        //printf("same\n");
        return 0;
    }
    else
    {
        printf("different\n");
    }

    
}
//printf("same\n");
}