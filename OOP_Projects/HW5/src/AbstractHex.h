#ifndef AbstractHex_h
#define AbstractHex_h
#include <iostream>
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Exceptions.h"

using namespace std;

namespace HexGame {
	class AbstractHex{
	public:
		AbstractHex();
		~AbstractHex() {};
		void print() const;
		void fix_print(const Cell_state form) const;
		virtual bool readFromFile(const string filename) = 0;
		bool writeToFile(const string filename) const;
		virtual void reset() = 0;
		void setSize(int board_size);
		virtual void play() = 0;
		virtual int play(Cell_state player) = 0;
		bool isEnd(const Cell_state symbol, const bool flag, int pos_y, int pos_x) const;
		virtual Cell_state operator()(const int coor_y, const int coor_x) const=0;
		bool operator==(const AbstractHex &board2) const;
		Cell lastMove();
		int numberOfMoves();
		void menu();
		virtual void resize_board()=0;
		void convert_to_coordinate(const int num, int &pos_y, int &pos_x) const;
		int convert_to_cell_id(const int pos_y, const int pos_x) const;
		int get_size() const;
		bool get_choice() const{return choice;};
		int get_input(int &input1, int &input2);
		int check_move_input(const int pos_y, const int pos_x) const;
		int playGame();
		int game_flow();
		int continue_game();
		bool save(const string filename) const;
		bool validity_test();
		virtual void undo() = 0;
	protected:
		int size;
		bool choice;
		bool turn;
		vector<int> move_order;
	};

}

#endif



