#ifndef HexArray1D_h
#define HexArray1D_h

#include <cstdlib>
#include "AbstractHex.h"

using namespace std;

namespace HexGame {
	
	class HexArray1D : public AbstractHex{
	public:
		HexArray1D();
		HexArray1D(int board_size);
		//Big Three
		~HexArray1D();
		HexArray1D(const HexArray1D& rightside);
		HexArray1D& operator=(const HexArray1D& rightside);

		void init_board();
		virtual void resize_board() override;
		virtual bool readFromFile(const string filename) override;
		virtual void reset() override;
		virtual void play() override;
		virtual int play(Cell_state user_mark) override;
		virtual Cell_state operator()(const int coor_y, const int coor_x) const override;
		virtual void undo() override;
	private:
		Cell *hexCells;
	};

}
#endif