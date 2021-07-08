#ifndef source_h
#define source_h

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Cell_state{player1 = 'X', player2 = 'O', empty = '.'};

class Hex{
public:
	Hex(); //Default constructor
	Hex(int length) {size = length, turn = 0;}; //Paramaterized constructor
	Hex(int length, bool option) {size = length, choice = option, turn = 0;}; //Parameterized constructor
	//static int get_marked_count() {return filled_cell_count;};
	const int get_size() {return size;};
	const int get_choice() {return choice;};
	void main_menu();
	const void menu();
	const void init_board();
	const void display_board();
	const void fix_print(const Cell_state form);
	const int check_move_input(const int pos_y, const int pos_x);
	int get_input(int &input1, int &input2);
	const void play(int &last_pos_y, int &last_pos_x, const bool first);
	int play(const Cell_state user_mark);
	bool win_check_p1(const bool flag, int pos_y, int pos_x);
	bool win_check_p2(const bool flag, int pos_y, int pos_x);
	bool save(const string filename);
	bool load(const string filename);
	bool write_to_file(const string filename);
	bool read_from_file(const string filename);
	int game_flow();
	int continue_game();
	int playGame();
	int count_marked_cells();
	bool Compare_games(Hex other);
	static void increment_filled(int number);
	static void decrement_filled(int number);
	static int get_filled();
private:
	class Cell{
		friend class Hex;
	public:
		Cell() {coor_y = 0; coor_x = 0; state = empty;}; //Default constructor
		Cell(int coor1, int coor2) {coor_y = coor1; coor_x = coor2; state = empty;}; //Parameterized constructor
		const void set_coordinates(int coor1, int coor2, Cell_state state) {coor_y = coor1; coor_x = coor2;};
		const int get_coor_y() {return coor_y;};
		const int get_coor_x() {return coor_x;};
		const Cell_state get_state() {return state;};
		const void set_state(Cell_state form) {state = form;};
	private:
		int coor_y;
		int coor_x;
		Cell_state state;
		static int filled_cell_count;
	};
	vector<vector<Cell> > hexCells;
	int size;
	bool choice;
	bool turn;
};


#endif