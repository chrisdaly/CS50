/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Initialize the limits for the search
    int low = 0;
    int high = n - 1;
    
    while(low <= high)
    {
        //Since mid is an integer, it will also work for an even amount
        //of items in the array.
        //Keep changing the bounds of the search based on the comparison result.
        int mid = low + ((high-low)/2);
        if (value == values[mid])
            return true;
        else if (value < values[mid])
            high = mid -1;
        else if (value > values[mid])  
            low = mid + 1;   
    }
    
    return false;   
}

/**
 * Sorts array of n values.
 */
		
void sort(int values[], int n)
{
    //The values in the array are checked from left to right 
    //starting from the second one
    //The current value is stored and a second index is created
    for(int i = 1; i < n; i++)
    {
        int valueToInsert = values[i];
        int j = i-1;
        
        while((j >= 0) && (valueToInsert < values[j]))
        {
        //Keep shifting the hole down until while the stored value 
        //is less than the value being checked
            values[j+1] = values[j];
            j --;
        }
    
    //The hole is now in its correct position, so insert the stored value
    values[j+1] = valueToInsert; 
    }
  
    return; 
}

