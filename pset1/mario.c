#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int row;
    
    do {
        printf ("Height: ");
        row = GetInt();
    } while (!(row >= 0 && row <=23 ));

    for (int i = 0; i < row; i ++)
    {
        for (int counter1 = 0; counter1 < row - i - 1; counter1 ++)
        {
            printf(" "); 
        }
        
        for (int counter1 = 0; counter1 < 2 + i; counter1 ++)
        {
            printf("#"); 
        }
        
        printf("\n");
    } 
}
