#ifndef HexAdapter_h
#define HexAdapter_h

#include "AbstractHex.h"

using namespace std;
namespace HexGame {
	template <template<class ...> class T>
	class HexAdapter : public AbstractHex{
	public:
		HexAdapter();
		HexAdapter(int board_size);
		virtual void resize_board() override;
		virtual bool readFromFile(const string filename) override;
		virtual void reset() override;
		virtual void play() override;
		virtual int play(Cell_state user_mark) override;
		virtual Cell_state operator()(const int coor_y, const int coor_x) const override;
		virtual void undo() override;
	private:
		T< T <Cell> > hexCells;
	};

}


#endif