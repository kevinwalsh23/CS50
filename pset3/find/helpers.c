/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"


void swap(int* x, int* y);
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n<0)
    {
        return false;
    }

   
    int x = n;
    int y = 0;
    
    
    while (x>=y)
    {
    int w = (x + y)/2;
    
   // do   
    
    //{
    if (values[w] == value)
    {
        return true;
    }
    
    
   // if (values[w] != value)
    //{
    //w = ((x - y)/2);
    //}
    
    else if (values[w] > value)
    {
       x = (w-1);
       
    }   
    else if (values[w] < value)
    {
        y = (w + 1);
        
    }
    }
    
   // }
    //while (values[w] != value);
    //else return false;
    //while (values[w] != value);

return false;
}

    








//{
//    if (n/2 == value)
//    {
//        return true;
//    }
    
//    if (n/2 > value)
//    {
//        if ((n + (n/2)/2) == value)
//        return true;
//    }
//    if (n/2 < value)
//    {
//        if (n - (n/2)/n) == value)
//        return true;
//    }
    
    
//    if (n > 0)
//    // TODO: implement a searching algorithm
//    for (int i = 0; i < n; i++)
//        {
//        if (value == values[i])
//        return true;
//        }
    
//    return false;
//}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
{
   int c = -4;
   // TODO: implement an O(n^2) sorting algorithm
   do
   {
   c = 0;
   for (int i = 0; i < (n-1); i++)
      
      if (values [i] > values[i+1])
      {
      swap (&values [i], &values[i+1]);
      c = c + 1 ;
      }
   }
      while (c != 0);
        
      //if (values > i)
        //{
        //swap values $$ i;
        //}
    return ;
}

void swap(int* x, int* y)
{
int tmp = *x;
*x = *y;
*y = tmp;
}

