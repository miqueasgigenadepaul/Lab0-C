#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define dim 4
#define CELL_MAX (dim * dim - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");
}

void print_board(char board[dim][dim])
{
    int cell = 0;

    print_sep(dim);   
    for (int row = 0; row < dim; ++row) {
        for (int column = 0; column < dim; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(dim);
    }
}

char get_winner(char board[dim][dim]){
    char winner = '-';

    int i = 0;
    while (i < dim) {
        bool hayGanador = false;

        // filas
        
        // columnas
        for (int fila = 0; fila < dim; fila++){
            for (int columna = 0; columna < dim - 1; columna++){
                if (board[fila][columna] == board[fila][columna+1]){
                    hayGanador = true;
                }
            }
        }

        if (hayGanador == true){
            winner = board[i][0];
        } 

        i++;
    }
    
    
    
    

    //diagonal principal

    //diagonal opuesta

    return winner;
}

bool has_free_cell(char board[dim][dim])
{
    bool free_cell=false;
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            if (board[i][j] == '-'){
                free_cell = true;
            }
        }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[dim][dim];
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            board[i][j] = '-';
        }
    }

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / dim;
            int colum = cell % dim;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
