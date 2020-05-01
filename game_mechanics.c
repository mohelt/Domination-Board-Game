//
// Created by moham on 29/04/2020.
//
#include "input_output.h"
#include "game_mechanics.h"
//Function to create the player turns
void player_turns(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE]){
    bool gameWon = false;
    if(gameWon == true){

    }
    int turn = 1;

    while(turn <5)
    {

        if (players[0].playerTurn == true)
        {
            //player One play
            int z = 0;
            printf("Player 1 turn:\n");
            player_moves(players,board,z);
            print_board(board);
            turn++;
        }
        else
        {
            //player Two play
            int z = 1;
            printf("Player 2 turn:\n");
            player_moves(players,board,z);
            print_board(board);
            turn++;
        }
        if (turn % 2 == 0)
        {
            players[0].playerTurn = false;
        }
        else
        {
            players[0].playerTurn = true;
        }
    }
}
//Function to preform player moves
void player_moves(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z){
    int i,j;
    bool notChosenPiece = true;
    bool chosenPlaceToMove = false;
    while(notChosenPiece) {
        printf("Please enter the row of the piece you would like to move.(0 - 7)\n");
        scanf("%d", &i);
        printf("Please enter the column of the piece you would like to move. (0 - 7)\n");
        scanf("%d", &j);
        notChosenPiece = check_piece_possible(players, board, z, i, j, notChosenPiece);
    }
    while(chosenPlaceToMove == false) {
        chosenPlaceToMove = check_move_possible(players, board, z, i, j, chosenPlaceToMove);
    }
}

bool check_piece_possible(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z,int i, int j,bool notChosenPiece){
    if(board[i][j].type == VALID) {
        if (board[i][j].stack == NULL) {
            printf("Cannot choose that square. Its empty.\n");
        }
            if (board[i][j].stack->p_color == players[z].player_color){
                printf("Successfully selected square.\n");
                notChosenPiece = false;
            }
            else{
                printf("Cannot choose that square. Its not your color.\n");
            }
    }
        else{
                printf("Illegal move. Those squares arent part of the game.\n");
            }
        return notChosenPiece;
}

bool check_move_possible(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z,int k, int l,bool chosenPlaceToMove) {
    int i, j;
    printf("Please enter the row of the piece you would like to move your piece to.(0 - 7)\n");
    scanf("%d", &i);
    printf("Please enter the column of the piece you would like to move your piece to. (0 - 7)\n");
    scanf("%d", &j);
    bool moveAllowed = true;
    if (board[i][j].type == VALID) {
        if (((k - 1) == i) && ((l - 1) == j)) {
            printf("Illegal diagonal move.\n");
            moveAllowed = false;
        }
        if (((k + 1) == i) && ((l + 1) == j)) {
            printf("Illegal diagonal move.\n");
            moveAllowed = false;
        }
        if (((k - 1) == i) && ((l + 1) == j)) {
            printf("Illegal diagonal move.\n");
            moveAllowed = false;
        }
        if (((k + 1) == i) && ((l - 1) == j)) {
            printf("Illegal diagonal move.\n");
            moveAllowed = false;
        }
    }
    else{
        printf("Illegal move. Those squares are not part of the game\n");
    }
    if(moveAllowed == true){
        printf("Successfully chosen a piece.\n");
        pop(board,i,j,k,l);
        chosenPlaceToMove = true;
    }
    return chosenPlaceToMove;
}
struct piece * push(square board[BOARD_SIZE][BOARD_SIZE],int i,int j,struct piece * stack ){
        struct piece *curr = board[i][j].stack;
        board[i][j].stack = malloc(sizeof(piece));
        board[i][j].stack = stack;
        board[i][j].stack->next = curr;
        return board[i][j].stack;
}

/*
 * This method prints the value of the topmost element of the stack
 * and removes the element from the stack
 *
 * Input
 * top: a pointer to the top of the stack
 *
 * Output
 * Returns the new top of the stack after the topmost element is removed
 */
struct piece * pop(square board[BOARD_SIZE][BOARD_SIZE],int i,int j, int k, int l){
    struct piece *curr = board[k][l].stack;
    if(curr!=NULL){
        board[k][l].stack = curr->next;
        free(curr);
    }
    push(board,i,j,curr);
    return board[k][l].stack;
}