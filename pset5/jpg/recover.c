/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
	// create a 512 byte buffer
	BYTE buffer[BLOCKSIZE];

	// integer to keep track of jpeg files
	int jpg_counter = -1;

	// set search status
	bool search = true;

	// create a temp outfile
	FILE* outfile = NULL;

	//open input file
	FILE* fp = fopen("card.raw", "r");
    if (fp == NULL)
    {
        printf("%s cannot open\n", argv[1]);
        return 1;
    }

    //while(fgets(fp, sizeof(fp), fp)!= NULL)

    // repeat until the end of the card
    while (search)
    {
        // read the fp into buffer
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            if (feof(fp))
            {
                fclose(fp);
                
                if (outfile != NULL)
                    fclose(outfile);
                    
    	        search = false;
                                 
                return 0;
            }
             
            fread(&buffer[i], sizeof(BYTE), 1, fp);
         }

    	// start of a new jpg 0xff 0xd8 0xff 0xe0 || 0xff 0xd8 0xff 0xe1         
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // record the picture found
            jpg_counter++;
            
            // check if there's jpg found before
            if (outfile != NULL)
                fclose(outfile);
            
            // create a new jpg file with count, count from 0
            char title[4];
            sprintf(title, "%03d.jpg", jpg_counter);
             
            // point the outfile to the newly ceated file
            outfile = fopen(title, "w");
                 
            // check if the file can be written
            if(outfile == NULL)
            {
                printf("Could not write the image.\n");
                return 1;
            }
             
            // write the buffer into the file
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
        }
        else if (outfile != NULL)
        {                 
            // copy the continued data in buffer
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
        }
    }
}
