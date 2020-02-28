#include "chess.h"

const int color[13] = {0, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1};
const char symbol[13] = {' ', ' ', 'N', 'B', 'R', 'Q', 'K', ' ', 'N', 'B', 'R', 'Q', 'K'};
const int mobility[13] = {0, 4, 8, 28, 28, 56, 10, 4, 8, 28, 28, 56, 10};
const int iterable[13] = {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0};
const int iterate[56] = {
    7, 7, 7, 7, 7, 7, 7, 
    14, 14, 14, 14, 14, 14, 14, 
    21, 21, 21, 21, 21, 21, 21, 
    28, 28, 28, 28, 28, 28,28,
    35, 35, 35, 35, 35, 35, 35,
    42, 42, 42, 42, 42, 42, 42,
    49, 49, 49, 49, 49, 49, 49,
    56, 56, 56, 56, 56, 56, 56
    };
    
const int movement[13][56][2] = {
    {
        {0, 0}
    },
    {
        {0, -1},{0, -2},{-1, -1},{1, -1}
    },
    {
        {-2, -1},{-1, -2},{1, -2},{2, -1},{2, 1},{1, 2},{-1, 2},{-2, 1}
    },
    {
        {-1, -1},{-2, -2},{-3, -3},{-4, -4},{-5, -5},{-6, -6},{-7, -7},
        {1, -1},{2, -2},{3, -3},{4, -4},{5, -5},{6, -6},{7, -7},
        {1, 1},{2, 2},{3, 3},{4, 4},{5, 5},{6, 6},{7, 7},
        {-1, 1},{-2, 2},{-3, 3},{-4, 4},{-5, 5},{-6, 6},{-7, 7}
    },
    {
        {-1, 0},{-2, 0},{-3, 0},{-4, 0},{-5, 0},{-6, 0},{-7, 0},
        {0, -1},{0, -2},{0, -3},{0, -4},{0, -5},{0, -6},{0, -7},
        {1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},
        {0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7}
    },
    {
        {-1, -1},{-2, -2},{-3, -3},{-4, -4},{-5, -5},{-6, -6},{-7, -7},
        {1, -1},{2, -2},{3, -3},{4, -4},{5, -5},{6, -6},{7, -7},
        {1, 1},{2, 2},{3, 3},{4, 4},{5, 5},{6, 6},{7, 7},
        {-1, 1},{-2, 2},{-3, 3},{-4, 4},{-5, 5},{-6, 6},{-7, 7},
        {-1, 0},{-2, 0},{-3, 0},{-4, 0},{-5, 0},{-6, 0},{-7, 0},
        {0, -1},{0, -2},{0, -3},{0, -4},{0, -5},{0, -6},{0, -7},
        {1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},
        {0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7}
    },
    {
        {-1, 0},{-1, -1},{0, -1},{1, -1},{1, 0},{1, 1},{0, 1},{-1, 1}, {-2, 0}, {2, 0}
    },
    {
        {0, 1},{0, 2},{-1, 1},{1, 1}
    },
    {
        {-2, -1},{-1, -2},{1, -2},{2, -1},{2, 1},{1, 2},{-1, 2},{-2, 1}
    },
    {
        {-1, -1},{-2, -2},{-3, -3},{-4, -4},{-5, -5},{-6, -6},{-7, -7},
        {1, -1},{2, -2},{3, -3},{4, -4},{5, -5},{6, -6},{7, -7},
        {1, 1},{2, 2},{3, 3},{4, 4},{5, 5},{6, 6},{7, 7},
        {-1, 1},{-2, 2},{-3, 3},{-4, 4},{-5, 5},{-6, 6},{-7, 7}
    },
    {
        {-1, 0},{-2, 0},{-3, 0},{-4, 0},{-5, 0},{-6, 0},{-7, 0},
        {0, -1},{0, -2},{0, -3},{0, -4},{0, -5},{0, -6},{0, -7},
        {1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},
        {0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7}
    },
    {
        {-1, -1},{-2, -2},{-3, -3},{-4, -4},{-5, -5},{-6, -6},{-7, -7},
        {1, -1},{2, -2},{3, -3},{4, -4},{5, -5},{6, -6},{7, -7},
        {1, 1},{2, 2},{3, 3},{4, 4},{5, 5},{6, 6},{7, 7},
        {-1, 1},{-2, 2},{-3, 3},{-4, 4},{-5, 5},{-6, 6},{-7, 7},
        {-1, 0},{-2, 0},{-3, 0},{-4, 0},{-5, 0},{-6, 0},{-7, 0},
        {0, -1},{0, -2},{0, -3},{0, -4},{0, -5},{0, -6},{0, -7},
        {1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},
        {0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7}
    },
    {
        {-1, 0},{-1, -1},{0, -1},{1, -1},{1, 0},{1, 1},{0, 1},{-1, 1}, {-2, 0}, {2, 0}
    }
};

const int eval[13][8][8] = {
    {
        //EMPTY
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        //WHITE PAWN
        {20, 20, 20, 20, 20, 20, 20, 20},
        {30, 30, 30, 30, 30, 30, 30, 30},
        {22, 22, 24, 26, 26, 24, 22, 22},
        {21, 21, 22, 25, 25, 22, 21, 21},
        {20, 20, 20, 24, 24, 20, 20, 20},
        {21, 19, 18, 20, 20, 18, 19, 19},
        {21, 22, 22, 16, 16, 22, 22, 21},
        {20, 20, 20, 20, 20, 20, 20, 20}
    },
    {
        //WHITE KNIGHT
        {50, 52, 54, 54, 54, 54, 52, 50},
        {52, 56, 60, 60, 60, 60, 56, 52},
        {54, 60, 62, 63, 63, 62, 60, 54},
        {54, 61, 63, 64, 64, 63, 61, 54},
        {54, 60, 63, 64, 64, 63, 60, 54},
        {54, 61, 62, 63, 63, 62, 61, 54},
        {52, 56, 60, 61, 61, 60, 56, 52},
        {50, 52, 54, 54, 54, 54, 52, 50}
    },
    {
        //WHITE BISHOP
        {56, 58, 58, 58, 58, 58, 58, 56},
        {58, 60, 60, 60, 60, 60, 60, 58},
        {58, 60, 61, 62, 62, 61, 60, 58},
        {58, 61, 61, 62, 62, 61, 61, 58},
        {58, 60, 62, 62, 62, 62, 60, 58},
        {58, 62, 62, 62, 62, 62, 62, 58},
        {58, 61, 60, 60, 60, 60, 61, 58},
        {56, 58, 58, 58, 58, 58, 58, 56}
    },
    {
        //WHITE ROOK
        {100, 100, 100, 100, 100, 100, 100, 100},
        {101, 102, 102, 102, 102, 102, 102, 101},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {100, 100, 100, 101, 101, 100, 100, 100}
    },
    {
        //WHITE QUEEN
        {176, 178, 178, 179, 179, 178, 178, 176},
        {178, 180, 180, 180, 180, 180, 180, 178},
        {178, 180, 181, 181, 181, 181, 180, 178},
        {179, 180, 181, 181, 181, 181, 180, 179},
        {180, 180, 181, 181, 181, 181, 180, 180},
        {178, 181, 181, 181, 181, 181, 180, 178},
        {178, 180, 178, 180, 180, 180, 180, 178},
        {176, 178, 178, 179, 179, 178, 178, 176}
    },
    {
        //WHITE KING
        {74, 72, 72, 70, 70, 72, 72, 74},
        {74, 72, 72, 70, 70, 72, 72, 74},
        {74, 72, 72, 70, 70, 72, 72, 74},
        {74, 72, 72, 70, 70, 72, 72, 74},
        {76, 74, 74, 72, 72, 74, 74, 76},
        {78, 76, 76, 76, 76, 76, 76, 78},
        {84, 84, 80, 80, 80, 80, 84, 84},
        {84, 86, 82, 80, 80, 82, 86, 84}
    },
    {
        //BLACK PAWN
        {-20, -20, -20, -20, -20, -20, -20, -20},
        {-21, -22, -22, -16, -16, -22, -22, -21},
        {-21, -19, -18, -20, -20, -18, -19, -19},
        {-20, -20, -20, -24, -24, -20, -20, -20},
        {-21, -21, -22, -25, -25, -22, -21, -21},
        {-22, -22, -24, -26, -26, -24, -22, -22},
        {-30, -30, -30, -30, -30, -30, -30, -30},
        {-20, -20, -20, -20, -20, -20, -20, -20}
    },
    {
        //BLACK KNIGHT
        {-50, -52, -54, -54, -54, -54, -52, -50},
        {-52, -56, -60, -61, -61, -60, -56, -52},
        {-54, -61, -62, -63, -63, -62, -61, -54},
        {-54, -60, -63, -64, -64, -63, -60, -54},
        {-54, -61, -63, -64, -64, -63, -61, -54},
        {-54, -60, -62, -63, -63, -62, -60, -54},
        {-52, -56, -60, -60, -60, -60, -56, -52},
        {-50, -52, -54, -54, -54, -54, -52, -50}
    },
    {
        //BLACK BISHOP
        {-56, -58, -58, -58, -58, -58, -58, -56},
        {-58, -61, -60, -60, -60, -60, -61, -58},
        {-58, -62, -62, -62, -62, -62, -62, -58},
        {-58, -60, -62, -62, -62, -62, -60, -58},
        {-58, -61, -61, -62, -62, -61, -61, -58},
        {-58, -60, -61, -62, -62, -61, -60, -58},
        {-58, -60, -60, -60, -60, -60, -60, -58},
        {-56, -58, -58, -58, -58, -58, -58, -56}
    },
    {
        //BLACK ROOK
        {-100, -100, -100, -101, -101, -100, -100, -100},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-101, -102, -102, -102, -102, -102, -102, -101},
        {-100, -100, -100, -100, -100, -100, -100, -100}
    },
    {
        //BLACK QUEEN
        {-176, -178, -178, -179, -179, -178, -178, -176},
        {-178, -180, -178, -180, -180, -180, -180, -178},
        {-178, -181, -181, -181, -181, -181, -180, -178},
        {-180, -180, -181, -181, -181, -181, -180, -180},
        {-179, -180, -181, -181, -181, -181, -180, -179},
        {-178, -180, -181, -181, -181, -181, -180, -178},
        {-178, -180, -180, -180, -180, -180, -180, -178},
        {-176, -178, -178, -179, -179, -178, -178, -176}
    },
    {
        //BLACK KING
        {-84, -86, -82, -80, -80, -82, -86, -84},
        {-84, -84, -80, -80, -80, -80, -84, -84},
        {-78, -76, -76, -76, -76, -76, -76, -78},
        {-76, -74, -74, -72, -72, -74, -74, -76},
        {-74, -72, -72, -70, -70, -72, -72, -74},
        {-74, -72, -72, -70, -70, -72, -72, -74},
        {-74, -72, -72, -70, -70, -72, -72, -74},
        {-74, -72, -72, -70, -70, -72, -72, -74}
    }
};

void chess_init(chess_board b)
{
    int i, j;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 9;j++){
            if(j == 1)
                b[i][j] = B_PAWN;
            else if(j == 6)
                b[i][j] = W_PAWN;
            else
                b[i][j] = EMPTY;
        }
    }

    b[0][7] = b[7][7] = W_ROOK;
    b[1][7] = b[6][7] = W_KNIGHT;
    b[2][7] = b[5][7] = W_BISHOP;
    b[3][7] = W_QUEEN;
    b[4][7] = W_KING;
    
    b[0][0] = b[7][0] = B_ROOK;
    b[1][0] = b[6][0] = B_KNIGHT;
    b[2][0] = b[5][0] = B_BISHOP;
    b[3][0] = B_QUEEN;
    b[4][0] = B_KING;
}

void chess_copy(chess_board src, chess_board dst)
{
    int i, j;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 9;j++){
            dst[i][j] = src[i][j];
        }
    }
}

void chess_save(chess_board b, int i, int j, int m, int memory[9])
{
    if(b[i][j] == W_KING && m == 8){
        memory[0] = 1;
    }
    else if(b[i][j] == W_KING && m == 9){
        memory[0] = 2;
    }
    else if(b[i][j] == B_KING && m == 8){
        memory[0] = 3;
    }
    else if(b[i][j] == B_KING && m == 9){
        memory[0] = 4;
    }
    else{
        memory[0] = 0;
        memory[1] = i;
        memory[2] = j;
        memory[3] = b[i][j];
        memory[4] = i + movement[b[i][j]][m][0];
        memory[5] = j + movement[b[i][j]][m][1];
        memory[6] = b[memory[4]][memory[5]];
    }
    memory[7] = b[6][8];
    memory[8] = b[7][8];
}

void chess_undo(chess_board b, int memory[8])
{
    switch(memory[0]){
        case 0 :
        b[memory[1]][memory[2]] = memory[3];
        b[memory[4]][memory[5]] = memory[6];
        break;
        case 1 :
        b[0][7] = W_ROOK;
        b[3][7] = EMPTY;
        b[4][7] = W_KING;
        b[2][7] = EMPTY;
        b[0][8] = b[1][8] = 0;
        break;
        case 2 :
        b[7][7] = W_ROOK;
        b[5][7] = EMPTY;
        b[4][7] = W_KING;
        b[6][7] = EMPTY;
        b[0][8] = b[2][8] = 0;
        break;
        case 3 :
        b[0][0] = B_ROOK;
        b[3][0] = EMPTY;
        b[4][0] = B_KING;
        b[2][0] = EMPTY;
        b[3][8] = b[4][8] = 0;
        break;
        case 4 :
        b[7][0] = B_ROOK;
        b[5][0] = EMPTY;
        b[4][0] = B_KING;
        b[6][0] = EMPTY;
        b[0][8] = b[2][8] = 0;
        break;
    }
    b[6][8] = memory[7];
    b[7][8] = memory[8];
}

void chess_notation(chess_board b, int x1, int y1, int x2, int y2, char *notation)
{
    int i = 0;
    if(b[x1][y1] == W_KING && x1 == 3 && y1 == 7){
        if(x2 == 1 && y2 == 7){
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
        }
        else if(x2 == 6 && y2 == 7){
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
        }
    }else if(b[x1][y1] == B_KING && x1 == 3 && y1 == 0){
        if(x2 == 1 && y2 == 0){
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
        }
        else if(x2 == 6 && y2 == 0){
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
            notation[i++] = '-';
            notation[i++] = 'O';
        }
    }else{
        if(symbol[b[x1][y1]] != ' '){
        notation[i++] = symbol[b[x1][y1]];
        }
        
        if(b[x2][y2] == EMPTY){
            notation[i++] = 'a' + x2;
            notation[i++] = '1' + y2;
        }else{
            notation[i++] = 'x';
            notation[i++] = 'a' + x2;
            notation[i++] = '1' + y2;
        }
    }
    notation[i] = 0;
}

int chess_play_2(chess_board b,int x1, int y1, int x2, int y2)
{
    int m, x, y;
    for(m = 0;m < mobility[b[x1][y1]];m++){
        x = x1 + movement[b[x1][y1]][m][0];
        y = y1 + movement[b[x1][y1]][m][1];
        if(x == x2 && y == y2){
            return (chess_play(b, x1, y1, m))? 1 : 0;
        }
    }
    return 0;
}

int chess_play(chess_board b, int x1, int y1, int m)
{
    int i, tmp_x, tmp_y, x2, y2, can_play = 0;
    enum chess_piece piece_from, piece_to;
    
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7){
        return 0;
    }
    if(m >= mobility[b[x1][y1]]){
        return 0;
    }
    
    piece_from = b[x1][y1];
    
    x2 = x1 + movement[piece_from][m][0];
    y2 = y1 + movement[piece_from][m][1];
    
    if(x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7){
        return 0;
    }
    
    piece_to = b[x2][y2];
    
    if(color[piece_from] == color[piece_to]){
        return 0;
    }
    
    switch(piece_from){
        case W_PAWN:
            if(m == 0){
                if(piece_to == EMPTY){
                    if(y2 == 0){
                        b[x2][y2] = W_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else{
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                    }
                    can_play = 1;
                }
            }
            else if(m == 1){
                if(piece_to == EMPTY){
                    if(y1 == 6 && b[x2][5] == EMPTY){
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                        can_play = 1;
                    }
                }
            }
            else{
                if(color[piece_from] + color[piece_to] == 0){
                    if(y2 == 0){
                        b[x2][y2] = W_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else{
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                    }
                    can_play = 1;
                }
            }
            break;
        case B_PAWN:
            if(m == 0){
                if(piece_to == EMPTY){
                    if(y2 == 7){
                        b[x2][y2] = B_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else{
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                    }
                    can_play = 1;
                }
            }
            else if(m == 1){
                if(piece_to == EMPTY){
                    if(y1 == 1 && b[x2][2] == EMPTY){
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                        can_play = 1;
                    }
                }
            }
            else{
                if(color[piece_from] + color[piece_to] == 0){
                    if(y2 == 7){
                        b[x2][y2] = B_QUEEN;
                        b[x1][y1] = EMPTY;
                    }else{
                        b[x2][y2] = piece_from;
                        b[x1][y1] = EMPTY;
                    }
                    can_play = 1;
                }
            }
            break;
        case W_KNIGHT:
        case B_KNIGHT:
            b[x2][y2] = piece_from;
            b[x1][y1] = EMPTY;
            can_play = 1;
            break;
        case W_BISHOP:
        case B_BISHOP:
        case W_ROOK:
        case B_ROOK:
        case W_QUEEN:
        case B_QUEEN:
            for(i = m - (m % 7);i < m;i++){
                tmp_x = movement[piece_from][i][0];
                tmp_y = movement[piece_from][i][1];
                if(b[x1 + tmp_x][y1 + tmp_y] != EMPTY){
                    return 0;
                }
            } 
            b[x2][y2] = piece_from;
            b[x1][y1] = EMPTY;
            can_play = 1;
            break;
        case W_KING:
            if(m == 8){
                if(b[4][7] == W_KING && b[0][7] == W_ROOK && !b[0][8] && !b[1][8] && !b[1][7] && !b[2][7] && !b[3][7]){
                    b[4][7] = EMPTY;
                    b[2][7] = W_KING;
                    b[0][7] = EMPTY;
                    b[3][7] = W_ROOK;
                    b[0][8] = 1;
                    b[1][8] = 1;
                    can_play = 1;
                }
            }
            else if(m == 9){
                if(b[4][7] == W_KING && b[7][7] == W_ROOK && !b[0][8] && !b[2][8] && !b[5][7] && !b[6][7]){
                    b[4][7] = EMPTY;
                    b[6][7] = W_KING;
                    b[7][7] = EMPTY;
                    b[5][7] = W_ROOK;
                    b[0][8] = 1;
                    b[2][8] = 1;
                    can_play = 1;
                }
            }
            else{
                b[x2][y2] = piece_from;
                b[x1][y1] = EMPTY;
                can_play = 1;
            }
            break;
        case B_KING:
            if(m == 8){
                if(b[4][0] == B_KING && b[0][0] == B_ROOK && !b[3][8] && !b[4][8] && !b[1][0] && !b[2][0] && !b[3][0]){
                    b[4][0] = EMPTY;
                    b[2][0] = B_KING;
                    b[0][0] = EMPTY;
                    b[3][0] = B_ROOK;
                    b[3][8] = 1;
                    b[4][8] = 1;
                    can_play = 1;
                }
            }
            else if(m == 9){
                if(b[4][0] == B_KING && b[7][0] == B_ROOK && !b[3][8] && !b[5][8] && !b[5][0] && !b[6][0]){
                    b[4][0] = EMPTY;
                    b[6][0] = B_KING;
                    b[7][0] = EMPTY;
                    b[5][0] = B_ROOK;
                    b[3][8] = 1;
                    b[5][8] = 1;
                    can_play = 1;
                }
            }
            else{   
                b[x2][y2] = piece_from;
                b[x1][y1] = EMPTY;
                can_play = 1;
            }
            break;
        default:
            return 0;
    }
    
    if(can_play){
        b[7][8] += (eval[b[x2][y2]][x2][y2] - eval[piece_to][x2][y2] - eval[piece_from][x1][y1]);
        if(piece_to == W_KING || piece_to == B_KING){
            b[6][8] = 1;
        }
    }
    return can_play;
}

void chess_play_ai(chess_board b, enum chess_player player, int level)
{
    int i, j, m, best_x, best_y, best_m, status, best_status, memory[9];
    enum chess_piece piece_from;
    
    if(player == WHITE){
        best_status = -10000;
        for(i =8;i--;){
            for(j = 8;j--;){
                piece_from = b[i][j];
                if(color[piece_from] > 0){
                    m = 0;
                    while(m < mobility[piece_from]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(b[6][8]){
                                status = level * 1000;
                            }else{
                                status = chess_min_max(b, player, level - 1, 0, -10000, 10000);
                            }
                            chess_undo(b, memory);
                            
                            if(best_status < status){
                                best_status = status;
                                best_x = i;
                                best_y = j;
                                best_m = m;
                            }
                            m++;
                        }else{
                            m = (iterable[piece_from])? iterate[m] : m + 1;
                        }
                    }
                }
            }
        }
    }
    else{
        best_status = -10000;
        for(i = 8;i--;){
            for(j = 8;j--;){
                piece_from = b[i][j];
                if(color[piece_from] < 0){
                    m = 0;
                    while(m < mobility[piece_from]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(b[6][8]){
                                status = level * 1000;
                            }else{
                                status = chess_min_max(b, player, level - 1, 0, -10000, 10000);
                            }
                            chess_undo(b, memory);
                            
                            if(best_status < status){
                                printf("status : %d\n",status);
                                best_status = status;
                                best_x = i;
                                best_y = j;
                                best_m = m;
                            }
                            m++;
                        }else{
                            m = (iterable[piece_from])? iterate[m] : m + 1;
                        }
                    }
                }
            }
        }
    }
    int x2 = best_x + movement[b[best_x][best_y]][best_m][0];
    int y2 = best_y + movement[b[best_x][best_y]][best_m][1];
    chess_notation(b, best_x, best_y, x2, y2, LAST_MOVEMENT);
    chess_play(b, best_x, best_y, best_m);
}

int chess_min_max(chess_board b, enum chess_player player, int level, _Bool maximize, int alpha, int beta)
{
    int i, j, m, status, best_status, memory[9];
    enum chess_piece piece_from;
    
    if(level == 0){
        return (player == WHITE)? b[7][8] : -b[7][8];
    }
    
    if((player == WHITE && maximize) || (player == BLACK && !maximize)){
        best_status = (maximize)? -10000 : 10000;
        for(i = 8;i--;){
            for(j = 8;j--;){
                piece_from = b[i][j];
                if(color[piece_from] > 0){
                    m = 0;
                    while(m < mobility[piece_from]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(b[6][8]){
                                status = level * ((player == WHITE)? 1000 : -1000);
                            }else{
                                status = chess_min_max(b, player, level - 1, !maximize, alpha, beta);
                            }
                            chess_undo(b, memory);
                            
                            if(maximize){
                                if(best_status < status)best_status = status;
                                if(alpha < best_status)alpha = best_status;
                            }else{
                                if(best_status > status)best_status = status;
                                if(beta > best_status)beta = best_status;
                            }
                            
                            if(beta <= alpha){
                                return best_status;
                            }
                            m++;
                        }else{
                            m = (iterable[piece_from])? iterate[m] : m + 1;
                        }
                    }
                }
            }
        }
    }
    else if((player == WHITE && !maximize) || (player == BLACK && maximize)){
        best_status = (maximize)? -10000 : 10000;
        for(i = 8;i--;){
            for(j = 8;j--;){
                piece_from = b[i][j];
                if(color[piece_from] < 0){
                    m = 0;
                    while(m < mobility[piece_from]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(b[6][8]){
                                status = level * ((player == WHITE)? -1000 : 1000);
                            }else{
                                status = chess_min_max(b, player, level - 1, !maximize, alpha, beta);
                            }
                            chess_undo(b, memory);
                            
                            if(maximize){
                                if(best_status < status)best_status = status;
                                if(alpha < best_status)alpha = best_status;
                            }else{
                                if(best_status > status)best_status = status;
                                if(beta > best_status)beta = best_status;
                            }
                            
                            if(beta <= alpha){
                                return best_status;
                            }
                            m++;
                        }else{
                            m = (iterable[piece_from])? iterate[m] : m + 1;
                        }
                    }
                }
            }
        }
    }
    return best_status;
}