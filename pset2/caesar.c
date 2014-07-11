# include <cs50.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char encrypt(int key, char letter)
{       
    // if the character is not alphabetical then just return the letter
    if (isalpha(letter) == false)
        return letter;
    
    // offset shifts the character's ASCII value to an alphabetical index
    // it accounts for different character cases
    int offset = 0;

    // check if the letter is upper or lower 
    if (islower(letter))
        offset = 97;
        
    else if (isupper(letter))
        offset = 65;
        
    int alpha_letter = letter - offset;
        
    int crypt_letter;
    // shifts the character by the key, wrapped, and then switched back to proper ASCII value
    crypt_letter = ((alpha_letter + key)% 26) + offset;
    
    return crypt_letter;
}

int main(int argc, string argv[])
{   
    // if the user did not include a key in the command line then return an error
    if (argc != 2)
    {
        printf("Usage: ./asciimath key\n");
        return 1;
    }
    
    int key = atoi(argv[1]); 
    string plaintext = GetString();
    
    //  loop to encrypt each character in plaintext 
    for (int i = 0, n = strlen(plaintext); i < n; i++)
        printf("%c", encrypt(key, plaintext[i]));
    
    printf("\n");
        
    return 0;
}
