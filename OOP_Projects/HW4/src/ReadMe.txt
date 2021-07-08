////////HW 3 INSTRUCTIONS////////////
When playing game, entering coordinates;
If you type SAVE filename, it saves the board to filename.
If you type LOAD filename, it loads the board from filename.
If you type MENU, it returns to main menu.
If you type COMPARE, it lists you all existing games and you choose one of them.

In menu, you can start a new game, continue to an existing game or exit. You can create a new game as much as you want. I printed my static filled_cell_count variable in menu.

My play() function for computer takes parameters. (I asked you the validity of this through e-mail but you did not answer).

I used friend to reach Cell's data with Hex public methods. Actually just for reaching to static member filled_cell_count. 

/////////HW 4 INSTRUCTIONS///////////////

-I made my >> operator my load function. So when you want to load a game, you have to type LOAD and enter first, then it is going to ask you for a filename. Because I can't pass filename as argument to >> overload function.

-In undo feature I overloaded my prefix and postfix -- operators. In UvsC, it undos user's and comp's last move. In UvsU, it asks permission from opponent to undo his last move too.

-I made my == operator my compare function. Sınce it checks equality, now it only determines marked cell number of two games are equal or not.

-You have to type UNDO when making a move. My UNDO works after loading a game too.

-I held my moves in int *move_order array in class for undo feature. It holds the cell number every time players make a move.