///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      None
// Semester:         CS 354 Spring 2023
// Instructor:       Debbra Deppeler
//
// Author:           Nikhil Sethuram Thenmozhi
// Email:            nst@wisc.edu
// CS Login:         sethuram-thenmozhi
// GG#:              GG 12
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          None
//
//
// Online sources:   None
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct
{
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize()
{
    int mgsize; // size of magic square inputted by user
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%i", &mgsize);
    if (mgsize < 3)
    {
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }
    if (mgsize % 2 == 0)
    {
        printf("Magic square size must be odd.\n");
        exit(1);
    }

    return mgsize;
}

/* TODO:
 * Makes a magic square of size n using the
 * Siamese magic square algorithm or alternate from assignment
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n)
{
    MagicSquare *mysquare = (MagicSquare *)malloc(sizeof(MagicSquare));
    mysquare->size = n;
    mysquare->magic_square = (int **)malloc(n * sizeof(int *));

    // Allocate and initialize the magic square directly to 0
    for (int i = 0; i < n; i++)
    {
        mysquare->magic_square[i] = (int *)calloc(n, sizeof(int));
    }

    int rowindex = 0;
    int colindex = n / 2;
    int magicnumber = 1;

    while (magicnumber <= n * n)
    {
        mysquare->magic_square[rowindex][colindex] = magicnumber;

        int nextrowindex = (rowindex - 1 + n) % n; //% n to wrap it around
        int nextcolindex = (colindex + 1) % n;

        if (mysquare->magic_square[nextrowindex][nextcolindex] == 0)
        { // index not filled //fill up right
            rowindex = nextrowindex;
            colindex = nextcolindex;
        }
        else
        { // the index is filled //fill down
            rowindex = (rowindex + 1) % n;
        }

        magicnumber++;
    }

    return mysquare;
}

/* TODO:
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int size = magic_square->size;
    int **mysquare = magic_square->magic_square;

    // write the size out
    fprintf(fp, "%d\n", size);

    // write the magic square out
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(fp, "%d ", *(*(mysquare + i) + j));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv)
{
    // TODO: Check input arguments to get output filename
    if (argc != 2)
    {
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }

    // TODO: Get magic square's size from user
    int size = getSize();

    // TODO: Generate the magic square by correctly interpreting
    MagicSquare *mysquare = generateMagicSquare(size);
    //       the algorithm(s) in the write-up or by writing or your own.
    //       You must confirm that your program produces a
    //       Magic Sqare as described in the linked Wikipedia page.

    // TODO: Output the magic square
    fileOutputMagicSquare(mysquare, argv[1]);

    // freeing memory
    for (int i = 0; i < size; i++)
    {
        free(mysquare->magic_square[i]);
    }
    free(mysquare->magic_square);
    free(mysquare);

    return 0;
}

// S23
