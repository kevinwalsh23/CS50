#include <cs50.h>

#include "helpers.h"
int value = 5;
int values = (1,2,3,4,5);
int n = 5;
bool search(value, values(), n)
{
   {
    if (n<0)
    {
        return false;
    }

   
    int x = n;
    int y = 0;
    
    
  
    int w = ((x - y)/2);
    
    do   
    
    {
    if (values[w] == value)
    {
        return true;
    }
    
    
   // if (values[w] != value)
    //{
    //w = ((x - y)/2);
    //}
    
    if (values[w] > value)
    {
       x = (w-1);
       
    }   
    if (values[w] < value)
    {
        y = (w + 1);
        
    }
    }
    while (values[w] != value);
    

return false;
}
