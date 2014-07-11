#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Global Variables
    int num_coins = 0;
    int remaining_change;

void coinCheck(int coin_value)
{
    int coin_count;

    coin_count = remaining_change / coin_value;
    num_coins = num_coins + coin_count;
    remaining_change = remaining_change % coin_value;  
}

int main(void)
{
    float amount_dollars;
    int amount_cents;
    int coin_value = 0;

    do {
        printf ("How much?: \n");
        amount_dollars = GetFloat();
        amount_cents = round(amount_dollars * 100);
    } while (!(amount_dollars > 0 ));
    
    remaining_change = amount_cents;
    
    do {
    
        if (remaining_change >= 25){
            coin_value = 25;
		}
		
		else if (remaining_change >= 10){
            coin_value = 10;
		}
		
		else if (remaining_change >= 5){
            coin_value = 5;
		}
		
		else if (remaining_change < 5){
            coin_value = 1;
		}
        
    coinCheck(coin_value);
    } while (remaining_change != 0);

    printf("%d\n", num_coins);
}
