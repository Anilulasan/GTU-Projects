#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum{noone, cap, car}player_type;
typedef enum{start, property, tax, punish}block_type;

typedef struct{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
}player;

typedef struct{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	player owner;
	block_type type;
}block;

void init_the_board(block board[20]);
void show_board(block board[20], player player_one, player player_two);
void show_properties(block board[20]);
void all_zero(block board[20]);
void buy_property(block *current_block, player *current_player);
void sell_property(block board[20], player *current_player);
void gameplay(block board[20], player player_one, player player_two);
int menu();
void play(block board[20], player *current_player, int choice);
void case_1(block board[20], player *current_player);
void show_player_properties(block board[20], player current_player);
void buy_house(block *current_block, player *current_player);
void property_print(block board[20], int id_block);
void character_print(int number, char c, int backn);
int find_digits(int number);
int decider(int i, int j);
int calculate_rent(block current_block);
int count_owned_properties(block board[20], player *current_player);
int survive_test(block board[20], player current_player, int owned_count);

//YOU SHOULD USE 121x50 TERMINAL TO SEE THE BOARD AND SENTENCES CORRECTLY. 

int main() {
	srand(time(NULL));
	block board[20];
	player player_one, player_two;
	player_one.name = "Car"; player_one.type = cap; player_one.account = 100000;
	player_two.name = "Cap"; player_two.type = car; player_two.account = 100000;
	player_one.current_block_id = 0; player_one.turn_to_wait = 0;
	player_two.current_block_id = 0; player_two.turn_to_wait = 0;
	init_the_board(board);
	gameplay(board, player_one, player_two);
	
}

void init_the_board(block board[20]) {
	block startt, esenyurt, car_park, tuzla, arnavutkoy, wait_2_turn, catalca, beykoz, car_fix, maltepe, bills, sisli, oil, atasehir, sariyer, wait_1_turn, kadikoy, besiktas, vocation, bebek; 
	startt.name = "Start";			esenyurt.name = "Esenyurt";	  		  car_park.name = "Car park";	 		 tuzla.name = "Tuzla";			arnavutkoy.name = "Arnavutkoy";   		 wait_2_turn.name = "Wait 2 turn";			catalca.name = "Catalca";   	   beykoz.name = "Beykoz";   		car_fix.name = "Car fix";   	   maltepe.name = "Maltepe";   		  bills.name = "Bills";   		 sisli.name = "Sisli";   		oil.name = "Oil";   	   atasehir.name = "Atasehir";   		sariyer.name = "Sariyer";  		   wait_1_turn.name = "Wait 1 turn";   		  kadikoy.name = "Kadikoy";   		 besiktas.name = "Besiktas";   		  vocation.name = "Vocation";   	   bebek.name = "Bebek";
	startt.type = start;			esenyurt.price = 16000;		  		  car_park.price = 1500;				 tuzla.price = 16500;			arnavutkoy.price = 17000;				 wait_2_turn.price = 2;						catalca.price = 20000;	           beykoz.price = 23000;			car_fix.price = 1750;			   maltepe.price = 30000;			  bills.price = 2000;			 sisli.price = 33000;			oil.price = 2250;		   atasehir.price = 35000;				sariyer.price = 40000;			   wait_1_turn.price = 1;					  kadikoy.price = 43000;			 besiktas.price = 60000;			  vocation.price = 5000;			   bebek.price = 70000;		  
									esenyurt.rent = 800;				  car_park.type = tax;					 tuzla.rent = 850;				arnavutkoy.rent = 875;					 wait_2_turn.type = punish;					catalca.rent = 1000;			   beykoz.rent = 1100;				car_fix.type = tax;				   maltepe.rent = 1350;				  bills.type = tax;				 sisli.rent = 1500;				oil.type = tax;			   atasehir.rent = 1600;				sariyer.rent = 1750;			   wait_1_turn.type = punish;				  kadikoy.rent = 1900;				 besiktas.rent = 2500;				  vocation.type = tax;				   bebek.rent = 3500;										
									esenyurt.rent_1 = 4000;														 tuzla.rent_1 = 4250;			arnavutkoy.rent_1 = 4500;															catalca.rent_1 = 5000;			   beykoz.rent_1 = 5500;											   maltepe.rent_1 = 7000;											 sisli.rent_1 = 8000;									   atasehir.rent_1 = 8500;				sariyer.rent_1 = 9500;														  kadikoy.rent_1 = 11000;			 besiktas.rent_1 = 15000;												   bebek.rent_1 = 20000;
									esenyurt.rent_2 = 9000;			  										     tuzla.rent_2 = 9500;			arnavutkoy.rent_2 = 10000;					 										catalca.rent_2 = 12000;			   beykoz.rent_2 = 12500;											   maltepe.rent_2 = 15000;											 sisli.rent_2 = 16000;									   atasehir.rent_2 = 17000;				sariyer.rent_2 = 19000;			   											  kadikoy.rent_2 = 21500;			 besiktas.rent_2 = 28000;												   bebek.rent_2 = 35500;
									esenyurt.rent_3 = 25000;			  										 tuzla.rent_3 = 26000;			arnavutkoy.rent_3 = 28000;					 										catalca.rent_3 = 30000;			   beykoz.rent_3 = 33000;											   maltepe.rent_3 = 40000;											 sisli.rent_3 = 42000;									   atasehir.rent_3 = 45000;				sariyer.rent_3 = 48000;			   						  					  kadikoy.rent_3 = 55500;			 besiktas.rent_3 = 60000;												   bebek.rent_3 = 65000;
									esenyurt.house_price = 10000;			  									 tuzla.house_price = 12000;		arnavutkoy.house_price = 12000;					 									catalca.house_price = 13000;	   beykoz.house_price = 13000;										   maltepe.house_price = 15000;										 sisli.house_price = 16000;								   atasehir.house_price = 17000;		sariyer.house_price = 19000;			   									  kadikoy.house_price = 23000;		 besiktas.house_price = 30000;											   bebek.house_price = 35000;
									esenyurt.type = property;			  										 tuzla.type = property;			arnavutkoy.type = property;					 										catalca.type = property;		   beykoz.type = property;											   maltepe.type = property;											 sisli.type = property;									   atasehir.type = property;			sariyer.type = property;			   										  kadikoy.type = property;			 besiktas.type = property;												   bebek.type = property;								
	board[0] = startt, board[1] = esenyurt, board[2] = car_park, board[3] = tuzla, board[4] = arnavutkoy, board[5] = wait_2_turn, board[6] = catalca, board[7] = beykoz, board[8] = car_fix, board[9] = maltepe, board[10] = bills, board[11] = sisli, board[12] = oil, board[13] = atasehir, board[14] = sariyer, board[15] = wait_1_turn, board[16] = kadikoy, board[17] = besiktas, board[18] = vocation, board[19] = bebek;
	all_zero(board);
	board[0].type = start;			board[1].price = 16000;		  		  board[2].price = 1500;				 board[3].price = 16500;			board[4].price = 17000;				 board[5].price = 2;				board[6].price = 20000;	           		board[7].price = 23000;				board[8].price = 1750;			   board[9].price = 30000;			  	  board[10].price = 2000;		 board[11].price = 33000;			board[12].price = 2250;		    board[13].price = 35000;				board[14].price = 40000;			  board[15].price = 1;					  board[16].price = 43000;				board[17].price = 60000;			  board[18].price = 5000;			   board[19].price = 70000;		  
									board[1].rent = 800;				  board[2].type = tax;					 board[3].rent = 850;				board[4].rent = 875;				 board[5].type = punish;			board[6].rent = 1000;			  		board[7].rent = 1100;				board[8].type = tax;			   board[9].rent = 1350;				  board[10].type = tax;			 board[11].rent = 1500;				board[12].type = tax;			board[13].rent = 1600;					board[14].rent = 1750;			  	  board[15].type = punish;				  board[16].rent = 1900;				board[17].rent = 2500;				  board[18].type = tax;				   board[19].rent = 3500;										
									board[1].rent_1 = 4000;														 board[3].rent_1 = 4250;			board[4].rent_1 = 4500;													board[6].rent_1 = 5000;			 		board[7].rent_1 = 5500;											   	   board[9].rent_1 = 7000;											 	 board[11].rent_1 = 8000;									   		board[13].rent_1 = 8500;				board[14].rent_1 = 9500;													  board[16].rent_1 = 11000;				board[17].rent_1 = 15000;												   board[19].rent_1 = 20000;
									board[1].rent_2 = 9000;			  										     board[3].rent_2 = 9500;			board[4].rent_2 = 10000;					 							board[6].rent_2 = 12000;			    board[7].rent_2 = 12500;											   board[9].rent_2 = 15000;												 board[11].rent_2 = 16000;									   		board[13].rent_2 = 17000;				board[14].rent_2 = 19000;			   										  board[16].rent_2 = 21500;				board[17].rent_2 = 28000;												   board[19].rent_2 = 35500;
									board[1].rent_3 = 25000;			  										 board[3].rent_3 = 26000;			board[4].rent_3 = 28000;					 							board[6].rent_3 = 30000;			    board[7].rent_3 = 33000;											   board[9].rent_3 = 40000;												 board[11].rent_3 = 42000;									   		board[13].rent_3 = 45000;				board[14].rent_3 = 48000;			   						  				  board[16].rent_3 = 55500;				board[17].rent_3 = 60000;												   board[19].rent_3 = 65000;
									board[1].house_price = 10000;			  									 board[3].house_price = 12000;		board[4].house_price = 12000;					 						board[6].house_price = 13000;	  		board[7].house_price = 13000;										   board[9].house_price = 15000;										 board[11].house_price = 16000;								   		board[13].house_price = 17000;			board[14].house_price = 19000;			   									  board[16].house_price = 23000;		board[17].house_price = 30000;											   board[19].house_price = 35000;
									board[1].type = property;			  										 board[3].type = property;			board[4].type = property;					 							board[6].type = property;		  		board[7].type = property;											   board[9].type = property;											 board[11].type = property;									   		board[13].type = property;				board[14].type = property;			   										  board[16].type = property;			board[17].type = property;												   board[19].type = property;	
}

void all_zero(block board[20]) { // I made all values 0 then fill them on init_the_board().
	int i;
	for (i = 0; i < 20; i++) {
		board[i].block_id = i;
		board[i].price = 0;
		board[i].rent = 0;
		board[i].rent_1 = 0;
		board[i].rent_2 = 0;
		board[i].rent_2 = 0;
		board[i].rent_3 = 0;
		board[i].house_price = 0;
		board[i].house_count = 0;
		board[i].owner.type = 0;
	}
}

void show_board(block board[20], player player_one, player player_two) {
	int i, j, counter = 0, counter_p = 0, counter_pp = 0, counter_r = 19, counter_n = 0, counter_pr = 19, counter_pn = 0, counter_ppr = 19, counter_ppn = 0; //I did the same thing for all Name, price, player name statements.(i % 3 == 0, i % 3 == 1, i % 3 == 2). Counter holds how many property printed so far. Counter_r is 19 because it is the last index of array and prints last line and leftside blocks of the rectangle. Counter_n is 0 because it is the first index and prints first line and rightside blocks of rectangle. Counter_p is the counter for second line of the block(Prices). Counter_pp means is the counter for last line of the block(Player name). It goes like this.
	character_print(120, '-', 1);
	for (i = 0; i < 18; ++i) { //LINE
		for (j = 0; j < 120; ++j) { //COLUMN. I increased j everytime i write something.
			if ((j == 0 || j % 20 == 19) && decider(i,j) == 1) { //Decider decides if i,j values points the board. Especially after 3rd and before 15th lines.
				j++;
				printf("|");
			}
			if (j % 20 == 5 && decider(i, j) == 1) {
				if (i%3 == 0) { //NAME LINE
					if ((counter > 5 && counter < 14 && counter%2 == 0) || counter > 13) { //The board goes like 19 - 7 \n 18 - 6... after first 6 blocks and before last 6 blocks. So i assigned counter_r 19 then reduced it to print correctly. That statement checks if the block stays leftside of the board. If so, prints it.
						printf("%s",board[counter_r].name);
						if (board[counter_r].house_count > 0) {
							printf(" %dH",board[counter_r].house_count); //If block has house on it, prints that too.
							j += 3;
						}
						j += strlen(board[counter_r].name);
						counter_r--;
					}
					else { //Means the block stays rightside of the board. So counter_n (defined as 0 first, increasing) is our index there.
						printf("%s",board[counter_n].name);
						if (board[counter_n].house_count > 0) {
							printf(" %dH",board[counter_n].house_count); //If block has house on it, prints that too.
							j += 3;
						}
						j += strlen(board[counter_n].name);
						counter_n++;
					}
					counter++;
				}
				else if(i%3 == 1) { //PRICE LINE
					if ((counter_p > 5 && counter_p < 14 && counter_p%2 == 0) || counter_p > 13) {
						if (board[counter_pr].price > 10) {
							printf("%d$",board[counter_pr].price);
							j += find_digits(board[counter_pr].price) + 1;
						}
						counter_pr--;
					}
					else {
						if (board[counter_pn].price > 10) {
							printf("%d$",board[counter_pn].price);
							j += find_digits(board[counter_pn].price) + 1;
						}
						counter_pn++;
					}
					counter_p++;
				}
				else { //PLAYERS LINE
					if ((counter_pp > 5 && counter_pp < 14 && counter_pp%2 == 0) || counter_pp > 13) {
						if (player_one.current_block_id == counter_ppr) {
							printf("%s",player_one.name);
							j+= 3;
						}
						if (player_two.current_block_id == counter_ppr) {
							printf("%s",player_two.name);
							j+= 3;
						}
						counter_ppr--;
					}
					else {
						if (player_one.current_block_id == counter_ppn) {
							printf("%s",player_one.name);
							j+= strlen(player_one.name);
						}
						if (player_two.current_block_id == counter_ppn) {
							printf("%s",player_two.name);
							j+= strlen(player_two.name);
						}
						counter_ppn++;
					}
					counter_pp++;
				}
			}
			printf(" ");
		}
		if (i % 3 == 2) {
			if (i < 3 || i > 13)
				character_print(120, '-', 1);
			else {
				character_print(20, '-', 0);
				character_print(79, ' ', 0);
				character_print(21, '-', 0);
				printf("\n");
			}
		}
	}
}

void character_print(int number, char c, int backn) { //Helps on show_board function. Prints the characters that takes as parameter.
	int i;
	for (i = 0; i < number; ++i) {
		printf("%c",c);
	}
	if (backn == 1)
		printf("\n");
}

int power(int base, int exponent) { //Helps on find_digits function.
	if (exponent == 0)
		return 1;
	if (exponent == 1) 
		return base;
	return base * power(base, exponent - 1);
}

int find_digits(int number) { //Helps to increase the j in show_board() function. 
	int i;
	for (i = 0; i < 10; ++i) {
		if (number < power(10, i))
			break;
	}
	if (i == 0)
		return 1;
	return i;
}

int decider(int i, int j) { //Decides if (i,j) points the board or the void in the center.
	if (i < 3 || i > 14)
		return 1;
	else if(j < 21 || j > 98)
		return 1;
	return 0;
}

void show_properties(block board[20]) { //Shows player's properties.
	int choice;
	do {
		printf("Please select a property to see details:\n1 - \tEsenyurt\n3 - \tTuzla\n4 - \tArnavutkoy\n6 - \tCatalca\n7 - \tBeykoz\n9 - \tMaltepe\n11 - \tSisli\n13 - \tAtasehir\n14 - \tSariyer\n16 - \tKadikoy\n17 - \tBesiktas\n19 - \tBebek\n0 - \tExit\n");
		scanf("%d",&choice);
		if (choice != 0) 
			property_print(board, choice);
	}while(choice != 0);
	printf("\n\n");
	
}

void property_print(block board[20], int id_block) { //Prints properties.
		character_print(36, '-', 1);
		printf("|");
		character_print(13, ' ', 0);
		printf("%s",board[id_block].name );
		character_print(12 + (9 - strlen(board[id_block].name)), ' ', 0);
		printf("|\n");
		character_print(36, '-', 1);
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent");
		character_print(15, ' ',0 );
		printf("%d$",board[id_block].rent );
		character_print(7 - find_digits(board[id_block].rent), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 1 H");
		character_print(11, ' ',0 );
		printf("%d$",board[id_block].rent_1 );
		character_print(7 - find_digits(board[id_block].rent_1), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 2 H");
		character_print(11, ' ',0 );
		printf("%d$",board[id_block].rent_2 );
		character_print(7 - find_digits(board[id_block].rent_2), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 3 H");
		character_print(11, ' ',0 );
		printf("%d$",board[id_block].rent_3 );
		character_print(7 - find_digits(board[id_block].rent_3), ' ', 0);
		printf("|\n");
		character_print(36, '-', 1);
		printf("|");
		character_print(7, ' ', 0);
		printf("House price");
		character_print(8, ' ', 0);
		printf("%d$",board[id_block].house_price);
		character_print(7 - find_digits(board[id_block].house_price), ' ', 0);
		printf("|\n");
		character_print(36, '-', 1);
}

void buy_property(block *current_block, player *current_player) { //Tests all the things needed to buy a property. If player passes all tests, then buys it.
	int choice, tests = 0;
	if (current_block->type == property)
		tests++;
	else
		printf("This place is not a property!\n");
	if (current_block->owner.type == noone)
		tests++;
	else
		printf("This place has an owner!\n");
	if (current_player->current_block_id == current_block->block_id)
		tests++;
	else
		printf("You are not on that block!\n");
	if (current_player->account >= current_block->price)
		tests++;
	else
		printf("You can not afford this place's price!\n");

	if (tests == 4) {
		current_block->owner = *current_player;
		current_block->owner.type = current_player->type;
		current_player->account -= current_block->price;
		buy_house(current_block, current_player);
	}
}

void buy_house(block *current_block, player *current_player) { //Tests all the things to buy a house. Asks player to buy a house until player cant afford a house or buys 3 house.
	int i, count = 0;
	char choice;
	if (current_block->owner.type == current_player->type) {
		if (current_block->house_count == 3) 
			printf("You can not build more than 3 house!\n");
		else {
			for (i = 0; i < 3; i++) {
				printf("Do you want to build a house?(Y/N): ");
				scanf(" %c", &choice);
				if (choice == 'Y' || choice == 'y') {
					if (current_player->account >= current_block->house_price) {
						current_block->house_count++;
						current_player->account -= current_block->house_price;
					}
					else {
						printf("You dont have enough money to buy a house.\n");
						break;
					}
					if (current_block->house_count == 3) {
						printf("You have 3 house on your property. You can not build more.\n");
						break;
					}
				}
				else
					break;
			}
		}
	}
	else
		printf("This place in not your property!\n");
}

void sell_property(block board[20], player *current_player) { //Sells a property then shifts owned_block_ids array.
	int i, choice, owned, index;
	printf("These are your properties, select one to sell it to the bank: \n");
	owned = count_owned_properties(board, current_player);
	show_player_properties(board, *current_player);
	printf("-1 - Exit\n");
	scanf("%d",&choice);
	index = current_player->owned_block_ids[choice];
	if (choice != -1 && board[index].owner.type == current_player->type) {
		board[index].owner.type = noone;
		board[index].house_count = 0;
		current_player->account += (board[index].price + board[index].house_price * board[index].house_count) / 2;
		owned --;
		for (i = choice; i < owned; i++) {
			current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
		}
	}
	else if (choice != -1)
		printf("Invalid entry. Please try again later...\n");
	
}

void gameplay(block board[20], player player_one, player player_two) { //Play
	int i, choice, turn = 2;
	do {
		if (turn%2 == 0)
			printf("%s's turn...\n",player_one.name);
		if (turn%2 == 1)
			printf("%s's turn...\n",player_two.name);
		do {
			show_board(board, player_one, player_two);
			choice = menu();
			if (choice < 1 || choice > 7) {
				printf("Invalid choice, please select valid choice: ");
				scanf("%d",&choice);
			}
			if (turn%2 == 0) //Player one
				play(board, &player_one, choice);
			else //Player two
				play(board, &player_two, choice);
		}while(choice != 1);

		 
		for (i = 0; i < 2; i++) { //If both players in punishment, reduces the values until one of them's punishment is over.
			if (player_one.turn_to_wait > 0 && player_two.turn_to_wait > 0) {
				player_one.turn_to_wait --;
				player_two.turn_to_wait --;
			}
			else
				break;
		}

		if (turn%2 == 0) {
			if (board[player_one.current_block_id].owner.type == player_two.type && player_one.account >= 0) //Tests if the player_one ended the turn on other player's property. If he can afford, increases player_two.account as the rent. Reduces player_one 's account in case_1 function.
				player_two.account += calculate_rent(board[player_one.current_block_id]); 
			if (player_two.turn_to_wait == 0) //If the other player is not in punishment, passes turn to him.
				turn++;
			else //If not, he plays one more turn until other player's punishment is over. Reduces the puniish value as 1 everytime one turn is over.
				player_two.turn_to_wait--;
		}
		else {
			if (board[player_two.current_block_id].owner.type == player_one.type && player_two.account >= 0) //Does the same for player two. (399th line)
				player_one.account += calculate_rent(board[player_two.current_block_id]);
			if (player_one.turn_to_wait == 0) //If the other player is not in punishment, passes turn to him.
				turn++;
			else //If not, he plays one more turn until other player's punishment is over. Reduces the puniish value as 1 everytime one turn is over.
				player_one.turn_to_wait--;
		}

	}while(player_one.account >= 0 && player_two.account >= 0);
	if (player_one.account > 0)
		printf("Congratulations %s. You won!\n",player_one.name);
	else
		printf("Congratulations %s. You won!\n",player_two.name );
}

int menu() {
	int choice;
	printf("1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue:\n");
	scanf("%d",&choice);
	return choice;
}

void play(block board[20], player *current_player, int choice) { //Executes the choices here.
	switch(choice) {
		case 1: case_1(board, current_player); break;
		case 2: printf("You have %d$ in your account.\n",current_player->account); break;
		case 3: show_player_properties(board, *current_player); break;
		case 4: show_properties(board); break;
		case 5: buy_property(&board[current_player->current_block_id] , current_player); break;
		case 6: buy_house(&board[current_player->current_block_id] , current_player);	break;
		case 7: sell_property(board, current_player);	break;
	}
}

void show_player_properties(block board[20], player current_player) { //Case 3 in play() function.
	int i, owned;
	owned = count_owned_properties(board, &current_player);
	if (owned == 0)
		printf("You dont have a property\n");
	for (i = 0; i < owned; i++) {
		printf(" %d - %s\n",i, board[current_player.owned_block_ids[i]].name);
	}
}

void case_1(block board[20], player *current_player) { //First, rolls the dice. Then checks which type of block he came in to, then does what needed on the block.
	int dice, rent_value, owned_count;
	char choice;
	dice = rand()%6 + 1;
	printf("Rolling a dice: %d\n",dice);
	current_player->current_block_id += dice;
	if (current_player->current_block_id > 19) { //Means player passed or on the start block. Increases player's account 10000$ and mods the current_block_id value.
		current_player->current_block_id = current_player->current_block_id%20;
		current_player->account += 10000;
	}
	printf("Now on %s block.\n",board[current_player->current_block_id].name ); // I didnt want to show the board so often, so i just wrote where he came after rolling a dice.
	owned_count = count_owned_properties(board, current_player); //For survive_test function.
	rent_value = calculate_rent(board[current_player->current_block_id]); //I assigned the rent_value there, bacause it works on all the payments and i wanted to print if player has to pay something.
	if (board[current_player->current_block_id].type == punish) {
		printf("You are on a punish block. You have to rest %d turns.\n", rent_value);
		current_player->turn_to_wait = rent_value;
	}
	if(board[current_player->current_block_id].type == tax) {
		printf("You are on a tax block. You have to pay the tax fee.\n\tPayment: %d$\n",rent_value);
		current_player->account -= rent_value; //Doesnt matter if player has enough money to pay, i reduced it. Because it checks if he can survive after that and if he can account increases as he sells the properties. So it goes to same place.
		if (current_player->account <= 0) {
			if (current_player->account + survive_test(board ,*current_player, owned_count) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
				printf("You are bankrupt! Game is over.\n");
			else {
				do {
					printf("You can not pay this, you have to sell some of your properties!\n");
					sell_property(board, current_player);
				}while(current_player->account < 0); //Doesnt end until he can pay the rent;
			}
		}
	}
	if (board[current_player->current_block_id].type == property) {
		if (board[current_player->current_block_id].owner.type == current_player->type) { //If player comes to his own property, asks him if he wants to build a house.
			printf("Welcome to your property. Do you want to build house?(Y/N): ");
			scanf(" %c",&choice);
			if (choice == 'Y' || choice == 'y')
				buy_house(&board[current_player->current_block_id], current_player);
		}
		else if (board[current_player->current_block_id].owner.type != noone) { //If player comes to other player's property, pays the rent.
			printf("You came to other player's property. You have to pay to rent.\n\tPayment: %d$\n", rent_value);
			current_player->account -= rent_value; //Doesnt matter if player has enough money to pay, i reduced it. Because it checks if he can survive after that and if he can account increases as he sells the properties. So it goes to same place.
			if (current_player->account <= 0) {
				if (current_player->account + survive_test(board ,*current_player, owned_count) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
					printf("You are bankrupt! Game is over.\n");
				else {
					do {
						printf("You can not pay this, you have to sell some of your properties!\n");
						sell_property(board, current_player);
					}while(current_player->account < 0); //Doesnt end until he can pay the rent;
				}
			}

		}
		else { //If player comes to unowned property, asks him if he wants to buy it. If he buys, asks him if he wants to buy a house.
			printf("Dou you want to buy this property?(Y/N): ");
			scanf(" %c",&choice);
			if (choice == 'Y' || choice == 'y')
				buy_property(&board[current_player->current_block_id], current_player);
		}
	}

	printf("%s's turn is over.\n",current_player->name );
}

int calculate_rent(block current_block) { //Calculates current block's rent.
	int rent_value;
	switch(current_block.house_count) {
		case 1: rent_value = current_block.rent_1; break;
		case 2: rent_value = current_block.rent_2; break;
		case 3: rent_value = current_block.rent_3; break;
		default: rent_value = current_block.rent; 
	}
	if (current_block.type == tax || current_block.type == punish)
		rent_value = current_block.price;
	return rent_value;
}	

int count_owned_properties(block board[20], player *current_player) { //In buy_property() function i didnt fill the owned_block_ids array of the player. There i assign the owned blocks to that array and return how many property does he have. 
	int i, counter = 0;
	for (i = 0; i < 19; i++) {
		if (board[i].owner.type == current_player->type) {
			current_player->owned_block_ids[counter] = i;
			counter++;
		}
	}
	return counter;
}

int survive_test(block board[20], player current_player, int owned_count) { //If player cant pay a rent or tax, it tests if he can pay them after selling all his properties. If not, game is over he is bankrupt.
	int i, value = 0;
	for (i = 0; i < owned_count; i++) {
		value += (board[current_player.owned_block_ids[i]].price + board[current_player.owned_block_ids[i]].house_price * board[current_player.owned_block_ids[i]].house_count) / 2;
	}
	return value;
}




	
	





