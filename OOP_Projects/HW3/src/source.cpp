#include "source.h"

Hex::Hex() {
	size = 6;
	choice = 0;
	turn = 0;
	int y, x;
	for (y = 0; y < size; y++) {
		vector<Cell> c1;
		for (x = 0; x < size; x++) {
			Hex::Cell c(y, x);
			c1.push_back(c);
		}
		hexCells.push_back(c1);
	}
}

int Hex::get_filled() {
	return Cell::filled_cell_count;
}

void Hex::decrement_filled(int number) {
	Cell::filled_cell_count -= number;
}

void Hex::increment_filled(int number) {
	Cell::filled_cell_count += number;
}

bool Hex::Compare_games(Hex other) {
	int num1, num2;
	bool result;
	num1 = count_marked_cells();
	num2 = other.count_marked_cells();
	if (num1 > num2)
		result = 1;
	else
		result = 0;
	return result;
}

int Hex::count_marked_cells() {
	int y, x, counter = 0;
	for (y = 0; y < size; y++) 
		for (x = 0; x < size; x++) 
			if (hexCells[y][x].get_state() != empty)
				counter++;
		
	return counter;
}

int Hex::continue_game() { //Continue to an existing game.
	int move;
	if (turn == 0)
		move = game_flow();
	else {
		bool win_test = 0;

		while (!win_test) {
			do {
				move = play(player2);
				if (move != 0 && move != 2)
					return move;
			}while(move == 2); //Calling play until user doesnt save the game.
			increment_filled(1);
			turn = 0;
			display_board();
			win_test = win_check_p2(0,0,0);
			if (win_test) {
				cout << "User 2 won." << endl;
				return 0;
			}	
			do {
				move = play(player1);
				if (move != 0 && move != 2)
					return move;
			}while(move == 2);
			increment_filled(1);
			turn = 1;
			display_board();
			win_test = win_check_p1(0,0,0);
			if (win_test) {
				cout << "User 1 won." << endl;
				return 0;
			}

		}
	}
	return move;
}

int Hex::playGame() { //Play new game.
	menu();
	init_board();
	display_board();
	int result = game_flow();
	return result;
}

int Hex::game_flow() { //Default game flow which user1 starts.
	int last_pos_y, last_pos_x, move;
	bool first = 1;
	decltype(first) win_test = 0;

	while (!win_test) {
		do {
			move = play(player1);
			if (move != 0 && move != 2)
				return move;
		}while(move == 2);
		increment_filled(1);
		turn = 1;
		display_board();
		win_test = win_check_p1(0,0,0);
		if (win_test) {
			cout << "User 1 won." << endl;
			return 0;
		}
		if (choice == 1)
			do {
				move = play(player2);
				if (move != 0 && move != 2)
					return move;
			}while(move == 2);
		else
			play(last_pos_y, last_pos_x, first);
		increment_filled(1);
		turn = 0;
		display_board();
		win_test = win_check_p2(0,0,0);
		if (win_test) {
			cout << "User 2 won." << endl;
			return 0;
		}

		first = 0;
	}
	return move;
}

const void Hex::init_board() {
	int i, y, x;
	hexCells.resize(size);
	for (i = 0; i < size; i++) 
		hexCells[i].resize(size);
}

const void Hex::display_board() {
	int y, x;
	char letter = 'a';
	cout << " ";
	for (x = 0; x < size; x++) {
		cout << letter;
		letter++;
	}
	cout << endl;
	
	for (y = 0; y < size; y++) {
		cout << y+1;
		for (x = -1; x < y; x++)
			cout << " ";
		for (x = 0; x <size; x++) 
			fix_print(hexCells[y][x].get_state());
		cout << endl;
	}
	
}

const void Hex::menu() {
	int choice2;
	auto error_counter = 0;
	bool test = 1;
	do {
		cout << "Please enter the size of the board: ";
		cin >> size;
		if (size < 6) {
			cout << "Size must be greater than 5. Try again." << endl;
			error_counter++;
			if (error_counter == 10) {
				cerr << "Too many invalid entry. Game stopped..." << endl;
				exit(0);
			}
			test = 0;
		}
		else
			test = 1;
	}while (test == 0);
	do {
		cout << "1.User vs Computer" << endl
		<< "2.User vs User" << endl
		<< "Choice: ";
		cin >> choice2;
		if (choice2 != 1 && choice2 != 2) {
			cout << "Invalid entry. Try again" << endl;
			error_counter++;
			if (error_counter == 10) {
				cerr << "Too many invalid entry. Game stopped..." << endl;
				exit(0);
			}
		}
		else {
			test = 1;
			choice = --choice2;
		}
	
	}while(test == 0);
	cin.ignore();
}

const void Hex::fix_print(const Cell_state form) { //Cout prints enum types as integers, so this function fixes that.
	if (form == empty)
		cout << '.';
	else if(form == player1)
		cout << 'X';
	else
		cout << 'O';
}

const void Hex::play(int &last_pos_y, int &last_pos_x, const bool first) { //Doesn't know anything about defense, just tries to win. Takes the coordinate of his last move and tries to move adjacent to it.
	bool valid = 0;
	if (first == 1) {
		int counter = 0;
		int coor_y;
		while (valid == 0) { //Looks for an empty cell in first column.
			coor_y= rand() % size;
			if (hexCells[coor_y][0].get_state() == empty && counter < size*2) {
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
				if (hexCells[coor_y][coor_x].get_state() == empty) {
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
			else if (last_pos_y > 0 && hexCells[last_pos_y-1][last_pos_x+1].get_state() == empty) {
				last_pos_y -= 1;
				last_pos_x += 1;
				valid = 1;
			}
			else if (hexCells[last_pos_y][last_pos_x+1].get_state() == empty) {
				last_pos_x += 1;
				valid = 1;
			}
			else if (last_pos_y < size-1 && hexCells[last_pos_y+1][last_pos_x+1].get_state() == empty) {
				last_pos_y += 1;
				last_pos_x += 1;
				valid = 1;
			}
			if (valid == 0) { //If no available moves in next column, computer plays random move.
				bool valid1 = 0;
				while (valid1 == 0) {
					last_pos_y = rand() % size;
					last_pos_x = rand() % size;
					if (hexCells[last_pos_y][last_pos_x].get_state() == empty) {
						valid1 = 1;
						valid = 1;
					}

				}
			}
		}
	}
	char letter = 'A';
	letter += last_pos_x;
	cout << "Computer played " << letter << " " << last_pos_y+1 << endl;
	hexCells[last_pos_y][last_pos_x].set_state(player2);

}



int Hex::play(const Cell_state user_mark) { //Gets input from user, checks validity, then marks the symbol on the coordinate.
	int user_choice, input1, input2, test, error_counter = 0;
	do {
		cout << "Make a move: ";
		user_choice = get_input(input1, input2);
		test = user_choice;
		if (user_choice == 0) { //Means its a coordinate.
			test = check_move_input(input1, input2);
			if (!test) {
				hexCells[input1][input2].set_state(user_mark);
			}
			else
				error_counter++;
		}
		else if(user_choice == 6)
			return test;
		else if(user_choice == -1){
			cout << "Invalid entry. Please try again." << endl;
			error_counter++;
		}
		if (error_counter == 10) {
			cerr << "Too many invalid entry. Game stopped" << endl;
			exit(0);
		}
	}while(test%2 == 1); //If save fails, it returns 3. If load fails, it returns 5. So if test is an odd number, thats invalid input.
	return test;
}

const int Hex::check_move_input(const int pos_y, const int pos_x) { //Checks that is the move input inside the game board.
	int result = 0;
	if (pos_x >= size || pos_x < 0 || pos_y >= size || pos_y < 0) {
		result = 3;
		cout << "Please enter a coordinate inside the game board." << endl;
	}
	else if (hexCells[pos_y][pos_x].get_state() != empty) {
		result = 3;
		cout << "The coordinate you are trying to move is not empty. Please choose an empty coordinate" << endl;
	}
	return result;
}

int Hex::get_input(int &input1, int &input2) {
	string str, command, filename;
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
		int test;
		value = 2;
		filename = str.substr(pos+1, str.size());
		test = save(filename);
		if (!test)
			value++;
	}
	else if(command.compare("LOAD") == 0) { //Means user wants to load a game.
		int test;
		value = 4;
		filename = str.substr(pos+1, str.size());
		test = load(filename);
		if (!test)
			value++;
	}
	else if(command.compare("MENU") == 0)//Means user wants to return to main menu.
		value = 6;
	else if(command.compare("COMPARE") == 0)
		value = 8;
	else //Means invalid entry.
		value = 1;

	return value;
}

bool Hex::write_to_file(const string filename) { 
	fstream file;
	int success;
	file.open(filename.c_str(), fstream::out);
	if (file) {
		int y, x;
		file << size << " ";
		file << choice << " ";
		file << turn << " ";
		for (y = 0; y < size; y++) {
			for (x = 0; x < size; x++) {
				if (hexCells[y][x].get_state() == player1) {
					file << y << " " << x << " " << player1 << " ";
				}
				if (hexCells[y][x].get_state() == player2) {
					file << y << " " << x << " " << player2 << " ";
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

bool Hex::read_from_file(const string filename) { //Loads the game. Deletes all marked cells from our static variable, then adds the loaded games marks.
	fstream file;
	int success = 0;
	file.open(filename.c_str());
	if (file) {
		decrement_filled(count_marked_cells());
		file >> size;
		file >> choice;
		file >> turn;
		init_board();

		int pos_y, pos_x, mark;
		while (!file.eof()) {
			file >> pos_y;
			file >> pos_x;
			file >> mark;
			if (mark == player1)
				hexCells[pos_y][pos_x].set_state(player1);
			else
				hexCells[pos_y][pos_x].set_state(player2);		
		}
		increment_filled(count_marked_cells());
		success++;
		file.close();
	}
	return success;
}

bool Hex::save(const string filename) {
	int test;
	test = write_to_file(filename);
	if (test)
		cout << "Your game succesfully saved" << endl;
	else
		cout << "Bad file name";
	return test;
}

bool Hex::load(const string filename) {
	int test;
	test = read_from_file(filename);
	if (test)
		cout << "Your game succesfully loaded" << endl;
	else
		cout << "Bad file name" << endl;
	return test;
}

bool Hex::win_check_p1(const bool flag, int pos_y, int pos_x) { //Checks did player 1 win the game.
	if (flag == 0) { //Flag == 0 means it has to find a symbol at first row.
		int i, test;
		for (i = 0; i < size; i++) { //At the beginning it looks for a user1symbol('X') in first row.
			if (hexCells[pos_y][i].get_state() == player1) {
				test = win_check_p1(1, 0, i);
				if (test == 1)
					return 1;
			}
		}
	}
	else { //If it finds a user1_mark at first row, now it looks for southeast, south and southwest directions if the chain goes on.(recursively)
		bool wtest = 0;
		if (pos_y == size-1) 
			return 1;
		if (pos_x > 0 && hexCells[pos_y+1][pos_x-1].get_state() == player1) {
			wtest = win_check_p1(1, pos_y+1, pos_x-1);
			if (wtest == 1) 
				return 1;
		}
		if (hexCells[pos_y+1][pos_x].get_state() == player1) {
			wtest = win_check_p1(1, pos_y+1, pos_x);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}

bool Hex::win_check_p2(const bool flag, int pos_y, int pos_x) {
	if (flag == 0) {
		int i = 0, test;
		for (i = 0; i < size; i++) {
			if (hexCells[i][0].get_state() == player2) {
				test = win_check_p2(1, i, 0);
				if (test == 1)
					return 1;
			}
		}
	}
	else {
		bool wtest = 0;
		if (pos_x == size-1) 
			return 1;
		if (pos_y > 0 && hexCells[pos_y-1][pos_x+1].get_state() == player2) {
			wtest = win_check_p2(1, pos_y-1, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		if (hexCells[pos_y][pos_x+1].get_state() == player2) {
			wtest = win_check_p2(1, pos_y, pos_x+1);
			if (wtest == 1) 
				return 1;
		}
		return 0;
	}
	return 0;
}


