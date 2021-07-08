#include "AbstractHex.h"

namespace HexGame {
	AbstractHex::AbstractHex() {
		size = 6;
		choice = 0;
		turn = 0;
	}

	void AbstractHex::print() const{
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
			for (x = 0; x < size; x++)  {
				fix_print((*this)(y,x));
			}
			cout << endl;
		}
	}

	void AbstractHex::fix_print(const Cell_state form) const{ //Cout prints enum types as integers, so this function fixes that.
		if (form == empty)
			cout << '.';
		else if(form == player1)
			cout << 'X';
		else
			cout << 'O';
	}

	bool AbstractHex::writeToFile(const string filename) const{
		fstream file;
		bool success = true;
		file.open(filename.c_str(), fstream::out);
		if (file) {
			file << size << " ";
			file << choice << " ";
			file << turn << " ";

			for (auto p:move_order) {
				int y, x;
				convert_to_coordinate(p, y, x);	
				file << y << " " << x << " " << (*this)(y,x) << " ";
			}
			file.close();
		}
		else
			success = false;
		return success;
	}

	bool AbstractHex::save(const string filename) const{
		int test;
		test = writeToFile(filename);
		if (test)
			cout << "Your game succesfully saved" << endl;
		else
			cout << "Bad file name";
		return test;
	}

	void AbstractHex::setSize(const int board_size) {
		if (board_size > 5) {
			reset();
			size = board_size;
			resize_board();
			move_order.clear();
		}
	}

	Cell AbstractHex::lastMove() {
		if (move_order.size() == 0)
			throw moveException();
		int cell_id, y, x;
		Cell last;
		Cell_state state;
		cell_id = move_order.back();
		convert_to_coordinate(cell_id, y, x);
		if (move_order.size() % 2 == 0)
			state = player2;
		else
			state = player1;
		last.set_coordinates(y, x, state);
		return last;
	}

	int AbstractHex::get_size() const{
		return size;
	}

	void AbstractHex::menu() {
		int choice_i, size_i;
		auto error_counter = 0;
		bool test = 1;
		do {
			cout << "Please enter the size of the board: ";
			cin >> size_i;
			if (size_i < 6) {
				cout << "Size must be greater than 5. Try again." << endl;
				error_counter++;
				if (error_counter == 10) {
					cerr << "Too many invalid entry. Game stopped..." << endl;
					exit(0);
				}
				test = 0;
			}
			else {
				size = size_i;
				test = 1;
			}
		}while (test == 0);
		
		do {
			cout << "1.User vs Computer" << endl
			<< "2.User vs User" << endl
			<< "Choice: ";
			cin >> choice_i;
			if (choice_i != 1 && choice_i != 2) {
				cout << "Invalid entry. Try again" << endl;
				test = 0;
				error_counter++;
				if (error_counter == 10) {
					cerr << "Too many invalid entry. Game stopped..." << endl;
					exit(0);
				}
			}
			else {
				test = 1;
				choice = --choice_i;
			}
		
		}while(test == 0);
		cin.ignore();
	}

	bool AbstractHex::isEnd(const Cell_state player, const bool flag, int pos_y, int pos_x) const{
		if (player == player1) {
			if (flag == 0) { //Flag == 0 means it has to find a symbol at first row.
				int i, test;
				for (i = 0; i < size; i++) { //At the beginning it looks for a user1symbol('X') in first row.
					if ((*this)(pos_y, i) == player1) {
						test = isEnd(player, 1, 0, i);
						if (test == 1)
							return 1;
					}
				}
			}
			else { //If it finds a user1_mark at first row, now it looks for southeast, south and southwest directions if the chain goes on.(recursively)
				bool wtest = 0;
				if (pos_y == size-1) 
					return 1;
				if (pos_x > 0 && (*this)(pos_y+1, pos_x-1) == player1) {
					wtest = isEnd(player, 1, pos_y+1, pos_x-1);
					if (wtest == 1) 
						return 1;
				}
				if ((*this)(pos_y+1, pos_x) == player1) {
					wtest = isEnd(player, 1, pos_y+1, pos_x);
					if (wtest == 1) 
						return 1;
				}
				return 0;
			}
			return 0;
		}
		else {
			if (flag == 0) {
				int i = 0, test;
				for (i = 0; i < size; i++) {
					if ((*this)(i, 0) == player2) {
						test = isEnd(player, 1, i, 0);
						if (test == 1)
							return 1;
					}
				}
			}
			else {
				bool wtest = 0;
				if (pos_x == size-1) 
					return 1;
				if (pos_y > 0 && (*this)(pos_y-1, pos_x+1) == player2) {
					wtest = isEnd(player, 1, pos_y-1, pos_x+1);
					if (wtest == 1) 
						return 1;
				}
				if ((*this)(pos_y, pos_x+1) == player2) {
					wtest = isEnd(player, 1, pos_y, pos_x+1);
					if (wtest == 1) 
						return 1;
				}
				return 0;
			}
			return 0;
		}
	}

	bool AbstractHex::operator==(const AbstractHex& rightside) const{
		if (this->size != rightside.get_size())
			return false;
		int y, x, length = this->size;
		for (y = 0; y < length; y++) {
			for (x = 0; x < length; x++) {
				if ((*this)(y, x) != rightside(y, x))
					return false;
			}
		}
		return true;
	}

	int AbstractHex::numberOfMoves() {
		return move_order.size();
	}

	void AbstractHex::convert_to_coordinate(const int num, int &pos_y, int&pos_x) const{ //This function converts cell num to its coordinates.
		pos_y = num/size;
		pos_x = num%size; 
	}

	int AbstractHex::convert_to_cell_id(const int pos_y, const int pos_x) const{ //This function converts cell num to its coordinates.
		return pos_y*size + pos_x;
	}

	int AbstractHex::get_input(int &input1, int &input2){
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
		else if(command.compare("LOAD") == 0)  {//Means user wants to load a game.
			int test;
			value = 4;
			filename = str.substr(pos+1, str.size());
			test = readFromFile(filename);
			if (!test)
				value++;
		}
		else if(command.compare("MENU") == 0)//Means user wants to return to main menu.
			value = 6;
		else if(command.compare("COMPARE") == 0)
			value = 8;
		else if(command.compare("UNDO") == 0)
			value = 10;
		else //Means invalid entry.
			value = 1;
		return value;
	}

	int AbstractHex::check_move_input(const int pos_y, const int pos_x) const{ //Checks that is the move input inside the game board.
		int result = 0;
		if (pos_x >= size || pos_x < 0 || pos_y >= size || pos_y < 0) {
			result = 3;
			cout << "Please enter a coordinate inside the game board." << endl;
		}
		else if ((*this)(pos_y, pos_x) != empty) {
			result = 3;
			cout << "The coordinate you are trying to move is not empty. Please choose an empty coordinate" << endl;
		}
		return result;
	}

	int AbstractHex::playGame() { //Play new game.
		menu();
		resize_board();
		print();
		int result = game_flow();
		return result;
	}

	int AbstractHex::game_flow() { //Default game flow which user1 starts.
		int last_pos_y, last_pos_x, move;
		bool win_test = 0;

		while (!win_test) {
			do {
				move = play(player1);
				if (move != 0 && move != 2 && move != 10)
					return move;
			}while(move == 2);
			turn = 1;
			print();
			win_test = isEnd(player1,0,0,0);
			if (win_test) {
				cout << "User 1 won." << endl;
				return 0;
			}
			if (choice == 1)
				do {
					move = play(player2);
					if (move != 0 && move != 2 && move != 10)
						return move;
				}while(move == 2);
			else
				play();
			turn = 0;
			print();
			win_test = isEnd(player2,0,0,0);
			if (win_test) {
				cout << "User 2 won." << endl;
				return 0;
			}
		}
		return move;
	}

	int AbstractHex::continue_game() { //Continue to an existing game.
		int move;
		if (turn == 0)
			move = game_flow();
		else {
			bool win_test = 0;

			while (!win_test) {
				do {
					move = play(player2);
					if (move != 0 && move != 2 && move != 10)
						return move;
				}while(move == 2); //Calling play until user doesnt save the game.
				turn = 0;
				print();
				win_test = isEnd(player2,0,0,0);
				if (win_test) {
					cout << "User 2 won." << endl;
					return 0;
				}	
				do {
					move = play(player1);
					if (move != 0 && move != 2 && move != 10)
						return move;
				}while(move == 2);
				turn = 1;
				print();
				win_test = isEnd(player1,0,0,0);
				if (win_test) {
					cout << "User 1 won." << endl;
					return 0;
				}

			}
		}
		return move;
	}

	bool AbstractHex::validity_test() {
		int y, x, player1_count, player2_count;
		bool validity;
		for (y = 0; y < size; y++) {
			for (x = 0; x < size; x++) {
				if ((*this)(y, x) == player1)
					player1_count++;
				else if((*this)(y, x) == player2)
					player2_count++;
			}
		}
		if (player1_count - player2_count < 2 && player1_count - player2_count > -2)
			validity = true;
		else
			validity = false;
		return validity;
	}








}





















