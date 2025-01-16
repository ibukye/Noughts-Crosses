#include <stdio.h>

#define MAX_SIZE 5
#define MAX_NAME 10

char players[2][MAX_NAME];

// Functions Prototypes
int display_menu();
int get_number();
void get_player(char [2][MAX_NAME]);
void display_board(char board[][MAX_SIZE], int, char [2][MAX_NAME], int);
int put_mark(char board[][MAX_SIZE], int, int *);
int win(char board[][MAX_SIZE], int, char [2][MAX_NAME], int);


// main
int main() {
    char board[MAX_SIZE][MAX_SIZE];
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

    while(win(board, number, players, player_number) == 0) {
        display_board(board, number, players, player_number);
        put_mark(board, number, &player_number);
        display_board(board, number, players, player_number);
    }
    
}





// Functions

int display_menu() {
    int choice, number = 3;  // Default if input is bypassed

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
            return 0;  // ensures main exits correctly
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

    get_player(players);
    return number;
}


int get_number() {
    int number;
    scanf("%d", &number);
    return number;
}

void get_player(char players[2][MAX_NAME]) {
    for (int i = 0; i < 2; i++) {
        printf("Enter player %d name: ", i+1);
        scanf("%s", players[i]);
    }
}

void display_board(char board[][MAX_SIZE], int number, char players[2][MAX_NAME], int player_number) {
    puts("********************");
    printf("It's your turn: %s\n", players[player_number]);
    printf(" ");
    for (int i = 0; i < number; i++) printf(" %d", i + 1);
    puts("");

    for (int i = 0; i < 2 * number - 1; i++) {
        if (i % 2 == 0) printf("%d ", 1 + (i + 1) / 2); 
        else if (i % 2 != 0) printf("  ");

        for (int j = 0; j < 2 * number - 1; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}




int put_mark(char board[][MAX_SIZE], int number, int *player_number) {
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
            *player_number = (*player_number == 0) ? 1 : 0; // Toggle between 0 and 1
            break;
        }
    }
    return 0;
}








// 縦横斜めのどれかで3つそろったか確認
int win(char board[][MAX_SIZE], int number, char players[2][MAX_NAME], int player_number) { 
    // 横向き
    
    for (int i = 0; i < 2 * number - 1; i+=2) {
        int pass = 0;
        for (int j = 0; j < 2 * number; j+=2) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 2][j + 2]) pass++;
        }
        if (pass == number - 1) printf("Player %s WIN!!!!\n", players[player_number]); return 1;
    } 


    // 縦向き
    for (int i = 0; i < 2 * number; i+=2) {
        int pass = 0;
        for (int j = 0; j < 2 * number - 1; j+=2) {
            if (board[j][i] != ' ' && board[j][i] == board[j+2][i]) pass++;
        }   
        if (pass == number - 1) printf("Player %s WIN!!!!\n", players[player_number]); return 1;
    }


    // 斜め向き

    return 0;
}