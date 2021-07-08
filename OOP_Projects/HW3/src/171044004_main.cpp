#include "source.h"

using namespace std;

int Hex::Cell::filled_cell_count = 0;

int main() {
	srand(time(NULL));

	int option, result;
	vector <Hex> games;
	Hex game;

	cout << "Welcome to Hex game!" << endl;
	do {
		cout << "1. Start new game" << endl
		<< "2. Continue on existing game" << endl
		<< "3. Terminate program" << endl
		<< "Marked Cell count: " << game.get_filled() << endl;
		cout << "Choice: ";
		cin >> option;
		if (option == 3)
			exit(0);
		if (option == 1) {
			int num;
			Hex game;
			games.push_back(game);
			num = games.size()-1;
			result = games[num].playGame();
			if (result == 4) //Means user entered LOAD
				do {
					games[num].display_board();
					result = games[num].continue_game();
				}while(result == 4);
			if (result == 0) {//Means game is over. Somebody won.
				games[num].decrement_filled(games[num].count_marked_cells());
				games.erase(games.begin()+num);
			}
			if (result == 8) { //Means user entered COMPARE.
				int limit = games.size();
				int i, selection;
				for (i = 0; i < limit; i++) {
					cout << i+1 << ".Game " << i+1
					<< "(size = " << games[i].get_size() 
					<< " choice = " << games[i].get_choice() << ")"<< endl;
				}
				cin >> selection;
				if (selection == num+1)
					cout << "You can not compare a game with itself. Returning to main menu." << endl;
				else if(selection < 1 || selection > limit)
					cout << "Invalid entry. Returning to main menu." << endl;
				else {
					bool comp;
					comp = games[num].Compare_games(games[selection-1]);
					if (comp)
						cout << "First game has more marked cells" << endl;
					else
						cout << "Second game has more marked cells or equal." << endl;
				}
			}
		}
		else if (option == 2) {
			int limit = games.size();
			if (limit < 1) {
				cout << "There is no existing game. Returning to main menu..." << endl;
				result = -1;
			}
			else {
				int i, selection;
				for (i = 0; i < limit; i++) {
					cout << i+1 << ".Game " << i+1
					<< "(size = " << games[i].get_size() 
					<< " choice = " << games[i].get_choice() << ")"<< endl;
				}
				cin >> selection;
				if (selection < 1 || selection > limit) {
					cout << "Invalid choice. Returning to main menu..." << endl;
				}
				else { //Valid input. Chosen game continues.
					selection--;
					games[selection].display_board();
					result = games[selection].continue_game();
					if (result == 4) {
						do {
							games[selection].display_board();
							result = games[selection].continue_game();
						}while(result == 4);
					}
					if (result == 0) {
						games[selection].decrement_filled(games[selection].count_marked_cells());
						games.erase(games.begin()+selection);
					}
					if (result == 8) { //Means user entered COMPARE.
						int limit = games.size();
						int i, num;
						for (i = 0; i < limit; i++) {
							cout << i+1 << ".Game " << i+1
							<< "(size = " << games[i].get_size() 
							<< " choice = " << games[i].get_choice() << ")"<< endl;
						}
						cin >> num;
						if (num == selection+1)
							cout << "You can not compare a game with itself. Returning to main menu." << endl;
						else if(num < 1 || num > limit)
							cout << "Invalid entry. Returning to main menu." << endl;
						else {
							bool comp;
							comp = games[selection].Compare_games(games[num-1]);
							if (comp)
								cout << "First game has more marked cells" << endl;
							else
								cout << "Second game has more marked cells or equal." << endl;
						}
			}
				}
			}
		}
		else
			cout << "Invalid entry. Try again." << endl;
	}while (option != 3);

}



















