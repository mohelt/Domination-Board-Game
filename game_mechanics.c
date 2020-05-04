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
            return notChosenPiece;
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

bool check_move_possible(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z,int i, int j,bool chosenPlaceToMove) {
    bool stackOrSingleChosen = false;
    int a;
while (stackOrSingleChosen == false){
    printf("Please enter 0 to move one piece, please enter 1 to move an entire stack \n");
    scanf("%d", &a);
    if(a==0){
        stackOrSingleChosen = true;
        int k, l;
        printf("Please enter the row of the piece you would like to move your piece to.(0 - 7)\n");
        scanf("%d", &k);
        printf("Please enter the column of the piece you would like to move your piece to. (0 - 7)\n");
        scanf("%d", &l);
        bool moveAllowed = true;
        if (board[k][l].type == VALID) {
        }
        else{
            printf("Illegal move. Those squares are not part of the game\n");
        }

        if(moveAllowed == true){
            printf("Successfully chosen a piece.\n");
            int value = board[i][j].stack->p_color;
            push(value,board,k,l);
            pop(board,i,j);
            chosenPlaceToMove = true;
        }
        return chosenPlaceToMove;
    }
    if(a==1) {
        if (board[i][j].stack->next != NULL) {
            stackOrSingleChosen = true;
            int k, l;
            printf("Please enter the row of the piece you would like to move your piece to.(0 - 7)\n");
            scanf("%d", &k);
            printf("Please enter the column of the piece you would like to move your piece to. (0 - 7)\n");
            scanf("%d", &l);
            bool moveAllowed = true;
            if (board[k][l].type == VALID) {
            } else {
                printf("Illegal move. Those squares are not part of the game\n");
            }

            if (moveAllowed == true) {
                printf("Successfully chosen a piece.\n");


                push_stack( board, k, l,i,j);
                pop_stack(board, i, j);
                chosenPlaceToMove = true;
            }
            return chosenPlaceToMove;
        }else{
            printf("This piece only has one piece pick 0 to move just that piece.\n");

        }
    }
}
}
struct piece * pop(square board[BOARD_SIZE][BOARD_SIZE], int i, int j){
    piece *thisPiece;
    thisPiece = board[i][j].stack;
    board[i][j].stack->p_color = thisPiece->p_color;
    board[i][j].stack = board[i][j].stack->next;
    free(thisPiece);

}

struct piece * push(int value,square board[BOARD_SIZE][BOARD_SIZE], int k, int l){
    piece *thisPiece;
    thisPiece = malloc(sizeof(piece));
    thisPiece -> p_color = value;
    thisPiece -> next = board[k][l].stack;
    board[k][l].stack = thisPiece;

}
struct piece * pop_stack(square board[BOARD_SIZE][BOARD_SIZE], int i, int j){

    piece *thisPiece;
    thisPiece = board[i][j].stack;
    while(thisPiece->next != NULL){
        thisPiece = thisPiece->next;
    }
    board[i][j].stack = thisPiece->next;
    free(thisPiece);

}

struct piece * push_stack(square board[BOARD_SIZE][BOARD_SIZE], int k, int l,int i,int j){
    piece *thisPiece;
    thisPiece = malloc(sizeof(piece));
    thisPiece = board[i][j].stack;
    while(thisPiece->next != NULL){
        thisPiece = thisPiece->next;
    }
    thisPiece->next = board[k][l].stack;
    board[k][l].stack = board[i][j].stack;

}