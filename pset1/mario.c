#include <stdio.h>
#include <cs50.h>

void cough(int n);
void yell (int n);
int rows;
int main(void)

{
    

{
    printf("Height:");
    rows = get_int();
}

while (rows<0 || rows > 23)
{
    printf("Height:");
    rows = get_int();
}

for (int i = 0; i < rows; i++)

{
    yell((rows -i)-1);
    cough(i + 1);
    printf("  ");
    cough(i+1);
    yell((rows -i)-1);
    printf("\n");
    
    
    
}


}


void cough(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
        
    }


    
}
void yell(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
        
    }
}

