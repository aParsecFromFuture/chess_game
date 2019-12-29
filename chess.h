#ifndef CHESS_H
#define CHESS_H
#include <stdio.h>
#include <stdint.h>

enum chess_piece{
    EMPTY, 
    W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING
    };
    
enum chess_player{
    WHITE = 1, BLACK = -1
    };
    
typedef int8_t chess_board[8][9];

extern int value[13];
extern int color[13];
extern char symbol[13];
extern int mobility[13];
extern int movement[13][56][2]; 
char LAST_MOVEMENT[6];

void chess_init(chess_board);
void chess_copy(chess_board, chess_board);
int chess_status(chess_board, enum chess_player);
int chess_game_over(chess_board);
void chess_save(chess_board, int, int, int, int*);
void chess_undo(chess_board, int*);
void chess_notation(chess_board, int, int, int, int, char*);
int chess_next(enum chess_piece, int);
int chess_play_2(chess_board, int, int, int, int);
int chess_play(chess_board, int, int, int);
void chess_play_ai(chess_board, enum chess_player, int);
int chess_min_max(chess_board, enum chess_player, int, _Bool, int, int);

#endif