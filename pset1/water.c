#include <stdio.h>
#include <cs50.h>

int minutes;
int main(void)

{
    int bottles = 12;
    int numbottles;
    
    printf("Minutes:");
    minutes = get_int();
   // printf("Minutes:, \n");
   
    

while (minutes<=0)
{
    printf("retry:");
    minutes = get_int();
}

if (minutes>0)
{
    numbottles = bottles * minutes;
    printf("number of bottles: %i\n", numbottles);
}
     
     
    //int x = get_int();
    //int botnum = bottles * x;
    //printf("number of bottles: %i\n", botnum);
}


    

