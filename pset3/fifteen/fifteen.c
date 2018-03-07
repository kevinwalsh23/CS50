/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// dimensions
int d;
int row;
int column;

// board
int board[DIM_MAX][DIM_MAX];



// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int* x, int* y);
//void trade(int* x, int* y);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    else
    {
        row = (d - 1);
        column = (d - 1);
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
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
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{

             
             //if (d % 2 == 0)
             //{
             
             
             for (int i = 0; i<d; i++)
                 {
                 for (int k = 0; k<d; k++)
                     {
                        board [i] [k] = ((d*d) - (k + 1 + (i*d)));
                        
                     }
                    
                     
                  
                 
                 }
             if (d % 2 == 0)
                     {
                       
                        //int tmp = board[d-1][d-2];
                        //board[d-1][d-2] = board[d][d-3];
                        //board[d-1][d-3] = tmp;
                         swap(&board[d-1][d-2], &board[d-1][d-3]);
                     }
                 
             
             
            //else
             //{
             //for (int i = 0; i<d; i++)
               //  {
                // for (int k = 0; k<d; k++)
                  //   {
                    //    board [i] [k] = ((d*d) - (k + 1 + (i*d)));
                     //}
            //     }
             //}
    // TODO
    
        
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i<d; i++)
              {
                  for (int k = 0; k<d; k++)
                     {
                        //board [i][k] = (d*d) - (i + 1);
                        if (board[i][k] != 0)
                        {
                        printf(" %2i", board[i][k]);
                        }
                        //else
                        if (board[i][k] == 0)
                        {
                            printf("  _");
                        }
                     }
                     
                         printf("\n");
                     }
                     
    
    // TODO
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
 //int column;
 //int row;

bool move(int tile)
{
    for (int i = 0; i<d; i++)
              {
                  for (int k = 0; k<d; k++)
                    
                     {
                         if (tile == board[i][k])
                          
                          //above, below, left, or right
                            {
                                 int nothing = 0;
                                // board[column][row] = nothing;
                                    
                                   
                                  if ((((column==k && row==(i + 1)) || (column==k && row==(i - 1)) || (column==(k + 1) && row==i) || (column==(k - 1) && row==i))))
                             //if ((k==column && (i + 1)==row) || (row==(k + 1) && i==column) || (k==column && (i - 1)==row) || (row==(k - 1) && i==column))
                             //if((board[k][i+1] || board[k+1][i] || board[k][i-1] || board[k-1][i]) = board[column][row])                             
                                    {
                                        swap(&board[row][column], &board[i][k]);
                                        swap(&tile, &nothing);
                                        //board [column][row] = tile;
                                        //board [i][k] = nothing;
                                        column = k;
                                        row = i;
                                    
                                        return true;
                                    }
                                    
                            }
                     }
              }
                    
                    
                                
                                
    
    
    
    
    // TODO
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
 //int a = 0;
bool won(void)
{
    for (int i = 0; i<d; i++)
                 {
                 for (int k = 0; k<d; k++)
                     
                        if (board [i][k] != ((d*d) -((d*d) -(1 + k + (i*d)))))
                            {
                            return false;
                           // int a = a +1;
                            }
                    
                     
                      
                          
                          
                       
                     }
                     
    // TODO
    return true;
}




void swap(int* x, int* y)
{
int tmp = *x;
*x = *y;
*y = tmp;
}

//void trade(int* x, int* y)
//{
//board[column][row] = tile;
//board[i][j] = blankspace;
//column=i;
//row=k;

