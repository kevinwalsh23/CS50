#include <stdio.h>
#include <cs50.h>

int x;
int q;
int p;
int n;
int d;
int total;
float change;
int main(void)
{
     printf("O hai! How much change is owed?");
     change = get_float();

while (change < 0.00)
{
    printf("Retry, How much change?");
    change = get_float();
}


if (change >= 0.00)
{
     x = change * 1000;
}


while (x>= 250)
{
    x = x-250;
    q++;
}
while (x>=100)
{
    x = x-100;
    d++;
}

while (x>=50)
{
    x = x-50;
    n++;
}

while (x>=10)
{
    x= x-10;
    p++;
}

total = p + n + d + q;
    
{ printf("%i\n", total);
}
}