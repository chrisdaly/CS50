/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(50000);// add an extra zero
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(100000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int i = 0, j = 0;
    int num = (d*d) -1;
    for (i = 0; (i < d); i++)
    {
        for (j = 0; (j < d); j++)
        {     
            if (num == 2)
            {
                if (d%2 == 0)
                    num = 1;
            }
            
            else if (num == 0)
            {
                if (d%2 == 0)
                {
                    num = 2;
                } 
            }   
             
            else if (num == 1)
            {
                if (d%2 == 0)
                {
                    num = 1000;
                }   
            }
            
            if (num == 0)
            {
                num = 1000;
            }          
                   
            board[i][j] = num;
            num --;
            }
    }  
    usleep(1000000);  
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //Draws the board.
    int i = 0, j = 0;
    for (i = 0; (i < d); i++)
    {
        if (i > 0)
            printf("\n");
        for (j = 0; (j < d); j++)
        {
            int num = board[i][j];
            if (num == 1000)
                printf("\033[32;1m - \033[0m");
            else 
            printf("%2d ", board[i][j]);
        
        }
    }  
    printf("\n");
    //printf("Blank  = %i", board[d][d]);
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
 
void search(int num, int *x, int *y)
{
    int i, j;
    for (i = 0; (i < d); i++)
        for (j = 0; (j < d); j++)
            if (board[i][j] == num)
            {
                *x = i;
                *y = j;
            }             
   return;  
}
 
bool nextTo(int pos1[1], int pos2[1])
{
    //Checks if two coordinates are orthogonally adjacent.
    int x1 = pos1[0], y1 = pos1[1], x2 = pos2[0], y2 = pos2[1];
    
    if ((x1 == x2) && (abs(y1 - y2) == 1))
        return true;
    
    else if ((y1 == y2) && (abs(x1 - x2) == 1))
        return true;
        
    else
        return false;    
}
  
void swap(int pos1[1], int pos2[1])
{
    //Switches numbers of two tile positions.
    int x1 = pos1[0], y1 = pos1[1], x2 = pos2[0], y2 = pos2[1], temp;
    
    temp = board[x1][y1];
    
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}
 
bool move(int tile)
{
    //Takes the number of a tile through user input and checks if it's next to
    //the blank tile. If they are adjacent then the tile position's numbers are swapped
    
    int blankTile_pos[2], x, y;
    x = 10;
    y = 10;
    search(1000, &x, &y);
    blankTile_pos[0] = x;
    blankTile_pos[1] = y;   
    //printf("Blank tile = %i, %i\n", blankTile_pos[0], blankTile_pos[1]); 
    
    int tile_pos[2], x1, y1;
    x1 = 10;
    y1 = 10;
    search(tile, &x1, &y1);
    tile_pos[0] = x1;
    tile_pos[1] = y1;   
    //printf("User tile = %i, %i\n", tile_pos[0], tile_pos[1]); 
    
    if (nextTo(blankTile_pos, tile_pos) == true)
    {
        swap(blankTile_pos, tile_pos);
        return true;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //Loops over the board, checking if each element is less than the next
    //and if the blank tile is in the proper position.
    int i, j;
    //printf("End position = %i\n", board[d-1][d-1]);
    
    //Check that the blank tile is in the bottom right position.
    if (board[d-1][d-1] != 1000)
    {
        //printf("Blank not in place");
        return false;
    }
    
    //Loop over the board to ensure that each number is less that the next number.
    for (i = 0; (i < d); i++)
        for (j = 0; (j < d); j++)
        {
            int current, next;
            current = board[i][j];
            next = board[i][j+1];
            
            //Once the last number has been checked, break the loop
            if ((i == d-1) && (j == d-2))
            break;
            
            //Once the end of a row is reached, check the start of the next row
            if (j == d-1)
            {
                next = board[i+1][0];
            }
            
            //printf("Current = %i, Next = %i\n", current, next);   
            if (current > next)
            {
                //printf("Not in order\n");
                return false;
            }
        }            
    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
