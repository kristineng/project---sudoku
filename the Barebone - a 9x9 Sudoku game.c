#include <stdio.h>

void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            gameBoard[i][j] = puzzle[i][j];
}

void printGameBoard(int gameBoard[][9]) {

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

int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
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




int checkFinish(int gameBoard[][9], int sol[][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (gameBoard[i][j] == 0) return 0;
            else if (gameBoard[i][j] != sol[i][j]) return 0;
        }
    return 1;
}

int checkSolutionDetail(int gameBoard[][9], int x, int y){
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

int checkFillable(int gameBoard[][9], int x, int y){
}

int isLockBoard(int gameBoard[][9]){
}

int savePuzzle(int gameBoard[][9], int sol[][9]){
}

int loadPuzzle(int gameBoard[][9], int sol[][9]){
}

void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n");
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]); 
        }
    }
    fclose(fp);
}


int main()
{

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
  
    int gameBoard[9][9];

    int gameMode, chances = 3, hintCount = 0;

    int x, y;

    int number;

    int win = 0, validIn = 0, inputValid = 0;
    int check = 0;

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


    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);

    while(checkFinish(gameBoard, mySolution) == 0)
    {
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



    if (gameMode == 0)
        printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.", hintCount);
    else if (chances > 0)
        printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.", chances);
    else
        printf("You lose.");

    return 0;
}
