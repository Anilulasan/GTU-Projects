#include "HexVector.h"

using namespace std;

namespace HexGame {
	HexVector::HexVector() {
		int y, x;
		for (y = 0; y < size; y++) {
			vector <Cell> cells;
			for (x = 0; x < size; x++) {
				Cell c1(y, x);
				cells.push_back(c1);
			}
			hexCells.push_back(cells);
		}
	}

	HexVector::HexVector(int board_size) {
		size = board_size;
		int y, x;
		for (y = 0; y < size; y++) {
			vector <Cell> cells;
			for (x = 0; x < size; x++) {
				Cell c1(y, x);
				cells.push_back(c1);
			}
			hexCells.push_back(cells);
		}
	}

	void HexVector::resize_board() {
		int i, y, x;
		hexCells.resize(size);
		for (i = 0; i < size; i++) 
			hexCells[i].resize(size);
	}

	bool HexVector::readFromFile(const string filename) {
		bool success = 0;
		int old_size;
		fstream file;
		file.open(filename.c_str());
		if (file) {
			old_size = size;
			file >> size;
			file >> choice;
			file >> turn;

			if (old_size == size)
				reset();
			else
				resize_board();


			move_order.clear();
			int pos_y, pos_x, mark, cell_id;
			while (!file.eof()) {
				file >> pos_y;
				file >> pos_x;
				file >> mark;
				if (mark == player1) 
					hexCells[pos_y][pos_x].set_state(player1);
				else
					hexCells[pos_y][pos_x].set_state(player2);
				cell_id = convert_to_cell_id(pos_y, pos_x);
				if (!file.eof())
					move_order.push_back(cell_id);		
			}
			file.close();
			cout << "Your game succesfully loaded" << endl;
			print();
			success = true;
		}
		else
			cout << "Bad file name" << endl;
		return success;
	}

	void HexVector::reset() {
		int y, x;
		for (auto p:move_order) {
			convert_to_coordinate(p, y, x);
			hexCells[y][x].set_state(empty);
		}
	}

	void HexVector::play() {
		int y, x;
		if (move_order.size() > 2) {
			bool valid;
			convert_to_coordinate(move_order[move_order.size()-2], y, x);
			if (x == size-1)
				valid = 0;
			else if (y > 0 && hexCells[y-1][x+1].get_state() == empty) {
				y -= 1;
				x += 1;
				valid = 1;
			}
			else if (hexCells[y][x+1].get_state() == empty) {
				x += 1;
				valid = 1;
			}
			if (valid == 0) { //If no available moves in next column, computer plays random move.
				bool valid1 = 0;
				while (valid1 == 0) {
					y = rand() % size;
					x = rand() % size;
					if (hexCells[y][x].get_state() == empty) {
						valid1 = 1;
						valid = 1;
					}

				}
			}
		}
		else {
			bool valid = 0;
			x = 0;
			while (valid == 0) {
				y = rand() % size;
				if (hexCells[y][x].get_state() == empty)
					valid = 1;
			}
		}
		hexCells[y][x].set_state(player2);
		move_order.push_back(convert_to_cell_id(y, x));
		char letter = 'A';
		letter += x;
		cout << "Computer played " << letter << " " << y+1 << endl;
	}

	int HexVector::play(Cell_state user_mark) {
		int user_choice, input1, input2, test, error_counter = 0;
		do {
			cout << "Make a move: ";
			user_choice = get_input(input1, input2);
			test = user_choice;
			if (user_choice == 0) { //Means its a coordinate.
				test = check_move_input(input1, input2);
				if (!test) {
					hexCells[input1][input2].set_state(user_mark);
					move_order.push_back(convert_to_cell_id(input1, input2));
				}
				else
					error_counter++;
			}
			else if(user_choice == 6)
				return test;
			else if(user_choice == 10) {
				undo();
				print();
			}
			else if(user_choice == -1){
				cout << "Invalid entry. Please try again." << endl;
				error_counter++;
			}
			if (error_counter == 10) {
				cerr << "Too many invalid entry. Game stopped" << endl;
				exit(0);
			}
		}while(test%2 == 1 || test == 10); //If save fails, it returns 3. If load fails, it returns 5. So if test is an odd number, thats invalid input.
		return test;
	}

	Cell_state HexVector::operator()(const int coor_y, const int coor_x) const{
		if (coor_y < 0 || coor_x < 0 || coor_y > size-1 || coor_x > size-1)
			throw BoardException();
		return hexCells[coor_y][coor_x].get_state();
	}

	void HexVector::undo() {
		if (move_order.size() < 2)
				cout << "There is not enough moves to undo." << endl;
			else {
				int y, x;
				convert_to_coordinate(move_order.back(), y, x);
				hexCells[y][x].set_state(empty);
				move_order.pop_back();
				convert_to_coordinate(move_order.back(), y, x);
				hexCells[y][x].set_state(empty);
				move_order.pop_back();
		}
	}


}