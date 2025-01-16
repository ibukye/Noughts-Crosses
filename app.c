#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 5
#define MAX_NAME 10

char board[MAX_SIZE][MAX_SIZE];
char players[2][MAX_NAME];
int mark_order[MAX_SIZE][MAX_SIZE];
int order = 0;      // Indicates the total number of marks

// Functions Prototypes
int display_menu();
int get_number();
void get_player();
void display_board(char board[][MAX_SIZE], int, int);
int put_mark(char board[][MAX_SIZE], int mark_order[][MAX_SIZE], int, int *);
int delete_oldest(char board[][MAX_SIZE], int mark_order[][MAX_SIZE], int);
int win(char board[][MAX_SIZE], int, int);


// main
int main() {
    int player_number = 0;
    int number = display_menu();

    // Initialize the board with empty spaces
    for (int i = 0; i < 2 * number - 1; i++) {
        for (int j = 0; j < 2 * number - 1; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) board[i][j] = ' ';
                else board[i][j] = '|';
            } 
            else {
                board[i][j] = '-';
            }
        }
    }

    while (win(board, number, player_number) == 0) {
        display_board(board, number, player_number);
        put_mark(board, mark_order, number, &player_number);
    }
    
    return 0;
}

// Display Menu
int display_menu() {
    int choice, number = 3; 

    while (1) {
        printf("********** Menu **********\n");
        printf("1. Play Game\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
            printf("Invalid choice. Please enter 1 or 2.\n");
            continue;
        }

        if (choice == 2) {
            printf("Goodbye!\n");
            return 0;  
        } else if (choice == 1) {
            printf("Let's play the game!\n");
            break;
        }
    }

    while (1) {
        printf("Select the size of the board (3-5): ");
        if (scanf("%d", &number) == 1 && number >= 3 && number <= 5) break;
        printf("Invalid size. Please enter a number between 3 and 5.\n");
    }

    get_player();
    return number;
}

// Get player names
void get_player() {
    for (int i = 0; i < 2; i++) {
        printf("Enter player %d name: ", i+1);
        scanf("%s", players[i]);
    }
}

// Display board
void display_board(char board[][MAX_SIZE], int number, int player_number) {
    printf("********************\n");
    printf("It's your turn: %s\n", players[player_number]);
    printf(" ");
    for (int i = 0; i < number; i++) printf(" %d", i + 1);
    printf("\n");

    for (int i = 0; i < 2 * number - 1; i++) {
        if (i % 2 == 0) printf("%d ", 1 + (i + 1) / 2); 
        else printf("  ");

        for (int j = 0; j < 2 * number - 1; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// Place mark
int put_mark(char board[][MAX_SIZE], int mark_order[][MAX_SIZE], int number, int *player_number) {
    int row, col;

    while (1) {
        while (1) {
            printf("Enter row (1-%d): ", number);
            scanf("%d", &row);
            row--;
            if (row >= 0 && row < number) break;
            printf("Invalid row, try again.\n");
        }

        while (1) {
            printf("Enter column (1-%d): ", number);
            scanf("%d", &col);
            col--;
            if (col >= 0 && col < number) break;
            printf("Invalid column, try again.\n");
        }

        if (board[2 * row][2 * col] != ' ') {
            printf("There is a mark. Enter again.\n");
        } else {
            board[2 * row][2 * col] = (*player_number == 0) ? 'X' : 'O';
            mark_order[2 * row][2 * col] = order++;
            if (order > 4) {
                delete_oldest(board, mark_order, number);
            }
            *player_number = (*player_number == 0) ? 1 : 0;
            break;
        }
    }
    return 0;
}


int delete_oldest(char board[][MAX_SIZE], int mark_order[][MAX_SIZE], int number) {
    int oldest = order - 6;
    for (int i = 0; i < 2 * number - 1; i+=2) {
        for (int j = 0; j < 2 * number - 1; j+=2) {
            if (mark_order[i][j] == oldest) board[i][j] = ' '; mark_order[i][j] = 0; return 1;
        }
    }
    return 0;
}


// Check for win
int win(char board[][MAX_SIZE], int number, int player_number) { 
    // Horizontal check
    for (int i = 0; i < 2 * number - 1; i += 2) {
        int pass = 0;
        for (int j = 0; j < 2 * number - 3; j += 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i][j + 2]) pass++;
        }
        if (pass == number - 1) {
            printf("Player %s WIN!!!! (%dturns)\n", players[player_number], order);
            return 1;
        }
    }
    // Vertical check
    for (int j = 0; j < 2 * number - 1; j += 2) {
        int pass = 0;
        for (int i = 0; i < 2 * number - 3; i += 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 2][j]) pass++;
        }
        if (pass == number - 1) {
            printf("Player %s WIN!!!! (%dturns)\n", players[player_number], order);
            return 1;
        }
    }

    // Diagonal check (\)

    /*
    for (int i = 0; i < 2 * number - 3; i+=2) {
        int pass = 0;
        for (int j = 0; j < 2 * number - 3; j+=2) {
            if (board[i][j] != ' ' && board[i][j] == board[i+2][j+2]) pass++;
        }
        if (pass == number - 1) {
            printf("Player %s WIN!!!! (%dturns)\n", players[player_number], order);
            return 1;
        }
    }

    // Diagonal check (/)
    for (int i = 2 * number - 3; i >= 2; i-=2) {
        int pass = 0;
        ; for (int j = 0; j < 2 * number - 3; j+=2) {
            if (board[i][j] != ' ' && board[i][j] == board[i-2][j+2]) pass++;
        }
        if (pass == number - 1) {
            printf("Player %s WIN!!!! (%dturns)\n", players[player_number], order);
            return 1;
        }
    }
    */

   // Diagonal check (\)
    int pass = 0;
    for (int i = 0; i < number; i++) {
        if (board[2 * i][2 * i] != ' ' && board[2 * i][2 * i] == board[2 * (i + 1)][2 * (i + 1)]) pass++;
    }
    if (pass == number - 1) {
        printf("Player %s WIN!!!! (%d turns)\n", players[player_number], order);
        return 1;
    }

    // Diagonal check (/)
    pass = 0;
    for (int i = 0; i < number; i++) {
        if (board[2 * i][2 * (number - 1 - i)] != ' ' && board[2 * i][2 * (number - 1 - i)] == board[2 * (i + 1)][2 * (number - 2 - i)]) pass++;
    }
    if (pass == number - 1) {
        printf("Player %s WIN!!!! (%d turns)\n", players[player_number], order);
        Sleep(3000);
        return 1;
    }



    return 0;
}
