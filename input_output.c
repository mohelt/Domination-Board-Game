//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j].type == VALID)
            {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else
                {

                    if (board[i][j].stack->p_color == GREEN)
                    {
                        printf("| G ");
                    }

                    if (board[i][j].stack->p_color == RED)
                    {
                        printf("| R ");
                    }

                }
            }
            else
                printf("| - ");
        }
        printf("|\n");
    }
}
bool see_winner(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM])
{
    // functions checks if red or green have a piece at the top of the stack
    // if not they lose as they cant make a move

    int topPieceRed = 0;
    int topPieceGreen = 0;
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j].type == VALID)
            {
                if(board[i][j].stack == NULL){}

                else{
                    if (board[i][j].stack->p_color == GREEN)
                    {
                        topPieceGreen++;
                    }
                    if (board[i][j].stack->p_color == RED)
                    {
                        topPieceRed++;
                    }
                }
            }
        }
    }
    if (topPieceGreen==0){
        printf("Player 1:%s wins!",players[0].playerName);
        return true;
    }
    if (topPieceRed==0){
        printf("Player 2:%s wins!",players[1].playerName);
        return true;
    }
    return false;
}
