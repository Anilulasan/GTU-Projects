#include "source.h"
/////// Big three
Hex::~Hex() {
	int i;
	for (i = 0; i < size; i++)
		delete [] hexCells[i];
	delete hexCells;
	delete [] move_order;
}

Hex::Hex(const Hex &copied) {
	int move_count;
	size = copied.size;
	choice = copied.choice;
	turn = copied.turn;
	move_count = copied.count_marked_cells();
	int i;
	move_order = new int [size*size];
	for (i = 0; i < move_count; i++) {
		move_order[i] = copied.move_order[i];
	}
	hexCells = new Cell *[size];
	for (i = 0; i < size; i++)
		hexCells[i] = new Cell[size];

	for (i = 0; i < move_count; i++) {
		int y, x;
		convert_to_coordinate(move_order[i], y, x);
		if (i % 2 == 0)
			hexCells[y][x].set_state(player1);
		else
			hexCells[y][x].set_state(player2);
	}
}

Hex &Hex::operator =(const Hex &rightside) {
	int move_count;
	size = rightside.size;
	choice = rightside.choice;
	turn = rightside.turn;
	move_count = this->count_marked_cells();
	int i;
	if (move_order != nullptr) 
		delete [] move_order;
	if (hexCells != nullptr) {
		int i;
		for (i = 0; i < size; i++)
			delete [] hexCells[i];
		delete hexCells;
	}
	move_order = new int [size*size];
	for (i = 0; i < move_count; i++) {
		move_order[i] = rightside.move_order[i];
	}
	hexCells = new Cell *[size];
	for (i = 0; i < size; i++)
		hexCells[i] = new Cell[size];

	for (i = 0; i < move_count; i++) {
		int y, x;
		convert_to_coordinate(move_order[i], y, x);
		if (i % 2 == 0)
			hexCells[y][x].set_state(player1);
		else
			hexCells[y][x].set_state(player2);
	}
	return *this;
}	
////// Big Three
Hex::Hex() {
	size = 10;
	choice = 0;
	turn = 0;
	int i;
	hexCells = new Cell *[size];
	for (i = 0; i < size; i++)
		hexCells[i] = new Cell[size];

	move_order = new int [size*size];
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

int Hex::count_marked_cells() const{
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
		int score = 0;

		while (score != size) {
			do {
				move = play(player2);
				if (move != 0 && move != 2)
					return move;
			}while(move == 2); //Calling play until user doesnt save the game.
			increment_filled(1);
			turn = 0;
			display_board();
			score = score_p2(0,0,0,0);
			cout << "Player2 Score = " << score << endl;
			if (score == size) {
				cout << "Player2 won." << endl;
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
			score = score_p1(0,0,0,0);
			cout << "Player1 Score = " << score << endl;
			if (score == size) {
				cout << "Player1 won." << endl;
				return 0;
			}
		}
	}
	return move;
}

int Hex::playGame() { //Play new game.
	menu();
	resize_board();
	display_board();
	int result = game_flow();
	return result;
}

int Hex::game_flow() { //Default game flow which user1 starts.
	int last_pos_y, last_pos_x, move;
	bool first = 1;
	decltype(move) score = 0;

	while (score != size) {
		do {
			move = play(player1);
			if (move != 0 && move != 2)
				return move;
		}while(move == 2);
		increment_filled(1);
		turn = 1;
		display_board();
		score = score_p1(0,0,0,0);
		cout << "Player1 Score = " << score << endl;
		if (score == size) {
			cout << "Player1 won." << endl;
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
		score = score_p2(0,0,0,0);
		cout << "Player2 Score = " << score << endl;
		if (score == size) {
			cout << "Player2 won." << endl;
			return 0;
		}

		first = 0;
	}
	return move;
}

const void Hex::resize_board(int old_size) {
	int i, y, x;
	//First deallocate
	for (i = 0; i < old_size; i++)
		delete [] hexCells[i];
	delete hexCells;
	delete [] move_order;

	//Then allocate with new size
	hexCells = new Cell *[size];
	for (i = 0; i < size; i++) {
		hexCells[i] = new Cell[size];
	}
	move_order = new int [size*size];
}

void Hex::display_board() const{
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
			size = size_i
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

void Hex::fix_print(const Cell_state form) const{ //Cout prints enum types as integers, so this function fixes that.
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
	move_order[this->count_marked_cells()] = last_pos_y*size + last_pos_x;
	hexCells[last_pos_y][last_pos_x].set_state(player2);
	
}



int Hex::play(const Cell_state user_mark) { //Gets input from user, checks validity, then marks the symbol on the coordinate.
	int user_choice, input1, input2, test, error_counter = 0;
	do {
		if (user_mark == player1)
			cout << "User 1, ";
		else
			cout << "User 2, ";
		cout << "Make a move: ";
		user_choice = get_input(input1, input2);
		test = user_choice;
		if (user_choice == 0) { //Means its a coordinate.
			test = check_move_input(input1, input2);
			if (!test) { //Test returns 0 if move input is valid.
				move_order[this->count_marked_cells()] = input1*size + input2;
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

const int Hex::check_move_input(const int pos_y, const int pos_x) const{ //Checks that is the move input inside the game board.
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
	else if(command.compare("LOAD") == 0) //Means user wants to load a game.
		value = 4;
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

bool Hex::write_to_file(const string filename) { 
	fstream file;
	int success;
	file.open(filename.c_str(), fstream::out);
	if (file) {
		file << size << " ";
		file << choice << " ";
		file << turn << " ";

		int i, limit = this->count_marked_cells();
		for (i = 0; i < limit; i++) {
			int y, x;
			convert_to_coordinate(move_order[i], y, x);
			if (hexCells[y][x].get_state() == player1) {
				file << y << " " << x << " " << player1 << " ";
			}
			if (hexCells[y][x].get_state() == player2) {
				file << y << " " << x << " " << player2 << " ";
			}
		}
		file.close();
		success = 1;
	}
	else
		success = 0;
	return success;

}

void Hex::read_from_file(const string filename) { //Loads the game. Deletes all marked cells from our static variable, then adds the loaded games marks.
	int old_size;
	fstream file;
	file.open(filename.c_str());
	if (file) {
		decrement_filled(count_marked_cells());
		old_size = size;
		file >> size;
		file >> choice;
		file >> turn;
		resize_board(old_size);

		int pos_y, pos_x, mark, index = 0;
		while (!file.eof()) {
			file >> pos_y;
			file >> pos_x;
			file >> mark;
			if (mark == player1)
				hexCells[pos_y][pos_x].set_state(player1);
			else
				hexCells[pos_y][pos_x].set_state(player2);
			move_order[index] = pos_y*size + pos_x;
			index++;		
		}
		increment_filled(index-1);
		file.close();
		cout << "Your game succesfully loaded" << endl;
	}
	else
		cout << "Bad file name" << endl;
}

bool Hex::save(const string filename) {
	int test;
	test = write_to_file(filename);
	if (test)
		cout << "Your game succesfully saved" << endl;
	else
		cout << "Bad file name" << endl;
	return test;
}

/*bool Hex::load(const string filename) {
	int test;
	test = read_from_file(filename);
	if (test)
		cout << "Your game succesfully loaded" << endl;
	else
		cout << "Bad file name" << endl;
	return test;
}*/

void Hex::convert_to_coordinate(const int num, int &pos_y, int&pos_x) const{ //This function converts cell num to its coordinates.
	pos_y = num/size;
	pos_x = num%size; 
}


Hex &Hex::operator --() { //Prefix
	int num, coor_y, coor_x;
	num = move_order[this->count_marked_cells()-1];
	this->convert_to_coordinate(num, coor_y, coor_x);
	hexCells[coor_y][coor_x].set_state(empty);
	return *this;
}

Hex Hex::operator --(int) { //Postfix
	Hex temp(*this);
	operator--();
	return temp;
}

bool Hex::operator ==(const Hex &other) {
	int num1, num2;
	bool result;
	num1 = count_marked_cells();
	num2 = other.count_marked_cells();
	if (num1 == num2)
		result = 1;
	else
		result = 0;
	return result;
}

ostream& operator <<(ostream &outputStream, const Hex &object) {
	int y, x, length;
	char letter = 'a';
	length = object.size;
	outputStream << " ";
	for (x = 0; x < length; x++) {
		outputStream << letter;
		letter++;
	}
	outputStream << endl;
	
	for (y = 0; y < length; y++) {
		outputStream << y+1;
		for (x = -1; x < y; x++)
			outputStream << " ";
		for (x = 0; x < length; x++) {
			if (object.hexCells[y][x].get_state() == empty)
				outputStream << '.';
			else if(object.hexCells[y][x].get_state() == player1)
				outputStream << 'X';
			else
				outputStream << 'O';
				}
		outputStream << endl;
	}
	return outputStream;
}

istream& operator >>(istream &inputStream, Hex &object) {
	string filename;
	cout << "Please enter the file name that you want to load: ";
	inputStream >> filename;
	object.read_from_file(filename);
	return inputStream;
}

const int Hex::score_p1(const bool flag, int pos_y, int pos_x, int start_index) const{ //When it finds a player2 symbol at the board, when looking for more connected symbols, my algorithm holds start index(pos_x) of head of the chain to calculate number of connected symbols.
	if (flag == 0) { //Flag == 0 means it has to find a symbol at first row.
		int y, x, score, max_score = 0;
		for (y = 0; y < size; y++) {
			for (x = 0; x < size; x++) { 
				if (hexCells[y][x].get_state() == player1) {
					score = score_p1(1, y, x, y);
					if (score == size) //It means player won, so immediately stops searching.
						return score;
					if (score > max_score)
						max_score = score;
				}
			}
		}
		return max_score;
	}
	else { //If it finds a user1_mark at first row, now it looks for south and southwest directions if the chain goes on.(recursively)
		if (pos_y == size-1)
			return pos_y - start_index + 1;
		int score = 0, check = 0;
		if (pos_x > 0 && hexCells[pos_y+1][pos_x-1].get_state() == player1) {
			score = score_p1(1, pos_y+1, pos_x-1, start_index);
			if (score == size) 
				return score;
			check++;
		}
		if (hexCells[pos_y+1][pos_x].get_state() == player1) {
			score = score_p1(1, pos_y+1, pos_x, start_index);
			if (score == size) 
				return score;
			check++;
		}
		if (check == 0) //It means this is the last element of chain.
			return pos_y - start_index + 1; //Substracting first element's coor_y from last element's coor_y to find size of the chain. 
		else //It means this is not the last element of chain, recursive function coming back to start, so it returns last element's return to not lose connected cells count.
			return score;
	}
	return 0;
}


const int Hex::score_p2(const bool flag, int pos_y, int pos_x, int start_index) const{ //Same algorithm with score_p1() function.
	if (flag == 0) { 
		int y, x, score, max_score = 0;
		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) { 
				if (hexCells[y][x].get_state() == player2) {
					score = score_p2(1, y, x, x);
					if (score == size) 
						return score;
					if (score > max_score)
						max_score = score;
				}
			}
		}
		return max_score;
	}
	else {
		if (pos_x == size-1) 
			return pos_x - start_index + 1;
		int score = 0, check = 0;
		if (pos_y > 0 && hexCells[pos_y-1][pos_x+1].get_state() == player2) {
			score = score_p2(1, pos_y-1, pos_x+1, start_index);
			if (score == size) 
				return score;
			check++;
		}
		if (hexCells[pos_y][pos_x+1].get_state() == player2) {
			score = score_p2(1, pos_y, pos_x+1, start_index);
			if (score == size) 
				return score;
			check++;
		}
		if (check == 0)
			return pos_x - start_index + 1;
		else
			return score;
	}
	return 0;
}



