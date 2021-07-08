#ifndef source_h
#define source_h

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#define MAXSIZE 12

enum Hex{user1_mark = 'X', user2_mark = 'O', empty = '.'};

int menu(int &, int &);
void init_board(char board[][MAXSIZE], const int size = 6);
void display_board(char board[][MAXSIZE], const int size = 6);
int check_move_input(const int size, const int pos_y, const int pos_x);
int move_user(char board[][MAXSIZE], const int choice, const int size, const Hex &symbol, std::string &filename);
int check_win_player1(char board[][MAXSIZE], const int size, bool flag, int pos_y, int pos_x);
int check_win_player2(char board[][MAXSIZE], const int size, bool flag, int pos_y, int pos_x);
bool game(char board[][MAXSIZE], std::string &filename, const int size = 6, const int choice = 1, const bool turn = 0);
void hex_game();
void move_AI(char board[][MAXSIZE], const int size, int &last_pos_y, int &last_pos_x, const bool first);
int get_input(int &input1, int &input2, std::string &filename);
bool save(char board[][MAXSIZE], const int size, const int choice, const bool turn, const std::string filename);
void load(const std::string filename, char board[][MAXSIZE], int &size, int &choice, bool &turn);

#endif