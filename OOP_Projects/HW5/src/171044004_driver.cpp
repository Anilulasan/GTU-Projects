#include "AbstractHex.h"
#include "HexArray1D.h"
#include "HexVector.h"
#include "HexAdapter.h"
#include "Exceptions.h"
#include <deque>

using namespace std;
using namespace HexGame;

template <int C>
bool global_test(AbstractHex* (&boards)[C]) { //Finds number of X and O in the board. If one of them is unacceptably higher than the other, returns false. One invalid board is enough to return false.
	int i, size;
	size = sizeof(boards)/sizeof(AbstractHex);
	for (i = 0; i < size; i++) {
		if (boards[i]->validity_test() == false)
			return false;
	}
	return true;
}

int main() {
	AbstractHex *game1 = new HexVector;
	AbstractHex *game2 = new HexArray1D;
	AbstractHex *game3 = new HexAdapter<vector>;
	AbstractHex *game4 = new HexAdapter<deque>;
	AbstractHex* boards[] = {game1, game2, game3, game4};
	int i = 0;
	for (auto p:boards) {
		if (i == 0)
			cout << "---------------HexVector TEST----------------" << endl << endl;
		else if(i == 1)
			cout << "-------------HexArray1D TEST----------------" << endl << endl;
		else if(i == 2)
			cout << "-------------HexAdapter<vector> TEST----------------" << endl << endl;
		else if(i == 3)
			cout << "--------------HexAdapter<deque> TEST----------------" << endl << endl;

		cout << "----TEST GLOBAL FUNCTİON----" << endl;
		cout << global_test(boards) << endl;

		cout << "----TEST readFromFile()------" << endl;
		p->readFromFile("test.txt");

		cout << "----TEST setSize()------" << endl;
		p->print();
		p->setSize(15);
		p->print();

		cout << "----TEST play()------" << endl;
		p->play();
		p->print();

		cout << "----TEST isEnd()------" << endl;
		cout << p->isEnd(player1, 0, 0, 0) << endl;

		cout << "----TEST operator== ------" << endl;
		bool test = p==(p+1);
		cout << test << endl;

		cout << "----TEST operator()------" << endl;
		p->fix_print((*p)(0, 0));
		cout << endl;
		
		cout << "----TEST lastMove()------" << endl;
		try {
			p->lastMove();
		}
		catch(moveException &ex) {
			cout << "Exception occured" << ex.what() << endl;
		}
		try {
			p->lastMove();
		}
		catch(moveException &ex) {
			cout << "Exception occured" << ex.what() << endl;
		}

		cout << "----TEST numberOfMoves()------" << endl;
		p->print();
		cout << "NofMoves: " << p->numberOfMoves() << endl;
		p->play();
		p->print();
		cout << "NofMoves: " << p->numberOfMoves() << endl;

		cout << "----TEST undo()------" << endl;
		p->print();
		p->undo();
		p->print();

		i++;
	}
}