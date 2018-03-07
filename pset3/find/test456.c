#include <cs50.h>

#include "helpers.h"
void dog (int w, int w, int y);
bool search(int value, int values[], int n)
{
    if (n<0)
    {
        return false;
    }

   
    int x = n;
    int y = 0;
    
    
  
    int w = ((x - y)/2);
    
    if (values[w] == value)
    {
        return true;
    while (values[w] != value)
    }
    
    if (values[w] > value)
    {
       x = (w-1);
       
    }   
    if (values[w] < value)
    {
        y = (w + 1);
        
    }
    
}
}

