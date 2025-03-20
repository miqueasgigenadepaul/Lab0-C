#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define dim 4
#define CELL_MAX (dim * dim - 1)

void print_sep(int length)
{
    printf("\t ");
    for (int i = 0; i < length; i++)
        printf("................");
    printf("\n");
}

void print_board(char board[dim][dim])
{
    int cell = 0;

    print_sep(dim);
    for (int row = 0; row < dim; ++row)
    {
        for (int column = 0; column < dim; ++column)
        {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(dim);
    }
}

char get_winner(char board[dim][dim])
{
    char winner = '-';
    int i = 0;

    while ((i < dim)&&(winner == '-'))
    {
        bool state1 = true;
        bool state2 = true;
        bool state3 = true;
        bool state4 = true;
        int first = board[i][0];
        int firstc = board[0][i];

        for (int columna = 1; columna < dim; columna++) // Comprueba que se gano por filas
        {
            if(first != board[i][columna])
            {
                state1 = false;
            }
        }
        for (int fila = 1; fila < dim; fila++) // Comprueba que se gano por columnas
        {
            if(firstc != board[fila][i])
            {
                state2 = false;
            }
        }
        for (int diagonal_principal = 0; diagonal_principal < dim; diagonal_principal++) // Comprueba que se gano por diagonal principal
        {
            if ((board[0][0] != board[diagonal_principal][diagonal_principal]))
            {
                state3 = false;
            }
            
        }
        for (int diagonal_opuesta = 0; diagonal_opuesta < dim; diagonal_opuesta++) // Comprueba que se gano por diagonal opuesta
        {
            //dim -1 es por la ieracion 0 1 2 3
            if (board[0][dim-1] != board[diagonal_opuesta][(dim-1) - diagonal_opuesta])
            {
                state4 = false;
            }
        }

        if (state1)
        {
            winner = first;
        } 
        else if (state2)
        {
            winner = firstc;
        }
        else if (state3 && (board[0][0] != '-')) // SOLUCIONA BUG?
        {
            winner = board[0][0];
        }
        else if (state4)
        {
            winner = board[0][dim-1];
        }
        
        i++;
    }
    

    

    return winner;
}

bool has_free_cell(char board[dim][dim])
{
    bool free_cell = false;
    for (int i = 0; i < dim; i++)
    {
        for (int z = 0; z < dim; z++)
        {
            if (board[i][z] == '-')
            {
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

    for (int i = 0; i < dim; i++)
    {
        for (int z = 0; z < dim; z++)
        {
            board[i][z] = '-';
        }
    }
    
    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board))
    {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0)
        {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX)
        {
            int row = cell / dim;
            int colum = cell % dim;
            if (board[row][colum] == '-')
            {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            }
            else
            {
                printf("\nCelda ocupada!\n");
            }
        }
        else
        {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-')
    {
        printf("Empate!\n");
    }
    else
    {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
