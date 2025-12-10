#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[9] = {'1','2','3','4','5','6','7','8','9'};

// Function to display game board
void displayBoard() {
    printf("\n\n TIC TAC TOE \n");
    printf("-------------\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("-------------\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("-------------\n");
    printf(" %c | %c | %c \n\n", board[6], board[7], board[8]);
}

// Function to check winner
int checkWinner() {
    int winCombinations[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},    // Rows
        {0,3,6}, {1,4,7}, {2,5,8},    // Columns
        {0,4,8}, {2,4,6}              // Diagonals
    };

    for(int i=0; i<8; i++) {
        int a = winCombinations[i][0];
        int b = winCombinations[i][1];
        int c = winCombinations[i][2];

        if(board[a] == board[b] && board[b] == board[c])
            return 1; // winner
    }
    return 0; // no winner
}

// Function to check if board is full (draw)
int isDraw() {
    for(int i=0; i<9; i++) {
        if(board[i] != 'X' && board[i] != 'O')
            return 0;
    }
    return 1;
}

// Function for Player move
void playerMove(char symbol) {
    int move;
    while(1) {
        printf("Enter your move (1-9): ");
        scanf("%d", &move);
        move--;
        if(move >= 0 && move < 9 && board[move] != 'X' && board[move] != 'O') {
            board[move] = symbol;
            break;
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
}

// Function for computer move
void computerMove() {
    int move;
    srand(time(0));

    while(1) {
        move = rand() % 9;
        if(board[move] != 'X' && board[move] != 'O') {
            board[move] = 'O';
            break;
        }
    }
}

void resetBoard() {
    for(int i=0; i<9; i++)
        board[i] = '1' + i;
}

int main() {
    int mode, turn = 0;
    char player1 = 'X', player2 = 'O';
    int gameOver = 0;

    printf("Choose Game Mode:\n");
    printf("1. Player vs Computer\n");
    printf("2. Player 1 vs Player 2\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    resetBoard();
    displayBoard();

    while(!gameOver) {
        if(mode == 1) {
            // Player vs Computer
            if(turn % 2 == 0) {
                printf("Player (X) Turn\n");
                playerMove('X');
            } else {
                printf("Computer (O) Turn\n");
                computerMove();
            }
        }
        else {
            // Player vs Player
            if(turn % 2 == 0) {
                printf("Player 1 (X) Turn\n");
                playerMove('X');
            } else {
                printf("Player 2 (O) Turn\n");
                playerMove('O');
            }
        }

        displayBoard();

        if(checkWinner()) {
            if(mode == 1 && turn % 2 == 1)
                printf("Computer Wins!\n");
            else if(mode == 1)
                printf("You Win!\n");
            else
                printf("Player %d Wins!\n", (turn % 2) + 1);

            gameOver = 1;
        }
        else if(isDraw()) {
            printf("It's a Draw!\n");
            gameOver = 1;
        }

        turn++;
    }

    return 0;
}