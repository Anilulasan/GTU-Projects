#include "source.h"

using namespace std;

void hex_game() { //Main function.
	int size, choice, test;
	char board[MAXSIZE][MAXSIZE];
	bool load_test = 1;
	decltype(load_test) turn = 0;
	string filename;

	test = menu(size, choice);
	if (test == -1) {
		cout << "Too many invalid entry. You are going to play against computer in 6x6 board." << endl;
		init_board(board);
		display_board(board);
		game(board, filename);
	}
	else {
		init_board(board, size);
		while (load_test != 0) {
			display_board(board, size);
			load_test = game(board, filename, size, choice, turn);
			if (load_test) {
				load(filename, board, size, choice, turn);
				cout << "Your game is succesfully loaded." << endl;
			}
		}
	}
	
}

bool game(char board[][MAXSIZE], std::string &filename, const int size, const int choice, const bool turn) { //Plays the game. Checks winning situation after 5 move played for each player.
	bool win_test = 0, first = 1;
	auto counter = 0, AI_pos_y = 0, AI_pos_x = 0, move_test = 0;
	char pos_x;

	cout << "User 1 will try to connect upper and lower sides" << endl;
	if (choice == 1)
		cout << "Computer";
	else
		cout << "User 2";
	cout << " will try to connect right and left sides" << endl
		<< "Game on!" << endl;
		
	while (win_test == 0) {
		if (turn == 0) {
			cout << "User 1 ";
			move_test = move_user(board, choice, size, user1_mark, filename);
		}
		else {
			cout << "User 2 ";
			move_test = move_user(board, choice, size, user2_mark, filename);
		}
		if (move_test == 2) //Means load
			return 1;
		else if(move_test == 1) { //Means save
			while(move_test == 1) { //Game has to go on in same point everytime user saves the game.
				if (turn == 0) {
					cout << "User 1 ";
					move_test = move_user(board, choice, size, user1_mark, filename);
				}
				else {
					cout << "User 2 ";
					move_test = move_user(board, choice, size, user2_mark, filename);
				}
			}
		}
		display_board(board, size);
		if (counter >= size-1) //Starts to check winning situation after necessary number of moves played.
			win_test = check_win_player1(board, size, 0, 0, 0);
		if (win_test == 0) {
			if (choice == 1) {
				move_AI(board, size, AI_pos_y, AI_pos_x, first);
				board[AI_pos_y][AI_pos_x] = user2_mark;
				pos_x = 'A' + AI_pos_x;
				cout << "Computer Played " << pos_x << AI_pos_y+1 <<endl;
			}
			else {
				if (turn == 1) {
					cout << "User 1 ";
					move_test = move_user(board, choice, size, user1_mark, filename);
				}
				else {
					cout << "User 2 ";
					move_test = move_user(board, choice, size, user2_mark, filename);
				}
			}
			if (move_test == 2) //Means load
				return 1;
			else if(move_test == 1) { //Means save
				while(move_test == 1) {
					if (turn == 1) {
						cout << "User 1 ";
						move_test = move_user(board, choice, size, user1_mark, filename);
					}
					else {
						cout << "User 2 ";
						move_test = move_user(board, choice, size, user2_mark, filename);
					}
				}
			}

			display_board(board, size);
			counter++;
			if (counter > size-1) {
				win_test = check_win_player2(board, size, 0, 0, 0);
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
	return 0;
}

int menu(int &size, int &choice) { //User's choices for the game.
	bool flag = 0;
	int error_counter = 0;
	while (flag == 0) {
		cout << "Please enter the size of the board (between 6 and 12):";
		cin >> size;
		if (size < 6 || size > 12) {
			cout << "Invalid number! Please try again." << endl;
			error_counter++;
			if (error_counter == 10)
				return -1;
		}
		else
			flag = 1;
	}
	while (flag == 1) {
		cout << "1. User vs Computer" <<endl
		<< "2. User vs User" << endl
		<< "Choice:";
		cin >> choice;
		if (choice != 1 && choice != 2) {
			cout << "Invalid number! Please try again." << endl;
			error_counter++;
			if (error_counter == 10)
				return -1;
		}
		else
			flag = 0;
	}
	cin.ignore();
	return 0; 
}

void init_board(char board[][MAXSIZE], const int size) { //Inıtıalizes the board
	int i,j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			board[i][j] = '.';
		}
	}
}

void display_board(char board[][MAXSIZE], const int size) { //Prints the board to screen
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

int check_move_input(const int size, const int pos_y, const int pos_x) { //Checks that is the move input inside the game board.
	if (pos_x >= size || pos_x < 0 || pos_y >= size || pos_y < 0)
		return -1;
	return 0;
}



int move_user(char board[][MAXSIZE], const int choice, const int size, const Hex &symbol, std::string &filename) { //Gets input from user, checks validity, then marks the symbol on the coordinate.
	int input_choice;
	int pos_x, pos_y, test, test2, error_counter = 0;
	do {
		
			cout << "Make a move: ";
			input_choice = get_input(pos_y, pos_x, filename);
			if (input_choice == 0) //Normal move.
				test = check_move_input(size, pos_y, pos_x); 
			else if(input_choice == 1) { //SAVE
				bool turn;
				if (symbol == user1_mark)
					turn = 0;
				else
					turn = 1;
				test = save(board, size, choice, turn, filename);
				if (test) {
					cout << "You have succesfully saved your game." << endl;
				}
				else {
					cout << "Bad file name" << endl;
					error_counter++;
					test = -1;
				}
			}
			else if(input_choice == 2) { //LOAD
				fstream file;
				file.open(filename.c_str());
				if (file) {
					file.close();
					return input_choice;
				}
				else {
					cout << "Bad file name" << endl;
					error_counter++;
					test = -1;
				}
			}
			else
				test = -1;

			if (input_choice == 0) {
				if (test != -1) {
					if (board[pos_y][pos_x] == '.')
						board[pos_y][pos_x] = symbol;
					else {
						test = -1;
						cout << "This coordinate is filled. Please choose a coordinate with '.' symbol." << endl;
					}
				}
				else {
					cout << "Invalid entry. Please enter a coordinate inside the game board." << endl;
					error_counter++;
				}
			}

			if (error_counter == 10) {
					cerr << "Too many invalid entry. Game stopped." << endl;
					exit(0);
			}
		
	}while (test == -1);
	return input_choice;
}

int check_win_player1(char board[][MAXSIZE], const int size, bool flag, int pos_y, int pos_x) { //Checks did player 1 win the game.
	if (flag == 0) { //Flag == 0 means it has to find a symbol at first row.
		int i = 0, test;
		for (i = 0; i < size; i++) { //At the beginning it looks for a user1symbol('X') in first row.
			if (board[0][i] == user1_mark) {
				test = check_win_player1(board, size, 1, 0, i);
				if (test == 1)
					return 1;
			}
		}
		return 0;
	}
	else { //If it finds a user1_mark at first row, now it looks for southeast, south and southwest directions if the chain goes on.(recursively)
		int wtest = 0;
		if (pos_y == size-1) 
			return 1;
		if (pos_x > 0 && board[pos_y+1][pos_x-1] == user1_mark) {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x-1);
			if (wtest == 1) 
				return 1;
		}
		if (board[pos_y+1][pos_x] == user1_mark) {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x);
			if (wtest == 1) 
				return 1;
		}
		if (pos_x < size-1 && board[pos_y+1][pos_x+1] == user1_mark) {
			wtest = check_win_player1(board, size, 1, pos_y+1, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}

int check_win_player2(char board[][MAXSIZE], const int size, bool flag, int pos_y, int pos_x) { //Same logic with check_win_player1.
	if (flag == 0) {
		int i = 0, test;
		for (i = 0; i < size; i++) {
			if (board[i][0] == user2_mark) {
				test = check_win_player2(board, size, 1, i, 0);
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
		if (pos_y > 0 && board[pos_y-1][pos_x+1] == user2_mark) {
			wtest = check_win_player2(board, size, 1, pos_y-1, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		if (board[pos_y][pos_x+1] == user2_mark) {
			wtest = check_win_player2(board, size, 1, pos_y, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		if (pos_y < size-1 && board[pos_y+1][pos_x+1] == user2_mark) {
			wtest = check_win_player2(board, size, 1, pos_y+1, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}

void move_AI(char board[][MAXSIZE], const int size, int &last_pos_y, int &last_pos_x, const bool first) { //Doesn't know anything about defense, just tries to win. Takes the coordinate of his last move and tries to move adjacent to it.
	bool valid = 0;
	if (first == 1) {
		int counter = 0;
		int coor_y;
		while (valid == 0) { //Looks for an empty cell in first column.
			coor_y= rand() % size;
			if (board[coor_y][0] == empty && counter < size*2) {
				valid = 1;
				last_pos_x = 0;
				last_pos_y = coor_y;
			}
			else 
				counter++;
			if (counter >= size*2) { //If the game is loaded and no empty cell in first column. Plays random move.
				int coor_x;
				coor_y= rand() % size;
				coor_x= rand() % size;
				if (board[coor_y][coor_x] == empty) {
					valid = 1;
					last_pos_x = coor_x;
					last_pos_y = coor_y;
				}
			}
		}
	}
	else {
		while (valid == 0) {
			if (last_pos_x == size-1)
				valid = 0;
			else if (last_pos_y > 0 && board[last_pos_y-1][last_pos_x+1] == empty) {
				last_pos_y -= 1;
				last_pos_x += 1;
				valid = 1;
			}
			else if (board[last_pos_y][last_pos_x+1] == empty) {
				last_pos_x += 1;
				valid = 1;
			}
			else if (last_pos_y < size-1 && board[last_pos_y+1][last_pos_x+1] == empty) {
				last_pos_y += 1;
				last_pos_x += 1;
				valid = 1;
			}
			if (valid == 0) { //If no available moves in next column, computer plays random move.
				bool valid1 = 0;
				while (valid1 == 0) {
					last_pos_y = rand() % size;
					last_pos_x = rand() % size;
					if (board[last_pos_y][last_pos_x] == empty) {
						valid1 = 1;
						valid = 1;
					}

				}
			}
		}
	}
}

int get_input(int &input1, int &input2, std::string &filename) {
	string str, command;
	int value;
	getline(cin, str);
	int pos = str.find(' ');
	command = str.substr(0, pos);

	if (command.size() < 4) { //Means its a coordinate
		value = 0;
		input2 = command[0] - 'A';
		if (str[1] == ' ') {
			if (str[3] <= '9' && str[3] >= '0')
				input1 = 10*(str[2] - '0') + str[3] - '0' -1;
			else
				input1 = str[2] - '0' - 1;
		}

	}
	else if (command.compare("SAVE") == 0) { //Means user wants to save the game.
		value = 1;
		filename = str.substr(pos+1, str.size());
	}
	else if(command.compare("LOAD") == 0) { //Means user wants to load a game.
		value = 2;
		filename = str.substr(pos+1, str.size());
	}
	else
		value = -1;

	return value;
}

bool save(char board[][MAXSIZE], const int size, const int choice, const bool turn, const std::string filename) {
	int x, y;
	bool success;
	fstream file;
	file.open(filename.c_str(), fstream::out);
	if (file) {
		file << size << " ";
		file << choice << " ";
		file << turn << " ";
		for (y = 0; y < size; y++) {
			for (x = 0; x < size; x++) {
				if (board[y][x] == user1_mark) {
					file << y << " " << x << " " << user1_mark << " ";
				}
				if (board[y][x] == user2_mark) {
					file << y << " " << x << " " << user2_mark << " ";
				}
			}
		}
		file.close();
		success = 1;
	}
	else
		success = 0;
	return success;
}

void load(const std::string filename, char board[][MAXSIZE], int &size, int &choice, bool &turn) {
	int pos_y, pos_x, mark;
	string s;
	fstream file;
	file.open(filename.c_str());
	file >> size;
	file >> choice;
	file >> turn;
	init_board(board, size);
	while (!file.eof()) {
		file >> pos_y;
		file >> pos_x;
		file >> mark;
		if (mark == user1_mark) 
			board[pos_y][pos_x] = user1_mark;
		else
			board[pos_y][pos_x] = user2_mark;
	}
	file.close();
}

















