#ifndef Cell_h
#define Cell_h

#include <iostream>

namespace HexGame {
	enum Cell_state{player1 = 'X', player2 = 'O', empty = '.'};
	
	class Cell{
		public:
			Cell() {coor_y = 0; coor_x = 0; state = empty;}; //Default constructor
			Cell(int coor1, int coor2) {coor_y = coor1; coor_x = coor2; state = empty;}; //Parameterized constructor
			const void set_coordinates(int coor1, int coor2, Cell_state form) {coor_y = coor1; coor_x = coor2; state = form;};
			const int get_coor_y() const{return coor_y;};
			const int get_coor_x() const{return coor_x;};
			Cell_state get_state() const{return state;};
			const void set_state(Cell_state form) {state = form;};
		private:
			int coor_y;
			int coor_x;
			Cell_state state;
		};
}

#endif