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
			Hex game;
			games.push_back(game);
		}
		if (option == 1 || option == 2) {
			int num;
			if (option == 1) {
				num = games.size()-1;
				result = games[num].playGame();
			}
			else { //Means user wants to pick a game and continue(option == 2).
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
					if (selection < 1 || selection > limit)
						cout << "Invalid choice. Returning to main menu..." << endl;
					else { //Means user entered valid input.
						num = selection-1;
						cout << games[num]; //Usage of overloaded <<.
						cin.ignore();
						result = games[num].continue_game();

					}
				}
			}
			while (result == 10 || result == 4) { //Game must continue if user enters UNDO or LOAD.
				if (result == 10) {
					if (games[num].count_marked_cells() < 2) { //If there is not 2 moves played, players can't undo. Because in UservsCom, computer automatically plays after user so there is gonna be 2 moves. In UservsUser, User2 can't undo User1's move so the number is 2 here.
						cout << "You can not undo, there is no move yet." << endl;
					}
					else if (games[num].get_choice() == 0) { //If game is UservsComputer, it undos last 2 move.
						--games[num];
						games[num]--;
						games[num].decrement_filled(2);
					}
					else { //If game is UservsUser, if user wants to undo his last move, it means it has to undo his opponents last move too. So he need permission for that.
						char answer;
						if (games[num].get_turn() == 0) 
							cout << "User 2, User 1 ";
						else
							cout << "User 1, User 2 ";
						cout << "wants to undo his last move, it means it is going to undo your last move too. Do you accept that?(Y/N): ";	
						cin >> answer;
						if (answer == 'Y') {
							--games[num];
							games[num]--;
							games[num].decrement_filled(2);
						}
						else
							cout << "Your opponent doesn't allow you to do that." << endl;
					}
				}
				else {
					cin >> games[num];
					cin.ignore();
				}
				cout << games[num];
				result = games[num].continue_game();
			}
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
					if (games[num] == games[selection-1])
						cout << "First game has same amount of marked cells with second game." << endl;
					else
						cout << "Marked cell numbers of two games are different." << endl;
				}
			}
		}
		else
			cout << "Invalid entry. Try again." << endl;
	}while (option != 3);

}



















