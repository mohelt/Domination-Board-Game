//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>

#include "input_output.h"


int main()
{

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    //pointer to the top of the stack
    struct piece *top = NULL;
    //pointer to the current element of the stack
    struct piece *curr = NULL;

    initialize_players(players);

    initialize_board(board);

    print_board(board);
// main function which allows game to work
    player_turns(players,board);
    return 0;
}
