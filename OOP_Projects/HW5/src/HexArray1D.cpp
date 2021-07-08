#include "HexArray1D.h"

using namespace std;

namespace HexGame {
	HexArray1D::HexArray1D() {
		hexCells = (Cell*) calloc(size*size, sizeof(Cell));
		init_board();
	}

	HexArray1D::HexArray1D(int board_size) {
		size = board_size;
		hexCells = (Cell*) calloc(size*size, sizeof(Cell));
		init_board();
	}

	HexArray1D::~HexArray1D() {
		free(hexCells);
	}

	HexArray1D::HexArray1D(const HexArray1D& rightside) {
		size = rightside.get_size();
		hexCells = (Cell*) calloc(size*size, sizeof(Cell));
		reset();
		int i, y, x;
		for (i = 0; i < rightside.move_order.size(); i++) {
			int cell_id = rightside.move_order[i];
			move_order.push_back(cell_id);
			convert_to_coordinate(cell_id, y, x);
			hexCells[cell_id] = rightside.hexCells[cell_id];
		}

	}

	HexArray1D& HexArray1D::operator=(const HexArray1D& rightside) {
		if (size == rightside.get_size())
			reset();
		else if (hexCells != nullptr)
			free(hexCells);

		int i, y, x;
		for (i = 0; i < rightside.move_order.size(); i++) {
			int cell_id = rightside.move_order[i];
			move_order.push_back(cell_id);
			convert_to_coordinate(cell_id, y, x);
			hexCells[cell_id] = rightside.hexCells[cell_id];
		}
		return *this;
	}

	void HexArray1D::init_board() {
		int i, y, x;
		for (i = 0; i < size*size; i++) {
			convert_to_coordinate(i, y, x);
			Cell c1;
			c1.set_coordinates(y, x, empty);
			hexCells[i] = c1;
		}
	}

	void HexArray1D::resize_board() {
		free(hexCells);
		hexCells = (Cell*) calloc(size*size, sizeof(Cell));
		init_board();
	}
	
	bool HexArray1D::readFromFile(const string filename) {
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
				cell_id = convert_to_cell_id(pos_y, pos_x);
				if (mark == player1) 
					hexCells[cell_id].set_state(player1);
				else
					hexCells[cell_id].set_state(player2);
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

	void HexArray1D::reset() {
		int i;
		for (i = 0; i < move_order.size(); i++) {
			hexCells[move_order[i]].set_state(empty);
		}
	}

	void HexArray1D::play() {
		int y, x;
		int cell_id;
		if (move_order.size() > 2) {
			bool valid;
			convert_to_coordinate(move_order[move_order.size()-2], y, x);
			if (x == size-1)
				valid = 0;
			else if (y > 0 && hexCells[convert_to_cell_id(y-1, x+1)].get_state() == empty) {
				y -= 1;
				x += 1;
				valid = 1;
			}
			else if (hexCells[convert_to_cell_id(y, x+1)].get_state() == empty) {
				x += 1;
				valid = 1;
			}
			if (valid == 0) { //If no available moves in next column, computer plays random move.
				bool valid1 = 0;
				while (valid1 == 0) {
					y = rand() % size;
					x = rand() % size;
					if (hexCells[convert_to_cell_id(y, x)].get_state() == empty) {
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
				cell_id = convert_to_cell_id(y, x);
				if (hexCells[cell_id].get_state() == empty)
					valid = 1;
			}
		}
		cell_id = convert_to_cell_id(y, x);
		hexCells[cell_id].set_state(player2);
		move_order.push_back(cell_id);
		char letter = 'A';
		letter += x;
		cout << "Computer played " << letter << " " << y+1 << endl;
	}

	int HexArray1D::play(Cell_state user_mark) {
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
					int cell_id = convert_to_cell_id(input1, input2);
					move_order.push_back(cell_id);
					hexCells[cell_id].set_state(user_mark);
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

	Cell_state HexArray1D::operator()(const int coor_y, const int coor_x) const{
		if (coor_y < 0 || coor_x < 0 || coor_y > size-1 || coor_x > size-1)
			throw BoardException();
		int cell_id = convert_to_cell_id(coor_y, coor_x);
		return hexCells[cell_id].get_state();
	}

	void HexArray1D::undo() {
		if (move_order.size() < 2)
			cout << "There is not enough moves to undo." << endl;
		else {
			hexCells[move_order.back()].set_state(empty);
			move_order.pop_back();
			hexCells[move_order.back()].set_state(empty);
			move_order.pop_back();
		}
	}











	
}
