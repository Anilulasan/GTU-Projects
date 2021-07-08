#ifndef source_h
#define source_h

#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAXSIZE 12

void menu(int *, int *);
void init_board(char board[][MAXSIZE], int size);
void display_board(char board[][MAXSIZE], int size);
int check_move_input(char input1, int input2, int *pos_y, int *pos_x, int size);
void move_user(char board[][MAXSIZE], int size, char symbol);
int check_win_player1(char board[][MAXSIZE], int size, bool flag, int pos_y, int pos_x, char symbol);
int check_win_player2(char board[][MAXSIZE], int size, bool flag, int pos_y, int pos_x, char symbol);
void game(char board[][MAXSIZE], int size, char user1_sym, char user2_sym, int choice);
void hex_game();
void move_AI(char board[][MAXSIZE], int size, int *last_pos_y, int *last_pos_x, bool first);

#endif