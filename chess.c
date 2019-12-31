#include "chess.h"

int value[13] = {0, 3, 9, 9, 15, 30, 200, -3, -9, -9, -15, -30, -200};
int color[13] = {0, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1};
char symbol[13] = {' ', ' ', 'N', 'B', 'R', 'Q', 'K', ' ', 'N', 'B', 'R', 'Q', 'K'};
int mobility[13] = {0, 4, 8, 28, 28, 56, 10, 4, 8, 28, 28, 56, 10};
int movement[13][56][2] = {
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

int chess_status(chess_board b, enum chess_player p)
{
    int status = 0;
    
    status = value[b[0][0]] + value[b[1][0]] + value[b[2][0]] + value[b[3][0]] + \
                 value[b[4][0]] + value[b[5][0]] + value[b[6][0]] + value[b[7][0]] + \
                 value[b[0][1]] + value[b[1][1]] + value[b[2][1]] + value[b[3][1]] + \
                 value[b[4][1]] + value[b[5][1]] + value[b[6][1]] + value[b[7][1]] + \
                 value[b[0][2]] + value[b[1][2]] + value[b[2][2]] + value[b[3][2]] + \
                 value[b[4][2]] + value[b[5][2]] + value[b[6][2]] + value[b[7][2]] + \
                 value[b[0][3]] + value[b[1][3]] + value[b[2][3]] + value[b[3][3]] + \
                 value[b[4][3]] + value[b[5][3]] + value[b[6][3]] + value[b[7][3]] + \
                 value[b[0][4]] + value[b[1][4]] + value[b[2][4]] + value[b[3][4]] + \
                 value[b[4][4]] + value[b[5][4]] + value[b[6][4]] + value[b[7][4]] + \
                 value[b[0][5]] + value[b[1][5]] + value[b[2][5]] + value[b[3][5]] + \
                 value[b[4][5]] + value[b[5][5]] + value[b[6][5]] + value[b[7][5]] + \
                 value[b[0][6]] + value[b[1][6]] + value[b[2][6]] + value[b[3][6]] + \
                 value[b[4][6]] + value[b[5][6]] + value[b[6][6]] + value[b[7][6]] + \
                 value[b[0][7]] + value[b[1][7]] + value[b[2][7]] + value[b[3][7]] + \
                 value[b[4][7]] + value[b[5][7]] + value[b[6][7]] + value[b[7][7]];
                 
                 
    status += color[b[2][2]] + color[b[3][2]] + color[b[4][2]] + color[b[5][2]] + \
                 color[b[2][3]] + color[b[3][3]] + color[b[4][3]] + color[b[5][3]] + \
                 color[b[2][4]] + color[b[3][4]] + color[b[4][4]] + color[b[5][4]] + \
                 color[b[2][5]] + color[b[3][5]] + color[b[4][5]] + color[b[5][5]];
                 
    status += color[b[3][3]] + color[b[4][3]] + color[b[3][4]] + color[b[4][4]];
        
    return (p == WHITE)? status : -status;
}

int chess_game_over(chess_board b)
{
    int i, j, white_king_is_living = 0, black_king_is_living = 0;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 8;j++){
            if(b[i][j] == W_KING){
                white_king_is_living = 1;
            }
            if(b[i][j] == B_KING){
                black_king_is_living = 1;
            }
        }
    }
    if(!white_king_is_living || !black_king_is_living){
        return 1;
    }
    return 0;
}

void chess_save(chess_board b, int i, int j, int m, int memory[7])
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
}

void chess_undo(chess_board b, int memory[7])
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

int chess_next(enum chess_piece p, int m)
{
    if(mobility[p] <= m){
        return -1;
    }
    if(p == W_BISHOP || p == B_BISHOP || p == W_ROOK || p == B_ROOK || p == W_QUEEN || p == B_QUEEN){
        return m - (m % 7) + 7; 
    }else{
        return m + 1;
    }
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
    int i, tmp_x, tmp_y, x2, y2;
    
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7){
        return 0;
    }
    if(m >= mobility[b[x1][y1]]){
        return 0;
    }
    
    x2 = x1 + movement[b[x1][y1]][m][0];
    y2 = y1 + movement[b[x1][y1]][m][1];
    
    if(x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7){
        return 0;
    }
    if(value[b[x1][y1]] * value[b[x2][y2]] > 0){
        return 0;
    }
    
    switch(b[x1][y1]){
        case W_PAWN:
        case B_PAWN:
            if(m == 0){
                if(b[x2][y2] == EMPTY){
                    if(b[x1][y1] == W_PAWN && y2 == 0){
                        b[x2][y2] = W_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else if(b[x1][y1] == B_PAWN && y2 == 7){
                        b[x2][y2] = B_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else{
                        b[x2][y2] = b[x1][y1];
                        b[x1][y1] = EMPTY;
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
            else if(m == 1){
                if(b[x2][y2] == EMPTY){
                    if(b[x1][y1] == W_PAWN && y1 == 6 && b[x2][5] == EMPTY){
                        b[x2][y2] = b[x1][y1];
                        b[x1][y1] = EMPTY;
                        return 1;
                    }
                    else if(b[x1][y1] == B_PAWN && y1 == 1 && b[x2][2] == EMPTY){
                        b[x2][y2] = b[x1][y1];
                        b[x1][y1] = EMPTY;
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }else{
                    return 0;
                }
            }
            else{
                if(value[b[x1][y1]] * value[b[x2][y2]] < 0){
                    if(b[x1][y1] == W_PAWN && y2 == 0){
                        b[x2][y2] = W_QUEEN;
                        b[x1][y1] = EMPTY;
                    }
                    else if(b[x1][y1] == B_PAWN && y2 == 7){
                        b[x2][y2] = B_QUEEN;
                        b[x1][y1] = EMPTY;
                    }else{
                        b[x2][y2] = b[x1][y1];
                        b[x1][y1] = EMPTY;
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
        case W_KNIGHT:
        case B_KNIGHT:
            b[x2][y2] = b[x1][y1];
            b[x1][y1] = EMPTY;
            return 1;
        case W_KING:
            if(m == 8){
                if(b[4][7] == W_KING && b[0][7] == W_ROOK && !b[0][8] && !b[1][8] && !b[1][7] && !b[2][7] && !b[3][7]){
                    b[4][7] = EMPTY;
                    b[2][7] = W_KING;
                    b[0][7] = EMPTY;
                    b[3][7] = W_ROOK;
                    b[0][8] = 1;
                    b[1][8] = 1;
                    return 1;
                }else{
                    return 0;
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
                    return 1;
                }else{
                    return 0;
                }
            }
            else{
                b[x2][y2] = b[x1][y1];
                b[x1][y1] = EMPTY;
                return 1;
            }
        case B_KING:
            if(m == 8){
                if(b[4][0] == B_KING && b[0][0] == B_ROOK && !b[3][8] && !b[4][8] && !b[1][0] && !b[2][0] && !b[3][0]){
                    b[4][0] = EMPTY;
                    b[2][0] = B_KING;
                    b[0][0] = EMPTY;
                    b[3][0] = B_ROOK;
                    b[3][8] = 1;
                    b[4][8] = 1;
                    return 1;
                }else{
                    return 0;
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
                    return 1;
                }else{
                    return 0;
                }
            }
            else{   
                b[x2][y2] = b[x1][y1];
                b[x1][y1] = EMPTY;
                return 1;
            }
        case W_BISHOP:
        case B_BISHOP:
        case W_ROOK:
        case B_ROOK:
        case W_QUEEN:
        case B_QUEEN:
            for(i = m - (m % 7);i < m;i++){
                tmp_x = movement[b[x1][y1]][i][0];
                tmp_y = movement[b[x1][y1]][i][1];
                if(b[x1 + tmp_x][y1 + tmp_y] != EMPTY){
                    return 0;
                }
            }
            if(value[b[x1][y1]] * value[b[x2][y2]] <= 0){      
                b[x2][y2] = b[x1][y1];
                b[x1][y1] = EMPTY;
                return 1;
            }
        default:
            return 0;
    }
}

void chess_play_ai(chess_board b, enum chess_player player, int level)
{
    int i, j, m, best_x, best_y, best_m, status, best_status, memory[7];
    if(player == WHITE){
        best_status = -10000;
        for(i = 0;i < 8;i++){
            for(j = 0;j < 8;j++){
                if(value[b[i][j]] > 0){
                    m = 0;
                    while(m < mobility[b[i][j]]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(chess_game_over(b)){
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
                            m = chess_next(b[i][j], m);
                            if(m == -1)break;
                        }
                    }
                }
            }
        }
    }
    else if(player == BLACK){
        best_status = -10000;
        for(i = 0;i < 8;i++){
            for(j = 0;j < 8;j++){
                if(value[b[i][j]] < 0){
                    m = 0;
                    while(m < mobility[b[i][j]]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(chess_game_over(b)){
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
                            m = chess_next(b[i][j], m);
                            if(m == -1)break;
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
    int i, j, m, status, best_status, memory[7];
    if(level == 0){
        return chess_status(b, player);
    }
    
    if((player == WHITE && maximize) || (player == BLACK && !maximize)){
        best_status = (maximize)? -10000 : 10000;
        for(i = 0;i < 8;i++){
            for(j = 0;j < 8;j++){
                if(value[b[i][j]] > 0){
                    m = 0;
                    while(m < mobility[b[i][j]]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(chess_game_over(b)){
                                status = level * ((player == WHITE)? 1000 : -1000);
                            }else{
                                status = chess_min_max(b, player, level - 1, !maximize, alpha, beta);
                            }
                            chess_undo(b, memory);
                            
                            if(maximize && best_status < status){
                                best_status = status;
                            }
                            if(!maximize && best_status > status){
                                best_status = status;
                            }
                            if(maximize && alpha < best_status){
                                alpha = best_status;
                            }
                            if(!maximize && beta > best_status){
                                beta = best_status;
                            }
                            if(beta <= alpha){
                                return best_status;
                            }
                            m++;
                        }else{
                            m = chess_next(b[i][j], m);
                            if(m == -1)break;
                        }
                    }
                }
            }
        }
    }
    else if((player == WHITE && !maximize) || (player == BLACK && maximize)){
        best_status = (maximize)? -10000 : 10000;
        for(i = 0;i < 8;i++){
            for(j = 0;j < 8;j++){
                if(value[b[i][j]] < 0){
                    m = 0;
                    while(m < mobility[b[i][j]]){
                        chess_save(b, i, j, m, memory);
                        if(chess_play(b, i, j, m)){
                            if(chess_game_over(b)){
                                status = level * ((player == WHITE)? -1000 : 1000);
                            }else{
                                status = chess_min_max(b, player, level - 1, !maximize, alpha, beta);
                            }
                            chess_undo(b, memory);
                            
                            if(maximize && best_status < status){
                                best_status = status;
                            }
                            if(!maximize && best_status > status){
                                best_status = status;
                            }
                            if(maximize && alpha < best_status){
                                alpha = best_status;
                            }
                            if(!maximize && beta > best_status){
                                beta = best_status;
                            }
                            if(beta <= alpha){
                                return best_status;
                            }
                            m++;
                        }else{
                            m = chess_next(b[i][j], m);
                            if(m == -1)break;
                        }
                    }
                }
            }
        }
    }
    return best_status;
}