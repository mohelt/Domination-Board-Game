//
// Created by moham on 29/04/2020.
//
#include "input_output.h"
#include "game_mechanics.h"
//Function to create the player turns
void player_turns(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE])
{
// if game is won then the game ends
    bool gameWon = false;
    if(gameWon == true)
    {

    }
    int turn = 1;

    while(gameWon == false)
    {
        if((players[0].piecesPlayerOwns == 0) || (players[0].piecesPlayerOwns == 0)){
            gameWon = true;
        }
//if its the players turn
        if (players[0].playerTurn == true)
        {
            //player One play
            int z = 0;
            printf("Player 1 turn:\n");
            printf("Number of Pieces:%d\n",players[z].piecesPlayerOwns);
            printf("Number of Pieces in Reserves:%d\n",players[z].piecesPlayerOwnsReserve);
            printf("Number of Pieces Captured:%d\n",players[z].piecesPlayerCaptured);
            //functions which allow player to move
            player_moves(players,board,z);
            print_board(board);
            turn++;
        }
        else
        {
            //player Two play
            int z = 1;
            printf("Player 2 turn:\n");
            printf("Number of Pieces:%d\n",players[z].piecesPlayerOwns);
            printf("Number of Pieces in Reserves:%d\n",players[z].piecesPlayerOwnsReserve);
            printf("Number of Pieces Captured:%d\n",players[z].piecesPlayerCaptured);
            //functions which allow player to move
            player_moves(players,board,z);
            print_board(board);
            turn++;
        }
        //allows for turns to alternate
        //if its modulus of 2 = 0 player on turn else player 2 turn
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
void player_moves(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z)
{
    //varibale declaration
    int i,j;
    bool notChosenPiece = true;
    bool chosenPlaceToMove = false;
    //while the player hasnt chosen a piece let him choose one
    while(notChosenPiece)
    {
        printf("Please enter the row of the piece you would like to move.(0 - 7)\n");
        scanf("%d", &i);
        printf("Please enter the column of the piece you would like to move. (0 - 7)\n");
        scanf("%d", &j);
        notChosenPiece = check_piece_possible(players, board, z, i, j, notChosenPiece);
    }
    while(chosenPlaceToMove == false)
    {
        //when the player hasnt chosen a piece to move to , let him
        chosenPlaceToMove = check_move_possible(players, board, z, i, j, chosenPlaceToMove);
    }
}

bool check_piece_possible(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z,int i, int j,bool notChosenPiece)
{
    if(board[i][j].type == VALID)
    {
        //if piece is available for player
        if (board[i][j].stack == NULL)
        {
            printf("Cannot choose that square. Its empty.\n");
            return notChosenPiece;
        }
        //if the top piece colour = player color then let the player continue
        if (board[i][j].stack->p_color == players[z].player_color)
        {
            printf("Successfully selected square.\n");
            notChosenPiece = false;
        }
        else
        {
            printf("Cannot choose that square. Its not your color.\n");
        }
    }
    else
    {
        printf("Illegal move. Those squares arent part of the game.\n");
    }
    return notChosenPiece;
}
// after the player chooses a piece to move , check if the place to move it to is possible
bool check_move_possible(player players[PLAYERS_NUM],square board[BOARD_SIZE][BOARD_SIZE],int z,int i, int j,bool chosenPlaceToMove)
{

    bool stackOrSingleChosen = false;
    int a;
    while (stackOrSingleChosen == false)
    {
        //check if player wants to move
        printf("Please enter 0 to move one piece, please enter 1 to move an entire stack \n");
        scanf("%d", &a);
        if(a==0)
        {
            stackOrSingleChosen = true;
            int k, l;
            printf("Please enter the row of the piece you would like to move your piece to.(0 - 7)\n");
            scanf("%d", &k);
            printf("Please enter the column of the piece you would like to move your piece to. (0 - 7)\n");
            scanf("%d", &l);
            bool moveAllowed = true;
            if (board[k][l].type == VALID)
            {
            }
            else
            {
                printf("Illegal move. Those squares are not part of the game\n");
            }

            if(moveAllowed == true)
            {
                printf("Successfully chosen a piece.\n");
                int value = board[i][j].stack->p_color;
                //functions which allow linked lists to
                push(players,z,value,board,k,l);
                pop(board,i,j);
                chosenPlaceToMove = true;
            }
            return chosenPlaceToMove;
        }
        if(a==1)
        {
            if (board[i][j].stack->next != NULL)
            {
                stackOrSingleChosen = true;
                int k, l;
                //choose place on the board to move to
                printf("Please enter the row of the piece you would like to move your piece to.(0 - 7)\n");
                scanf("%d", &k);
                printf("Please enter the column of the piece you would like to move your piece to. (0 - 7)\n");
                scanf("%d", &l);
                bool moveAllowed = true;
                if (board[k][l].type == VALID)
                {
                }
                else
                {
                    printf("Illegal move. Those squares are not part of the game\n");
                }

                if (moveAllowed == true)
                {
                    printf("Successfully chosen a piece.\n");
                    push_stack(players,z,board, k, l,i,j);
                    pop_stack(board, i, j);
                    chosenPlaceToMove = true;
                }
                return chosenPlaceToMove;
            }
            else
            {
                printf("This piece only has one piece pick 0 to move just that piece.\n");

            }
        }
    }
}
struct piece * pop(square board[BOARD_SIZE][BOARD_SIZE], int i, int j)
{
    //if you want to move just one piece
    piece *thisPiece;
    //this piece equals current piece
    thisPiece = board[i][j].stack;
    // color of top piece is equal to colour of the piece chosen
    board[i][j].stack->p_color = thisPiece->p_color;
    //top piece is now the piece underneath it;
    board[i][j].stack = board[i][j].stack->next;
    // clear the memory so no memory problems occur
    free(thisPiece);

}

struct piece * push(player players[PLAYERS_NUM],int z,int value,square board[BOARD_SIZE][BOARD_SIZE], int k, int l)
{
    //if you want to move just one piece
    piece *thisPiece;
    piece *thisPiece2;
    piece *toRemove;
    piece *last = NULL;
    int count = 1;
    //allow for dynamic memory
    thisPiece = malloc(sizeof(piece));
    //its value is equal to the piece that was previously chosen
    thisPiece -> p_color = value;
    //piece under
    thisPiece -> next = board[k][l].stack;
    board[k][l].stack = thisPiece;
    thisPiece2 = board[k][l].stack;
    while(thisPiece2 != NULL)
    {
        if (count < 5)
        {
            thisPiece2 = thisPiece2->next;
            count++;
        }
        else
        {
            last = thisPiece2;
        }
        if (last != NULL)
        {
            thisPiece2= thisPiece2->next;
            while (thisPiece2 != NULL)
            {
                toRemove = thisPiece2;
                thisPiece2 = thisPiece2->next;
                if (toRemove->p_color == players[z].player_color)
                {
                    players[z].piecesPlayerOwnsReserve++;

                }
                if (toRemove->p_color != players[z].player_color){
                    players[z].piecesPlayerCaptured++;
                    if (z==1){
                        players[(z-1)].piecesPlayerOwns--;
                    }
                    if (z==0){
                        players[(z+1)].piecesPlayerOwns--;
                    }
                }

                free(toRemove);
            }
            last->next = NULL;
        }

    }

}
struct piece * pop_stack(square board[BOARD_SIZE][BOARD_SIZE], int i, int j)
{
    //if person chooses to pop the whole stack
    piece *thisPiece;
    thisPiece = board[i][j].stack;
    while(thisPiece->next != NULL)
    {
        //finds the last piece
        thisPiece = thisPiece->next;
    }
    //top piece is now null
    board[i][j].stack = thisPiece->next;
    // frees memory so no stack problems
    free(thisPiece);

}

struct piece * push_stack(player players[PLAYERS_NUM],int z,square board[BOARD_SIZE][BOARD_SIZE], int k, int l,int i,int j)
{
    //variable declaration
    piece *thisPiece;
    piece *thisPiece2;
    piece *toRemove;
    piece *last = NULL;
    int count = 1;
    //allows dynamic memory
    thisPiece = malloc(sizeof(piece));
    thisPiece = board[i][j].stack;
    thisPiece2 = board[i][j].stack;
    while(thisPiece->next != NULL)
    {
        //finds the last piece of the stack
        thisPiece = thisPiece->next;
    }
    //next piece of the stack chosen = top piece of stack to move to
    thisPiece->next = board[k][l].stack;
    board[k][l].stack = board[i][j].stack;
// implementation to only allow 5 pieces and remove the rest
    while(thisPiece2 != NULL)
    {
        if (count < 5)
        {
            thisPiece2 = thisPiece2->next;
            count++;
        }
        else
        {
            last = thisPiece2;
        }
        if (last != NULL)
        {
            thisPiece2= thisPiece2->next;
            while (thisPiece2 != NULL)
            {
                toRemove = thisPiece2;
                thisPiece2 = thisPiece2->next;
                if (toRemove->p_color == players[z].player_color)
                {
                    players[z].piecesPlayerOwnsReserve++;

                }
                if (toRemove->p_color != players[z].player_color){
                    players[z].piecesPlayerCaptured++;
                    if (z==1){
                        players[(z-1)].piecesPlayerOwns--;
                    }
                    if (z==0){
                        players[(z+1)].piecesPlayerOwns--;
                    }
                }

                free(toRemove);
            }
            last->next = NULL;
        }

    }
}
