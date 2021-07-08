#include "source.h"

using namespace std;

void hex_game() { //Main function.
	int size, choice;
	char board[MAXSIZE][MAXSIZE];
	const char user1_sym = 'X', user2_sym = 'O';
	menu(&size, &choice);
	init_board(board, size);
	display_board(board, size);
	game(board, size, user1_sym, user2_sym, choice);
}

void game(char board[][MAXSIZE], int size, char user1_sym, char user2_sym, int choice) { //Plays the game. Checks winning situation after 5 move played for each player.
	bool win_test = 0, first = 1;
	int counter = 0, AI_pos_y = 0, AI_pos_x = 0;
	char pos_x;

	cout << "User 1 will try to connect upper and lower sides" << endl;
	if (choice == 1)
		cout << "Computer";
	else
		cout << "User 2";
	cout << " will try to connect right and left sides" << endl
		<< "Game on!" << endl;
		
	while (win_test == 0) {
		cout << "User 1 ";
		move_user(board, size, user1_sym);
		display_board(board, size);
		if (counter >= size-1) //Starts to check winning situation after necessary number of moves played.
			win_test = check_win_player1(board, size, 0, 0, 0, user1_sym);
		if (win_test == 0) {
			if (choice == 1) {
				move_AI(board, size, &AI_pos_y, &AI_pos_x, first);
				board[AI_pos_y][AI_pos_x] = user2_sym;
				pos_x = 'A' + AI_pos_x;
				cout << "Computer Played " << pos_x << AI_pos_y+1 <<endl;
			}
			else {
				cout << "User 2 ";
				move_user(board, size, user2_sym);
			}

			display_board(board, size);
			counter++;
			if (counter > size-1) {
				win_test = check_win_player2(board, size, 0, 0, 0, user2_sym);
				if (win_test == 1) {
					if (choice == 1)
						cout << "Computer Won!!!" << endl;
					else
						cout << "User 2 Won!!!" << endl;
				}
			}
			first = 0;
		}
		else
			cout << "User 1 Won!!!" << endl;
	}
}

void menu(int *size, int *choice) { //User's choices for the game.
	bool flag = 0;
	while (flag == 0) {
		cout << "Please enter the size of the board (between 6 and 12):";
		cin >> *size;
		if (*size < 6 || *size > 12)
			cout << "Invalid number! Please try again." << endl;
		else
			flag = 1;
	}
	while (flag == 1) {
		cout << "1. User vs Computer" <<endl
		<< "2. User vs User" << endl
		<< "Choice:";
		cin >> *choice;
		if (*choice != 1 && *choice != 2)
			cout << "Invalid number! Please try again." << endl;
		else
			flag = 0;
	} 
}

void init_board(char board[][MAXSIZE], int size) { //Inıtıalizes the board
	int i,j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			board[i][j] = '.';
		}
	}
}

void display_board(char board[][MAXSIZE], int size) { //Prints the board to screen
	int i, j, k;
	char x_axis[] = "abcdefghijkl";
	cout << " ";
	for (i = 0; i < size; i++) 
		cout << "" << x_axis[i];
	cout << endl;
	for(i = 0; i < size; ++i) {
		cout << "" << i+1;
		for (k = -1; k < i; k++) {
			cout << " ";
		}
		for(j = 0; j < size; ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

int check_move_input(char input1, int input2, int *pos_y, int *pos_x, int size) { //Checks that is the move input inside the game board.
	*pos_x = input1 - 'A';
	*pos_y = input2-1;
	if (*pos_x >= size || *pos_x < 0 || *pos_y >= size || *pos_y < 0)
		return -1;
	return 0;
}



void move_user(char board[][MAXSIZE], int size, char symbol) { //Gets input from user, checks validity, then marks the symbol on the coordinate.
	char input1;
	int input2;
	int pos_x, pos_y, test;
	do {
		cout << "Make a move: ";
		cin >> input1 >> input2;
		test = check_move_input(input1, input2, &pos_y, &pos_x, size);
		if (test != -1) {
			if (board[pos_y][pos_x] == '.')
				board[pos_y][pos_x] = symbol;
			else {
				test = -1;
				cout << "This coordinate is filled. Please choose a coordinate with '.' symbol." << endl;
			}
		}
		else
			cout << "Invalid entry. Please enter a coordinate inside the game board." << endl;
	}while (test == -1);
	
}

int check_win_player1(char board[][MAXSIZE], int size, bool flag, int pos_y, int pos_x, char symbol) { //Checks did player 1 win the game.
	if (flag == 0) { //Flag == 0 means it has to find a symbol at first row.
		int i = 0, test;
		for (i = 0; i < size; i++) { //At the beginning it looks for a user1symbol('X') in first row.
			if (board[0][i] == symbol) {
				test = check_win_player1(board, size, 1, 0, i, symbol);
				if (test == 1)
					return 1;
			}
		}
		return 0;
	}
	else { //If it finds a symbol at first row, now it looks for southeast, south and southwest directions if the chain goes on.(recursively)
		int wtest = 0;
		if (pos_y == size-1) 
			return 1;
		if (pos_x > 0 && board[pos_y+1][pos_x-1] == 'X') {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x-1, symbol);
			if (wtest == 1) 
				return 1;
		}
		if (board[pos_y+1][pos_x] == 'X') {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x, symbol);
			if (wtest == 1) 
				return 1;
		}
		if (pos_x < size-1 && board[pos_y+1][pos_x+1] == 'X') {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x+1, symbol);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}

int check_win_player2(char board[][MAXSIZE], int size, bool flag, int pos_y, int pos_x, char symbol) { //Same logic with check_win_player1.
	if (flag == 0) {
		int i = 0, test;
		for (i = 0; i < size; i++) {
			if (board[i][0] == symbol) {
				test = check_win_player2(board, size, 1, i, 0, symbol);
				if (test == 1)
					return 1;
			}
		}
		return 0;
	}
	else {
		int wtest = 0;
		if (pos_x == size-1) 
			return 1;
		if (pos_y > 0 && board[pos_y-1][pos_x+1] == symbol) {
			wtest = check_win_player2(board, size, 1, pos_y-1, pos_x+1, symbol);
			if (wtest == 1) 
				return 1;
		}
		if (board[pos_y][pos_x+1] == symbol) {
			wtest = check_win_player2(board, size, 1, pos_y, pos_x+1, symbol);
			if (wtest == 1) 
				return 1;
		}
		if (pos_y < size-1 && board[pos_y+1][pos_x+1] == symbol) {
			wtest = check_win_player2(board, size, 1, pos_y+1, pos_x+1, symbol);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}

void move_AI(char board[][MAXSIZE], int size, int *last_pos_y, int *last_pos_x, bool first) { //Doesn't know anything about defense, just tries to win. Takes the coordinate of his last move and tries to move adjacent to it.
	bool valid = 0;
	if (first == 1) {
		int coor_y;
		while (valid == 0) {
			coor_y= rand() % size;
			if (board[coor_y][0] == '.') {
				valid = 1;
				*last_pos_x = 0;
				*last_pos_y = coor_y;
			}
		}
	}
	else {
		while (valid == 0)
			if (*last_pos_y > 0 && board[*last_pos_y-1][*last_pos_x+1] == '.') {
				*last_pos_y -= 1;
				*last_pos_x += 1;
				valid = 1;
			}
			else if (board[*last_pos_y][*last_pos_x+1] == '.') {
				*last_pos_x += 1;
				valid = 1;
			}
			else if (*last_pos_y < size-1 && board[*last_pos_y+1][*last_pos_x+1] == '.') {
				*last_pos_y += 1;
				*last_pos_x += 1;
				valid = 1;
			}
			else {
				bool valid1 = 0;
				while (valid1 == 0) {
					*last_pos_y = rand() % size;
					*last_pos_x = rand() % size;
					if (board[*last_pos_y][*last_pos_x] == '.') {
						valid1 = 1;
						valid = 1;
					}

				}
			}
	}
}
