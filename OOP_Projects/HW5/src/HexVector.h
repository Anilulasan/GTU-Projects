#ifndef HexVector_h
#define HexVector_h

#include "AbstractHex.h"

using namespace std;

namespace HexGame {
	class HexVector : public AbstractHex {
	public:
		HexVector();
		HexVector(int board_size);
		virtual void resize_board() override;
		virtual bool readFromFile(const string filename) override;
		virtual void reset() override;
		virtual void play() override;
		virtual int play(Cell_state user_mark) override;
		virtual Cell_state operator()(const int coor_y, const int coor_x) const override;
		virtual void undo() override;
	private:
		vector< vector <Cell> > hexCells;
	};

}

#endif