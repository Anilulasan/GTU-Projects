#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum{noone, car, cap}player_type;
typedef enum{start, property, tax, punish, fortune}block_type;

typedef struct{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
}player;

typedef struct{
	char *name;
}fortune_card;

struct blockk{
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
	fortune_card f_card[5];
	struct blockk *next; 
};
typedef struct blockk block;



void init_the_board(block *root);
void show_board(block *root, player player_one, player player_two);
void show_properties(block *root);
void all_zero(block *root);
void buy_property(block *current_block, player *current_player);
void sell_property(block *root, player *current_player);
void gameplay(block *root, player player_one, player player_two);
int menu();
void play(block *root, player *current_player, int choice, int *);
void case_1(block *root, player *current_player, int *);
void show_player_properties(block *root, player current_player);
void buy_house(block *current_block, player *current_player);
void property_print(block *root, int id_block);
void character_print(int number, char c, int backn);
int find_digits(int number);
int decider(int i, int j);
int calculate_rent(block current_block);
int count_owned_properties(block *root, player *current_player);
int survive_test(block *root, player current_player, int owned_count);
int Fortune(block *root, player *current_player);
block go_to_list(block *iter, int number);
block go_to_list_f(block *root, int number, player *current_player, void f(block *current_block, player *current_player));
void sell(block *current_block, player *current_player);
void play_AI(block *root, player *current_player, int *);
int find_highest(block *root, player current_player, int owned_count);
double average_properties(block *root);
void buy_house_AI(block *root, player *current_player);
void buy_property_AI(block *root, player *current_player);


//YOU SHOULD USE 141x52 TERMINAL TO SEE THE BOARD AND SENTENCES CORRECTLY. 

int main() {
	srand(time(NULL));
	block *root, *iter, *t, temp;
	player player_one, player_two;
	player_one.name = "Car"; player_one.type = car; player_one.account = 100000;
	player_two.name = "Cap"; player_two.type = cap; player_two.account = 100000;
	player_one.current_block_id = 0; player_one.turn_to_wait = 0;
	player_two.current_block_id = 0; player_two.turn_to_wait = 0;
	root = (block*)malloc(sizeof(block));
	init_the_board(root);
	show_board(root, player_one, player_two);
	gameplay(root, player_one, player_two);
}

void init_the_board(block *root) {
	block *iter;
	block startt, esenyurt, car_park, tuzla, arnavutkoy, wait_2_turn, catalca, beykoz, car_fix, maltepe, bills, sisli, oil, atasehir, sariyer, wait_1_turn, kadikoy, besiktas, vocation, bebek, fortunee; 
	fortune_card fortune1, fortune2, fortune3, fortune4, fortune5;
	startt.name = "Start";			esenyurt.name = "Esenyurt";	  		  car_park.name = "Car park";	 		 tuzla.name = "Tuzla";			arnavutkoy.name = "Arnavutkoy";   		 wait_2_turn.name = "Wait 2 turn";			catalca.name = "Catalca";   	   beykoz.name = "Beykoz";   		car_fix.name = "Car fix";   	   maltepe.name = "Maltepe";   		  bills.name = "Bills";   		 sisli.name = "Sisli";   		oil.name = "Oil";   	   atasehir.name = "Atasehir";   		sariyer.name = "Sariyer";  		   wait_1_turn.name = "Wait 1 turn";   		  kadikoy.name = "Kadikoy";   		 besiktas.name = "Besiktas";   		  vocation.name = "Vocation";   	   bebek.name = "Bebek";
	startt.type = start;			esenyurt.price = 16000;		  		  car_park.price = 1500;				 tuzla.price = 16500;			arnavutkoy.price = 17000;				 wait_2_turn.price = 2;						catalca.price = 20000;	           beykoz.price = 23000;			car_fix.price = 1750;			   maltepe.price = 30000;			  bills.price = 2000;			 sisli.price = 33000;			oil.price = 2250;		   atasehir.price = 35000;				sariyer.price = 40000;			   wait_1_turn.price = 1;					  kadikoy.price = 43000;			 besiktas.price = 60000;			  vocation.price = 5000;			   bebek.price = 70000;		  
	startt.house_count = 0;			esenyurt.rent = 800;				  car_park.type = tax;					 tuzla.rent = 850;				arnavutkoy.rent = 875;					 wait_2_turn.type = punish;					catalca.rent = 1000;			   beykoz.rent = 1100;				car_fix.type = tax;				   maltepe.rent = 1350;				  bills.type = tax;				 sisli.rent = 1500;				oil.type = tax;			   atasehir.rent = 1600;				sariyer.rent = 1750;			   wait_1_turn.type = punish;				  kadikoy.rent = 1900;				 besiktas.rent = 2500;				  vocation.type = tax;				   bebek.rent = 3500;										
									esenyurt.rent_1 = 4000;				  car_park.house_count = 0;	  			 tuzla.rent_1 = 4250;			arnavutkoy.rent_1 = 4500;				 wait_2_turn.house_count = 0;				catalca.rent_1 = 5000;			   beykoz.rent_1 = 5500;			car_fix.house_count = 0;		   maltepe.rent_1 = 7000;			  bills.house_count = 0;		 sisli.rent_1 = 8000;			oil.house_count = 0;	   atasehir.rent_1 = 8500;				sariyer.rent_1 = 9500;			   wait_1_turn.house_count = 0;				  kadikoy.rent_1 = 11000;			 besiktas.rent_1 = 15000;			  vocation.house_count = 0;			   bebek.rent_1 = 20000;
									esenyurt.rent_2 = 9000;			  										     tuzla.rent_2 = 9500;			arnavutkoy.rent_2 = 10000;					 										catalca.rent_2 = 12000;			   beykoz.rent_2 = 12500;											   maltepe.rent_2 = 15000;											 sisli.rent_2 = 16000;									   atasehir.rent_2 = 17000;				sariyer.rent_2 = 19000;			   											  kadikoy.rent_2 = 21500;			 besiktas.rent_2 = 28000;												   bebek.rent_2 = 35500;
									esenyurt.rent_3 = 25000;			  										 tuzla.rent_3 = 26000;			arnavutkoy.rent_3 = 28000;					 										catalca.rent_3 = 30000;			   beykoz.rent_3 = 33000;											   maltepe.rent_3 = 40000;											 sisli.rent_3 = 42000;									   atasehir.rent_3 = 45000;				sariyer.rent_3 = 48000;			   						  					  kadikoy.rent_3 = 55500;			 besiktas.rent_3 = 60000;												   bebek.rent_3 = 65000;
									esenyurt.house_price = 10000;			  									 tuzla.house_price = 12000;		arnavutkoy.house_price = 12000;					 									catalca.house_price = 13000;	   beykoz.house_price = 13000;										   maltepe.house_price = 15000;										 sisli.house_price = 16000;								   atasehir.house_price = 17000;		sariyer.house_price = 19000;			   									  kadikoy.house_price = 23000;		 besiktas.house_price = 30000;											   bebek.house_price = 35000;
									esenyurt.type = property;			  										 tuzla.type = property;			arnavutkoy.type = property;					 										catalca.type = property;		   beykoz.type = property;											   maltepe.type = property;											 sisli.type = property;									   atasehir.type = property;			sariyer.type = property;			   										  kadikoy.type = property;			 besiktas.type = property;												   bebek.type = property;								
									esenyurt.house_count = 0;
																												 tuzla.house_count = 0;			arnavutkoy.house_count = 0;															catalca.house_count = 0;		   beykoz.house_count = 0;											   maltepe.house_count = 0;											 sisli.house_count = 0;									   atasehir.house_count = 0;			sariyer.house_count = 0;													  kadikoy.house_count = 0;			 besiktas.house_count = 0;												   bebek.house_count = 0;
	fortune1.name = "Free House";		
    fortune2.name = "Time Travel";		
    fortune3.name = "Garnishment";		
    fortune4.name = "Generosity";
    fortune5.name = "Treasure Hunter";

	fortunee.name = "Fortune Card";	fortunee.price = 0;  	fortunee.house_count = 0;	fortunee.type = fortune;
	fortunee.f_card[0] = fortune1;
	fortunee.f_card[1] = fortune2;
	fortunee.f_card[2] = fortune3;
	fortunee.f_card[3] = fortune4;
	fortunee.f_card[4] = fortune5; 

    *root = startt;
	root->next = (block*)malloc(sizeof(block)); *root->next = esenyurt; 		iter = root->next; 
	iter->next = (block*)malloc(sizeof(block)); *iter->next = car_park; 		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = fortunee;  		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = tuzla;     		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = arnavutkoy;		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = wait_2_turn;		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = catalca;			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = beykoz; 			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = fortunee; 		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = car_fix;			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = maltepe; 			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = bills;			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = sisli; 			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = oil;				iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = fortunee;  		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = atasehir; 		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = sariyer; 			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = wait_1_turn; 		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = kadikoy; 			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = besiktas;			iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = fortunee;  		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = vocation; 		iter = iter->next;
	iter->next = (block*)malloc(sizeof(block)); *iter->next = bebek; 			iter = iter->next;
	all_zero(root);
}

void all_zero(block *root) { // I made all values 0 then fill them on init_the_board().
	int i;
	for (i = 0; i < 24; i++) {
		root->block_id = i;
		root->house_count = 0;
		root->owner.type = 0;
		if (root->type != property) {
			root->rent = 0;
			root->rent_1 = 0;
			root->rent_2 = 0;
			root->rent_3 = 0;
			root->house_price = 0;
		}
		if (i == 0)
			root->price = 0;
		root = root->next;	
	}
}

void show_board(block *root, player player_one, player player_two) {
	int i, j, counter = 0, counter_p = 0, counter_pp = 0, counter_r = 23, counter_n = 0, counter_pr = 23, counter_pn = 0, counter_ppr = 23, counter_ppn = 0; //I did the same thing for all Name, price, player name statements.(i % 3 == 0, i % 3 == 1, i % 3 == 2). Counter holds how many property printed so far. Counter_r is 19 because it is the last index of array and prints last line and leftside blocks of the rectangle. Counter_n is 0 because it is the first index and prints first line and rightside blocks of rectangle. Counter_p is the counter for second line of the block(Prices). Counter_pp means is the counter for last line of the block(Player name). It goes like this.
	block temp;
	character_print(140, '-', 1);
	for (i = 0; i < 21; ++i) { //LINE
		for (j = 0; j < 140; ++j) { //COLUMN. I increased j everytime i write something.
			if ((j == 0 || j % 20 == 19) && decider(i,j) == 1) { //Decider decides if i,j values points the board. Especially after 3rd and before 15th lines.
				j++;
				printf("|");
			}
			if (j % 20 == 5 && decider(i, j) == 1) {
				if (i%3 == 0) { //NAME LINE
					if ((counter > 5 && counter < 17 && counter%2 == 1) || counter > 16) { //The board goes like 19 - 7 \n 18 - 6... after first 6 blocks and before last 6 blocks. So i assigned counter_r 19 then reduced it to print correctly. That statement checks if the block stays leftside of the board. If so, prints it.
						temp = go_to_list(root, counter_r);
						printf("%s",temp.name);
						if (temp.house_count > 0) {
							printf(" %dH",temp.house_count); //If block has house on it, prints that too.
							j += 3;
						}
						j += strlen(temp.name);
						counter_r--;
					}
					else { //Means the block stays rightside of the board. So counter_n (defined as 0 first, increasing) is our index there.
						temp = go_to_list(root, counter_n);
						printf("%s",temp.name);
						if (temp.house_count > 0) {
							printf(" %dH",temp.house_count); //If block has house on it, prints that too.
							j += 3;
						}
						j += strlen(temp.name);
						counter_n ++;
					}
					counter++;
				}
				else if(i%3 == 1) { //PRICE LINE
					if ((counter_p > 5 && counter_p < 17 && counter_p%2 == 1) || counter_p > 16) {
						temp = go_to_list(root, counter_pr);
						if (temp.price > 10) {
							printf("%d$",temp.price);
							j += find_digits(temp.price) + 1;
						}
						counter_pr--;
					}
					else {
						temp = go_to_list(root, counter_pn);
						if (temp.price > 10) {
							printf("%d$",temp.price);
							j += find_digits(temp.price) + 1;
						}
						counter_pn++;
					}
					counter_p++;
				}
				else { //PLAYERS LINE
					if ((counter_pp > 5 && counter_pp < 17 && counter_pp%2 == 1) || counter_pp > 16) {
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
			if (i < 3 || i > 14)
				character_print(140, '-', 1);
			else {
				character_print(20, '-', 0);
				character_print(99, ' ', 0);
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
	if (i < 3 || i > 17)
		return 1;
	else if(j < 21 || j > 118)
		return 1;
	return 0;
}

void show_properties(block *root) { //Shows player's properties.
	int choice;
	do {
		printf("Please select a property to see details:\n1 - \tEsenyurt\n4 - \tTuzla\n5 - \tArnavutkoy\n7 - \tCatalca\n8 - \tBeykoz\n11 - \tMaltepe\n13 - \tSisli\n16 - \tAtasehir\n17 - \tSariyer\n19 - \tKadikoy\n20 - \tBesiktas\n23 - \tBebek\n0 - \tExit\n");
		scanf("%d",&choice);
		if (choice != 0) 
			property_print(root, choice);
	}while(choice != 0);
	printf("\n\n");
	
}

void property_print(block *root, int id_block) { //Prints properties.
		block temp;
		temp = go_to_list(root, id_block);
		character_print(36, '-', 1);
		printf("|");
		character_print(13, ' ', 0);
		printf("%s",temp.name );
		character_print(12 + (9 - strlen(temp.name)), ' ', 0);
		printf("|\n");
		character_print(36, '-', 1);
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent");
		character_print(15, ' ',0 );
		printf("%d$",temp.rent );
		character_print(7 - find_digits(temp.rent), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 1 H");
		character_print(11, ' ',0 );
		printf("%d$",temp.rent_1 );
		character_print(7 - find_digits(temp.rent_1), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 2 H");
		character_print(11, ' ',0 );
		printf("%d$",temp.rent_2 );
		character_print(7 - find_digits(temp.rent_2), ' ', 0);
		printf("|\n");
		printf("|");
		character_print(7, ' ', 0);
		printf("Rent 3 H");
		character_print(11, ' ',0 );
		printf("%d$",temp.rent_3 );
		character_print(7 - find_digits(temp.rent_3), ' ', 0);
		printf("|\n");
		character_print(36, '-', 1);
		printf("|");
		character_print(7, ' ', 0);
		printf("House price");
		character_print(8, ' ', 0);
		printf("%d$",temp.house_price);
		character_print(7 - find_digits(temp.house_price), ' ', 0);
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

void sell_property(block *root, player *current_player) { //Sells a property then shifts owned_block_ids array.
	int i, choice, owned, index;
	block temp;
	printf("These are your properties, select one to sell it to the bank: \n");
	owned = count_owned_properties(root, current_player);
	show_player_properties(root, *current_player);
	if (owned >= 1) {
		printf("-1 - Exit\n");
		scanf("%d",&choice);
		index = current_player->owned_block_ids[choice];
		temp = go_to_list(root, index);
		if (choice != -1 && temp.owner.type == current_player->type) {
			go_to_list_f(root, index, current_player, sell);
			for (i = choice; i < owned; i++) {
				current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
			}
		}
		else if (choice != -1)
			printf("Invalid entry. Please try again later...\n");
	}
	
}

void sell(block *current_block, player *current_player) { //Used in sell_property function. I seperated this function to fit to go_to_list_f() function.	
	current_player->account += (current_block->price + current_block->house_price * current_block->house_count) / 2;
	current_block->owner.type = noone;
	current_block->house_count = 0;
}

void buy_property_AI(block *root, player *current_player) {
	int i, dice, owned, flag = 0;
	double average;
	block *iter;
	iter = root;
	average = average_properties(root);
	owned = count_owned_properties(root, current_player);
	for (i = 0; i < current_player->current_block_id; i++) {
		iter = iter->next;
	}
	if (root->price < average)
		flag = 1;
	else {
		dice = rand()%6 + 1;
		printf("Computer rolling a dice for property: %d\n",dice );
		if (dice < 4)
			flag = 1;
	}
	if (flag == 1) {
		current_player->account -= iter->price;
		printf("Cap bought %s.\n",iter->name);
		iter->owner = *current_player;
		iter->owner.type = current_player->type;
		if (owned >= 4) 
			buy_house_AI(root, current_player);
	}
	printf("Cap's account: %d$\n",current_player->account );
}

void buy_house_AI(block *root, player *current_player) {
	int i, dice, flag;
	for (i = 0; i < current_player->current_block_id; i++) {
		root = root->next;
	}
	do {
		if (current_player->account >= root->house_price) {
			dice = rand()%6 + 1;
			printf("Computer rolling a dice for house: %d\n",dice );
			if (dice < 4) {
				current_player->account -= root->house_price;
				root->house_count++;
				printf("Computer built %d. house to %s\n",root->house_count ,root->name );
				flag = 1;
			}
			else
				flag = 0;
			if (root->house_count == 3) {
				printf("Cap reached maximum number of houses on that property.\n");
				flag = 0;
			}
		}
		else {
			printf("Cap doesnt have enough money to build a house.\n");
			flag = 0;
		}
	}while (flag == 1);
			
}

int Fortune(block *root, player *current_player) {
	int i, dice, dice1, choice, owned, index, index_id, payment;
	block temp, *iter;
	dice = rand()%5 + 1;
	temp = go_to_list(root, current_player->current_block_id);
	printf("%s picked %s\n",current_player->name,temp.f_card[dice - 1].name);
	if (dice == 1) {
		owned = count_owned_properties(root, current_player);
		if (owned > 0 && current_player->type == car) {
			show_player_properties(root, *current_player);
			printf("Choose which property do you want to build a house!\n");
			scanf("%d",&choice);
			temp = go_to_list(root, choice);
			if (temp.owner.type == current_player->type) {
				if (temp.house_count < 3) {
					iter = root;
					for (i = 0; i < choice; i++) {
						iter = iter->next;
					}
					iter->house_count++;
				}
				else {
					printf("You already have 3 house in that property!\n");
				}
			}
			else {
				printf("This is not your property\n");
			}
		}
		else if(owned > 0 && current_player->type == cap) {
			dice1 = rand()%owned + 1;
			iter = root;
			for (i = 0; i < dice1; i++) {
				iter = iter->next;
			}
			iter->house_count++;
		}
		else 
			printf("You dont have a property to build a house\n");
	}
	else if (dice == 2) {
		dice1 = rand()%6 + 1;
		printf("%s rolling a dice: %d\n",current_player->name, dice1 );
		if (dice1 < 4) {
			current_player->current_block_id += 2;
			if (current_player->current_block_id > 23) {
				current_player->current_block_id = current_player->current_block_id % 24;
				current_player->account += 10000;
			}
		}
		else {
			current_player->current_block_id -= 2;
		}
		temp = go_to_list(root, current_player->current_block_id);
		printf("Now on %s block\n",temp.name );
	}
	else if (dice == 3) {
		payment = 5000;
		printf("Payment to the bank: %d$\n", payment);
		current_player->account -= payment;
		if (current_player->account < 0 && current_player->type == car) {
			if (current_player->account + survive_test(root ,*current_player, owned) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
				printf("You are bankrupt! Game is over.\n");
			else {
				do {
					printf("You can not pay this, you have to sell some of your properties!\n");
					sell_property(root, current_player);
				}while(current_player->account < 0); //Doesnt end until he can pay the rent;
			}
		}
		else if (current_player->account < 0 && current_player->type == cap) {
			if (current_player->account + survive_test(root, *current_player, owned) >= payment) {
				printf("Cap does not have enough money. He has to sell properties to pay the tax fee.\n");
				index_id = find_highest(root, *current_player, owned);
				index = current_player->owned_block_ids[index_id];
				temp = go_to_list(root, index);
				printf("Cap sold %s.\n",temp.name );
				go_to_list_f(root, index, current_player, sell);
				for (i = index_id; i < owned; i++) {
					current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
				}
			}
			else
				printf("Cap is bankrupt! Game is over.\n");
		}
	}
	else if (dice == 4) {
		payment = 10000;
		printf("%s have to pay %d$ to other player.\n",current_player->name, payment);
		current_player -= 10000;
		if (current_player->account < 0 && current_player->type == car) {
			if (current_player->account + survive_test(root ,*current_player, owned) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
				printf("You are bankrupt! Game is over.\n");
			else {
				do {
					printf("You can not pay this, you have to sell some of your properties!\n");
					sell_property(root, current_player);
				}while(current_player->account < 0); //Doesnt end until he can pay the rent;
			}
		}
		else if (current_player->account < 0 && current_player->type == cap) {
			if (current_player->account + survive_test(root, *current_player, owned) >= payment) {
				printf("Cap does not have enough money. He has to sell properties to pay the tax fee.\n");
				index_id = find_highest(root, *current_player, owned);
				index = current_player->owned_block_ids[index_id];
				temp = go_to_list(root, index);
				printf("Cap sold %s.\n",temp.name );
				go_to_list_f(root, index, current_player, sell);
				for (i = index_id; i < owned; i++) {
					current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
				}
			}
			else
				printf("Cap is bankrupt! Game is over.\n");
		} 
	}
	else {
		payment = 20000;
		printf("%s won %d$ from bank!\n",current_player->name, payment );
		current_player->account += payment;
	}
	return dice;
}

void gameplay(block *root, player player_one, player player_two) { //Play
	int i, choice, turn = 2, test_fortune4;
	block temp;
	do {
		test_fortune4 = -1;
		if (turn%2 == 0) {
			character_print(140, '-', 1);
			printf("%s's turn...\n",player_one.name);	
			do {
				choice = menu();
				if (choice < 1 || choice > 7) {
					printf("Invalid choice, please select valid choice: ");
					scanf("%d",&choice);
				}
				play(root, &player_one, choice, &test_fortune4);
			}while(choice != 1);
		}
		else {
			character_print(140, '-', 1);
			printf("%s's turn...\n",player_two.name);
			play_AI(root, &player_two, &test_fortune4);
		}
		show_board(root, player_one, player_two);
		 
		for (i = 0; i < 2; i++) { //If both players in punishment, reduces the values until one of them's punishment is over.
			if (player_one.turn_to_wait > 0 && player_two.turn_to_wait > 0) {
				player_one.turn_to_wait --;
				player_two.turn_to_wait --;
			}
			else
				break;
		}
		if (turn%2 == 0) {
			temp = go_to_list(root, player_one.current_block_id);
			if (temp.owner.type == player_two.type && player_one.account >= 0) //Tests if the player_one ended the turn on other player's property. If he can afford, increases player_two.account as the rent. Reduces player_one 's account in case_1 function.
				player_two.account += calculate_rent(temp); 
			if (player_two.turn_to_wait == 0) //If the other player is not in punishment, passes turn to him.
				turn++;
			else //If not, he plays one more turn until other player's punishment is over. Reduces the puniish value as 1 everytime one turn is over.
				player_two.turn_to_wait--;
			if (test_fortune4 == 1) {
				player_two.account += 10000;
			}
		}
		else {
			temp = go_to_list(root, player_one.current_block_id);
			if (temp.owner.type == player_one.type && player_two.account >= 0) //Does the same for player two. (399th line)
				player_one.account += calculate_rent(temp);
			if (player_one.turn_to_wait == 0) //If the other player is not in punishment, passes turn to him.
				turn++;
			else //If not, he plays one more turn until other player's punishment is over. Reduces the puniish value as 1 everytime one turn is over.
				player_one.turn_to_wait--;
			if (test_fortune4 == 1) {
				player_one.account += 10000;
			}
		}

	}while(player_one.account >= 0 && player_two.account >= 0);
	if (player_one.account > 0)
		printf("Congratulations %s. You won!\n",player_one.name);
	else
		printf("Congratulations %s. You won!\n",player_two.name );
}

int menu() {
	int choice;
	printf("\n1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue:\n");
	scanf("%d",&choice);
	return choice;
}

void play(block *root, player *current_player, int choice, int *test_fortune4) { //Executes the choices here.
	switch(choice) {
		case 1: case_1(root, current_player, test_fortune4); break;
		case 2: printf("You have %d$ in your account.\n",current_player->account); break;
		case 3: show_player_properties(root, *current_player); break;
		case 4: show_properties(root); break;
		case 5: go_to_list_f(root, current_player->current_block_id, current_player, buy_property); break;
		case 6: go_to_list_f(root, current_player->current_block_id, current_player, buy_house);	break;
		case 7: sell_property(root, current_player);	break;
	}
}

void show_player_properties(block *root, player current_player) { //Case 3 in play() function.
	int i, owned;
	block temp;
	owned = count_owned_properties(root, &current_player);
	if (owned == 0)
		printf("You dont have a property\n");
	for (i = 0; i < owned; i++) {
		temp = go_to_list(root, current_player.owned_block_ids[i]);
		printf(" %d - %s\n",i, temp.name);
	}
}

void case_1(block *root, player *current_player, int *test_fortune4) { //First, rolls the dice. Then checks which type of block he came in to, then does what needed on the block.
	block temp, *iter;
	int dice, rent_value, owned_count;
	char choice;
	dice = rand()%6 + 1;
	printf("Rolling a dice: %d\n",dice);
	current_player->current_block_id += dice;
	if (current_player->current_block_id > 23) { //Means player passed or on the start block. Increases player's account 10000$ and mods the current_block_id value.
		current_player->current_block_id = current_player->current_block_id%24;
		current_player->account += 10000;
	}
	temp = go_to_list(root, current_player->current_block_id);
	printf("Now on %s block.\n",temp.name ); // I didnt want to show the board so often, so i just wrote where he came after rolling a dice.
	owned_count = count_owned_properties(root, current_player); //For survive_test function.
	rent_value = calculate_rent(temp); //I assigned the rent_value there, bacause it works on all the payments and i wanted to print if player has to pay something.
	if (temp.type == fortune) {
		iter = root;
		*test_fortune4 = Fortune(iter, current_player);
		if (*test_fortune4 == 4) 
			*test_fortune4 = 1;
		else
			*test_fortune4 = 0;
	}
	temp = go_to_list(root, current_player->current_block_id);
	if (temp.type == punish) {
		printf("You are on a punish block. You have to rest %d turns.\n", rent_value);
		current_player->turn_to_wait = rent_value;
	}
	if(temp.type == tax) {
		printf("You are on a tax block. You have to pay the tax fee.\n\tPayment: %d$\n",rent_value);
		current_player->account -= rent_value; //Doesnt matter if player has enough money to pay, i reduced it. Because it checks if he can survive after that and if he can account increases as he sells the properties. So it goes to same place.
		if (current_player->account < 0) {
			if (current_player->account + survive_test(root ,*current_player, owned_count) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
				printf("You are bankrupt! Game is over.\n");
			else {
				do {
					printf("You can not pay this, you have to sell some of your properties!\n");
					sell_property(root, current_player);
				}while(current_player->account < 0); //Doesnt end until he can pay the rent;
			}
		}
	}
	if (temp.type == property) {
		if (temp.owner.type == current_player->type) { //If player comes to his own property, asks him if he wants to build a house.
			printf("Welcome to your property. Do you want to build house?(Y/N): ");
			scanf(" %c",&choice);
			if (choice == 'Y' || choice == 'y')
				go_to_list_f(root, current_player->current_block_id, current_player, buy_house);
		}
		else if (temp.owner.type != noone) { //If player comes to other player's property, pays the rent.
			printf("You came to other player's property. You have to pay to rent.\n\tPayment: %d$\n", rent_value);
			current_player->account -= rent_value; //Doesnt matter if player has enough money to pay, i reduced it. Because it checks if he can survive after that and if he can account increases as he sells the properties. So it goes to same place.
			if (current_player->account <= 0) {
				if (current_player->account + survive_test(root ,*current_player, owned_count) <= 0) //If player has not enough money to pay the tax fee, checks if he can pay after selling some of his property.
					printf("You are bankrupt! Game is over.\n");
				else {
					do {
						printf("You can not pay this, you have to sell some of your properties!\n");
						sell_property(root, current_player);
					}while(current_player->account < 0); //Doesnt end until he can pay the rent;
				}
			}

		}
		else { //If player comes to unowned property, asks him if he wants to buy it. If he buys, asks him if he wants to buy a house.
			printf("Dou you want to buy this property?(Y/N): ");
			scanf(" %c",&choice);
			if (choice == 'Y' || choice == 'y')
				go_to_list_f(root, current_player->current_block_id, current_player, buy_property);
		}
	}

	printf("%s's turn is over.\n",current_player->name );
}

void play_AI(block *root, player *current_player, int *test_fortune4) {
	block temp;
	int i, dice, rent_value, owned_count, index, index_id, flag;
	dice = rand()%6 + 1;
	printf("Computer rolling a dice: %d\n",dice );
	current_player->current_block_id += dice;
	if (current_player->current_block_id > 23) { //Means player passed or on the start block. Increases player's account 10000$ and mods the current_block_id value.
		current_player->current_block_id = current_player->current_block_id % 24;
		current_player->account += 10000;
	}
	temp = go_to_list(root, current_player->current_block_id);
	printf("Cap is now on %s block.\n",temp.name );
	owned_count = count_owned_properties(root, current_player);
	rent_value = calculate_rent(temp); //Rent value returns for every type's prices. For property returns rent, for tax returns tax, for punish block returns how many turns player is going to wait.
	if (temp.type == fortune) {
		*test_fortune4 = Fortune(root, current_player);
		if (*test_fortune4 == 4) 
			*test_fortune4 = 1;
		else
			*test_fortune4 = 0;
	}
	if (temp.type == punish) {
		printf("Cap is on a punish block. He is going to rest for %d turns\n",rent_value);
		current_player->turn_to_wait = rent_value;
	}
	if (temp.type == tax) {
		printf("Cap is on a tax block. Payment: %d$\n",rent_value);
		current_player->account -= rent_value;
		if (current_player->account < 0) {
			if(current_player->account + survive_test(root, *current_player, owned_count) >= rent_value) {
				printf("Cap does not have enough money. He has to sell properties to pay the tax fee.\n");
				index_id = find_highest(root, *current_player, owned_count);
				index = current_player->owned_block_ids[index_id];
				temp = go_to_list(root, index);
				printf("Cap sold %s.\n",temp.name );
				go_to_list_f(root, index, current_player, sell);
				for (i = index_id; i < owned_count; i++) {
					current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
				}
				temp = go_to_list(root, current_player->current_block_id);
			}
			else
				printf("Cap is bankrupt! Game is over.\n");
		}
	}
	if (temp.type == property) {
		if (temp.owner.type == current_player->type) {
			if (owned_count >= 4) 
				buy_house_AI(root, current_player);
			else
				printf("Cap doesnt have 1/3 of all properties, so he is not building a house.\n");
		}
		else if(temp.owner.type != noone) {
			printf("Cap came to other player's property. Payment: %d$\n",rent_value);
			current_player->account -= rent_value;
			if (current_player->account < 0) {
				if(current_player->account + survive_test(root, *current_player, owned_count) >= rent_value) {
					printf("Cap does not have enough money. He has to sell properties to pay the tax fee.\n");
					do {
						index_id = find_highest(root, *current_player, owned_count);
						index = current_player->owned_block_ids[index_id];
						temp = go_to_list(root, index);
						printf("Cap sold %s.\n",temp.name );
						go_to_list_f(root, index, current_player, sell);
						for (i = index_id; i < owned_count; i++) {
							current_player->owned_block_ids[i] = current_player->owned_block_ids[i + 1];
						}
					}while(current_player->account < 0);
				}
				else
					printf("Cap is bankrupt! Game is over.\n");
			}
		}
		else {
			if (current_player->account >= temp.price) {
				buy_property_AI(root, current_player);
			}
		}
	}
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

int count_owned_properties(block *root, player *current_player) { //In buy_property() function i didnt fill the owned_block_ids array of the player. There i assign the owned blocks to that array and return how many property does he have. 
	int i, counter = 0;
	block temp;
	for (i = 0; i < 19; i++) {
		temp = go_to_list(root, i);
		if (temp.owner.type == current_player->type) {
			current_player->owned_block_ids[counter] = i;
			counter++;
		}
	}
	return counter;
}

int survive_test(block *root, player current_player, int owned_count) { //If player cant pay a rent or tax, it tests if he can pay them after selling all his properties. If not, game is over he is bankrupt.
	int i, value = 0;
	block temp;
	for (i = 0; i < owned_count; i++) {
		temp = go_to_list(root, current_player.owned_block_ids[i]);
		value += (temp.price + temp.house_price * temp.house_count) / 2;
	}
	return value;
}

int find_highest(block *root, player current_player, int owned_count) {
	int i, value, max = 0, index;
	block temp;
	for (i = 0; i < owned_count; i++) {
		temp = go_to_list(root, current_player.owned_block_ids[i]);
		value = (temp.price + temp.house_price * temp.house_count) / 2;
		if (value > max) {
			max = value;
			index = i;
		}
	}
	return index;
}

double average_properties(block *root) {
	block temp;
	int i, counter = 0;
	double average;
	for (i = 0; i < 24; i++) {
		temp = go_to_list(root, i);
		if (temp.type == property) {
			counter++;
			average += temp.price;
		}
	}
	return average / counter;
}

block go_to_list(block *root, int number) { //This function helps me go to the list. You cannot change list's datas with use of this function, you just can reach them.
	int i;
	block *temp = root;
	for (i = 0; i < number; i++) {
		temp = temp->next;
	}
	return *temp;
}

block go_to_list_f(block *root, int number, player *current_player, void f(block *current_block, player *current_player)) { //I used that function for buy property, house and sell functions. This function helps me for going to list and change it.
	int i;
	block *temp = root;
	for (i = 0; i < number; i++) {
		temp = temp->next;
	}
	f(temp, current_player);
	return *temp;
}






	
	





