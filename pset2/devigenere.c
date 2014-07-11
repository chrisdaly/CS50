# include <cs50.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int offset(char letter, int *offset)
{        
    // offset shifts the character's ASCII value to an alphabetical index
    // it accounts for different character cases
    // the offset value is inputted by reference and modified in order to switch the char
    // back to ASCII and it's proper case
    
    // check if the letter is ASCII and (lower or upper) 
    if (isalpha(letter))
    {
        if (islower(letter))
            *offset = -97;
        
        else if (isupper(letter))
            *offset = -65;   
    }
    
    int alpha_letter = letter + *offset;
    
    return alpha_letter;
   
}

char encypher(int letter, int key, int offset)
{
    int crypt_letter;
    
    // shifts the character by the key, wrapped, and then switched back to proper ASCII value
    crypt_letter = ((letter + key)% 26) - offset;
    
    return crypt_letter;
}


int main(int argc, string argv[])
{   
    // if the user did not include a key in the command line then return an error
    if (argc != 2)
    {
        printf("No key entered.\n");
        return 1;
    }
    
    // set the key
    string key = argv[1]; 
       
    // check each character in the key to ensure that it's alphabetical
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Your key must be alphabetical.\n");
            return 1;
        }
    } 
    
    // set the plaintext  
    string plaintext = GetString();
    printf("Key is %s.\nPlain text is %s\n", key, plaintext);
       
    // loop to encrypt each character in plaintext 
    // i index for plaintext, j index for key (wrapped)
    
    
    for (int i = 0, j = 0, n1 = strlen(plaintext); i < n1; i++)
    {      
        // , n2 = strlen(key)
        //printf("i = %i, j = %i, n1 = %i, n2 = %i, plaintext = %c\n", i, j, n1, n2, plaintext[i]);
        
        
        if (isalpha(plaintext[i]) == false)
        {
            printf("%c", plaintext[i]);
            
        }
        
        else
        {
            //printf("success\n");
            int plaintext_offset = 0;
            int alpha_text = offset(plaintext[i], &plaintext_offset);
            int key_offset = 0;
            int alpha_key = offset(key[j], &key_offset);
            int key_length = strlen(key);
            j = j%key_length;
            //printf("PLAINTEXT:\tOffset = %i, Alpha text = %i \n", plaintext_offset, alpha_text);
            //printf("KEYTEXT:\tOffset = %i, Alpha text = %i \n", key_offset, alpha_key);
            //wrapper
            j ++;
            
            char cypher_char = encypher(alpha_text, alpha_key, plaintext_offset);
            printf("%c", cypher_char);
        }
        
    }
    printf("\n");  
    
    
    //char cypher_char2 = encypher('m', 'n', -97);
    //printf("%c", cypher_char2);
    //printf("%i", strlen("bacon"));
    return 0;
}
