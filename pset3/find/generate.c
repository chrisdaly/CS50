/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // The user must include at least one extra argument when calling this program
    // A second argument for a seed is optional
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Converts the user's first command line argument to an integer, for the amount of numbers
    int n = atoi(argv[1]);

    // Check if the user provided a 2nd command line argument
    // If so, then set that argument as the seed for the new sequence of psuedo random integers
    // Otherwise use the current time as the seed
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // A loop calls the random function with the previously defined seed a set number of times
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    return 0;
}
