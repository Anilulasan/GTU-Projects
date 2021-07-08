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
	class Cell{
	public:
		friend class Hex;
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

	//Big three provided
	~Hex(); //Destructor
	Hex(const Hex &copied); //Copy Constructor
	Hex &operator =(const Hex &rightside);

	Hex(); //Default constructor
	explicit Hex(int length) {size = length, turn = 0;}; //Paramaterized constructor
	Hex(int length, bool option) {size = length, choice = option, turn = 0;}; //Parameterized constructor
	const int get_size() const{return size;};
	const int get_choice() const{return choice;};
	const int get_turn() const{return turn;};
	void set_turn(bool set) {turn = set;}; //Implemented it for undo feature. In UservsUser i have to change turn if one of the users wants to undo his last move.
	const void menu();
	const void resize_board(int oldsize = 10);
	void display_board() const;
	void fix_print(const Cell_state form) const;
	const int check_move_input(const int pos_y, const int pos_x) const;
	int get_input(int &input1, int &input2);
	const void play(int &last_pos_y, int &last_pos_x, const bool first);
	int play(const Cell_state user_mark);
	bool win_check_p1(const bool flag, int pos_y, int pos_x) const;
	bool win_check_p2(const bool flag, int pos_y, int pos_x) const;
	bool save(const string filename);
	bool load(const string filename);
	bool write_to_file(const string filename);
	void read_from_file(const string filename);
	int game_flow();
	int continue_game();
	int playGame();
	int count_marked_cells() const;
	//bool Compare_games(Hex other) const;
	static void increment_filled(int number);
	static void decrement_filled(int number);
	static int get_filled();
	///////Added in HW4
	void convert_to_coordinate(const int num, int &pos_y, int&pos_x) const;
	Hex &operator --();
	Hex operator --(int);
	bool operator ==(const Hex &other);
	friend ostream& operator <<(ostream &outputStream, const Hex &object);
	friend istream& operator >>(istream &inputStream, Hex &object);
	const int score_p1(const bool flag, int pos_y, int pos_x, int start_index) const;
	const int score_p2(const bool flag, int pos_y, int pos_x, int start_index) const;
	//Big three provided in top of public section.

private:
	int *move_order; //For undo feature, i implemented an array to hold move order. It holds the cell number that got moved as integer.
	Cell **hexCells;
	int size;
	bool choice;
	bool turn;
};


#endif