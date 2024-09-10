/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Nguyen Thi Mai Huyen
 * Student ID    : 1155210003
 * Class/Section : D
 * Date          : 7/12/2023
 */

#include <stdio.h>
/* NO other header files are allowed */

/* NO global variables are allowed */


// Initialize the specified game board.
void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

    // TODO: Complete this part
    // Hint: Copies the content of puzzle to gameBoard
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            gameBoard[i][j] = puzzle[i][j];
}

/* Display the specified game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[][9]) {
    // TODO: Complete this part
    // Hint:
    // 1. First, try to prints the content of gameBoard
    // 2. Use conditional statement to print ' ' or 'X' for the two cases (empty or selected cell).
    // 3. Add the borders, col/row numbers

    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d", i);
        if (i % 3 == 2) printf(" ");
    }
    printf("\n");
    printf(" +---+---+---+\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%d|", i);
        for (int j = 0; j < 9; j++)
        {
            if(gameBoard[i][j] == -1)
                printf("X"); // X is -1
            else if (gameBoard[i][j] == 0)
                printf(" ");
            else
                printf("%d", gameBoard[i][j]);
            if(j % 3 == 2) printf("|");
        }
        printf("\n");
        if (i % 3 == 2)
            printf(" +---+---+---+\n");
    }
}

/* inputBoard() reads a char '1' to '9', or 'H' from the player.
    You need to apply input validation, output error message, and go back to cell selection if its input is invalid.
    gameMode indicates if the game is run in Easy (0) or Hard (1) mode, so that you can determine if hint is allowed.
    *** The function returns 1 if 'H' is inputted (i.e., the player uses a hint), returns -1 if an invalid input is read, and 0 otherwise (valid input). ***
    IMPORTANT: Using other output format will result in mark deduction. */
int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    // TODO: Complete this part
    printf("Input a number [or H: hint]: ");
    char a;
    scanf(" %c", &a);
    gameBoard[x][y] = 0;
    if (gameMode == 1)
    {
        if (a == 'H')
        {
            printf("No hint in Hard mode.\n");
            return -1;
        }
        else if (a > '9' || a < '0')
        {
            printf("Invalid Input.\n");
            return -1;
        }
        else
        {
            gameBoard[x][y] = a - '0';
            return 0;
        }
    }
    else
    {
        if (a == sol[x][y] + '0')
        {
            gameBoard[x][y] = sol[x][y];
            return 0;
        }
        else if (a == 'H')
        {
            gameBoard[x][y] = sol[x][y];
            return 1;
        }
        else if (a > '9' || a < '0')
        {
            printf("Invalid Input.\n");
            return -1;
        }
        else
        {
            printf("Sorry, %c should not be placed at (%d, %d).\n", a, x, y);
            return 0;
        }
    }
}



// This function outputs 1 if the gameBoard is finished (and identical to the solution), and 0 otherwise.
int checkFinish(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (gameBoard[i][j] == 0) return 0;
            else if (gameBoard[i][j] != sol[i][j]) return 0;
        }
    return 1;
}


/* ** Hard Mode **
    Check the (x, y) cell in the game board to see if it conflicts with other numbers in the same row/column/subgrid.
    You need to output messages to indicate incorrect answer.
    if (x,y) cell causes conflict in 2 or more categories, all such messages will be printed in order.
    The function returns 1 if (x, y) causes conflicts, and 0 otherwise.
    Hint: The return value can be used to update chances in main.
    IMPORTANT: Using other output format will result in mark deduction. */

int checkSolutionDetail(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int ok = 1, found = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i == y) continue;
        if (gameBoard[x][i] == gameBoard[x][y])
        {
            printf("Check again the numbers in row %d.\n", x);
            ok = 0;
            break;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (i == x) continue;
        if (gameBoard[i][y] == gameBoard[x][y])
        {
            printf("Check again the numbers in column %d.\n", y);
            ok = 0;
            break;
        }
    }
    for (int row = x / 3 * 3, i = row; i <= row + 2; i++)
    {
        for (int col = y / 3 * 3, j = col; j <= col + 2; j++)
        {
            if (i == x && j == y) continue;
            if (gameBoard[i][j] == gameBoard[x][y])
            {
                printf("Check again the numbers in the subgrid where (%d, %d) is at.\n", x, y);
                ok = 0;
                found = 1;
                break;
            }
        }
        if (found == 1) break;
    }
    if (ok == 0) gameBoard[x][y] = 0;
    return ok;
}

/* ** Part 2 **
    checkFillable() checks the row/column/subgrid that the cell (x, y) resides at given the current gameBoard.
    It determines if all the numbers in the same row + column + subgrid contain all numbers 1 - 9, i.e., the cell (x, y) cannot be filled (or is locked).
    It returns 0 if cell (x, y) is locked; and returns 1 if the cell (x, y) can be filled */
int checkFillable(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
}

/*
    isLockBoard() determines if the input gameBoard contains a locked cell.
    If there is a locked cell, it prints a locked cell and returns 1.
    It returns 0 if the game board is free of locked cell
    Hint: loop through all empty cell and use checkFillable to aid in checking the cell.
    */
int isLockBoard(int gameBoard[][9]){
    // TODO: Complete this part
}


/* ** Part 2: Save and Load** */
// the savePuzzle function saves the gameBoard and solution to the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to save.
// The program returns 1 if it successfully saves the file, and 0 otherwise.
int savePuzzle(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
}

// the loadPuzzle function loads the gameBoard and solution from the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to load.
// The program returns 1 if it successfully loads the file, and 0 otherwise.
int loadPuzzle(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
}

// A helper function to craft a text file containing the inputs to fill in the puzzle according to the solution.
// Call it to generate a text file that prints the inputs leading to a finished puzzle
// To Debug:
//  In Powershell, run: Get-Content .\textInput.txt | & .\main.exe
//  or simply run the program, copy and paste contents of the text file to console.
// You may modify the function as you wish
void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]); // You may print a character to test Hint/Save-load function.
        }
    }
    fclose(fp);
}

/* The main function */
int main()
{
    /* Local variables */

    // Assume both mode uses same set of puzzle
    // In Part 2, read the puzzle and solution from puzzle.txt
    // You may input your puzzle to debug, e.g., replace some entries of the solution by 0
    int myPuzzle[9][9]={
        {5,0,0,0,6,3,4,0,0},
        {0,0,0,7,0,0,0,0,0},
        {1,0,0,0,5,0,8,3,0},
        {0,0,0,0,1,8,0,0,7},
        {0,0,6,9,0,0,0,0,0},
        {0,4,3,0,0,0,9,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,7,0,0,2,0},
        {3,2,0,6,4,0,5,0,0}
    };
    // The solution
    int mySolution[9][9] = {
        {5,9,8,1,6,3,4,7,2},
        {6,3,2,7,8,4,1,5,9},
        {1,7,4,2,5,9,8,3,6},
        {2,5,9,4,1,8,3,6,7},
        {8,1,6,9,3,7,2,4,5},
        {7,4,3,5,2,6,9,8,1},
        {4,6,5,8,9,2,7,1,3},
        {9,8,1,3,7,5,6,2,4},
        {3,2,7,6,4,1,5,9,8}
    };
    // Game Board
    int gameBoard[9][9];

    // gameMode: {0: Easy  1: Hard}
    // chances is the no. of chances in hard mode
    // hintCount stores the no. of hint used.
    int gameMode, chances = 3, hintCount = 0;

    // store x, y coordinate of a cell
    int x, y;

    // number will store the puzzle ID (player's puzzle selection)
    int number;

    // Create YOUR local variables
    /* Initialize the local variables */
    int win = 0, validIn = 0, inputValid = 0;
    int check = 0;

    // Read the Game mode to gameMode
    // Repeats the input process for an invalid input
    // Set the Game mode and display the message

    // TODO: Read Game Mode and output selected mode
    do
    {
        printf("Enter the game mode [0: Easy. 1: Hard]: ");
        scanf("%d", &gameMode);
        if (gameMode != 0 && gameMode != 1) printf("Invalid Input.\n");
    } while (gameMode != 0 && gameMode != 1);

    if (gameMode == 0)
        printf("You have selected Easy mode.\n");
    else
        printf("You have selected Hard mode.\n");

    // Call initGameBoard to read the puzzle to gameBoard
    // and call printGameBoard to print it
    /* Uncomment the following statements to test if they are implemented correctly.
       You can add more if you wish. But remember to delete them before submission*/

    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);

    // The following line calls the helper function, which print the user inputs leading to a finished puzzle
    // printSolution(gameBoard, mySolution);

    // TODO: Your Easy/Hard mode Game starts
    // The following is the suggested workflow

    // While the game is not finished:
        // Let the player select a cell
        //    Repeat the cell selection process if it is invalid

        // Print Game Board After player chose a valid cell (displayed as 'X')

        // Receive input from the player by calling inputBoard().
        // Use the return value from inputBoard() for program control flow.

        // If inputBoard indicates invalid input, go back to cell selection

        // check the answer for different game mode
        // e.g., call checkSolutionDetail() for Hard mode

        // print the game board

        // If the player wins, exit the while loop, else continue the game.
    while(checkFinish(gameBoard, mySolution) == 0)
    {
        // Input the coordinates of the cell
        while(1 == 1)
        {
            printf("Select a row and column: ");
            scanf("%d%d", &x, &y);
            if (x < 0 || x > 8 || y < 0 || y > 8) printf("Out of bound. Input Again.\n");
            else if (gameBoard[x][y] >= 1 && gameBoard[x][y] <= 9) printf("Occupied.\n");
            else break;
        }
        gameBoard[x][y] = -1;

        printGameBoard(gameBoard);

        int input = inputBoard(gameBoard, x, y, mySolution, gameMode);
        if (gameMode == 1 && input == 0)
        {
            if (checkSolutionDetail(gameBoard, x, y) == 0)
            {
                chances--;
                if (chances == 0) break;
                else printf("You have %d chances left.\n", chances);
            }
        }

        printGameBoard(gameBoard);

        if (input == 1) hintCount++;
    }


    // Output the winning or losing message

    if (gameMode == 0)
        printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.", hintCount);
    else if (chances > 0)
        printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.", chances);
    else
        printf("You lose.");

    return 0;
}