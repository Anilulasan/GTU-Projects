#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include <iostream>
#include <ctime>
#include <deque>

using namespace std;
using namespace HexGame;

int main() {
	srand(time(NULL));

	int option, result;
	vector <AbstractHex*> games;

	cout << "Welcome to Hex game!" << endl;
	do {
		cout << "1. Start new game" << endl
		<< "2. Continue on existing game" << endl
		<< "3. Terminate program" << endl
		<< "Choice: ";
		cin >> option;
		if (option == 3)
			exit(0);
		if (option == 1) {
			int choice, result;
			cout << "How do you like to represent the board? " << endl
			<< "1. HexVector" << endl
			<< "2. HexArray1D" << endl
			<< "3. HexAdapter" << endl
			<< "choice: ";
			cin >> choice;
			AbstractHex *game;
			if (choice == 1) 
				game = new HexVector;

			if (choice == 2) 
				game = new HexArray1D;

			else if(choice == 3) {
				cout << "Welcome to Hex Game. How do you like to represent the board? " << endl
				<< "1. Vector" << endl
				<< "2. Deque" << endl
				<< "choice: ";
				cin >> choice;
				if (choice == 1) 
					game = new HexAdapter<vector>;
				else if (choice == 2) 
					game = new HexAdapter<deque>;
			}
			games.push_back(game);
		}
		if (option == 1 || option == 2) {
			int num;
			if (option == 1) {
				num = games.size()-1;
				result = games[num]->playGame();
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
						<< "(size = " << games[i]->get_size() 
						<< " choice = " << games[i]->get_choice() << ")"<< endl;
					}
					cin >> selection;
					if (selection < 1 || selection > limit)
						cout << "Invalid choice. Returning to main menu..." << endl;
					else { //Means user entered valid input.
						num = selection-1;
						cout << games[num]; //Usage of overloaded <<.
						cin.ignore();
						result = games[num]->continue_game();

					}
				}
			}
			while (result == 4) { //Game must continue if user enters LOAD.
				result = games[num]->continue_game();
			}
			if (result == 0) //Means game is over. Somebody won.
				games.erase(games.begin()+num);

			if (result == 8) { //Means user entered COMPARE.
				int limit = games.size();
				int i, selection;
				for (i = 0; i < limit; i++) {
					cout << i+1 << ".Game " << i+1
					<< "(size = " << games[i]->get_size() 
					<< " choice = " << games[i]->get_choice() << ")"<< endl;
				}
				cin >> selection;
				if (selection == num+1)
					cout << "You can not compare a game with itself. Returning to main menu." << endl;
				else if(selection < 1 || selection > limit)
					cout << "Invalid entry. Returning to main menu." << endl;
				else {
					if (games[num] == games[selection-1])
						cout << "Boards are equal." << endl;
					else
						cout << "Boards are not equal." << endl;
				}
			}
		}
		else
			cout << "Invalid entry. Try again." << endl;
	}while (option != 3);
}
