#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby}pokemon;
typedef enum{Linear, Quadratic}attack_type;
void pokedex(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[]);
void oaks_labaratory(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons);
void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]);
void menu();
int strlength(char str[][11], int number);
int strcompare(char str1[][11], char str2[]);
void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[], int pokemon_count);
void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons);
void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons);
void locate_your_pokemons(char Pokemon_name[][11], pokemon user_Pokemons[], int area[][8], int stamina[], int pokemon_staminas_view[][8], int team[][8]);
void show_area(char Pokemon_name[][11], int area[][8], int pokemon_staminas_view[][8]);
void show_area_location();
int random_number_generator(int lower_limit, int upper_limit);
void locate_AI_pokemons(int AI_pokemons[], int area[][8], int stamina[], int pokemon_staminas_view[][8], int team[][8]);
int move_user(char Pokemon_name[][11], int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[]);
int move_AI(char Pokemon_name[][11], int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[]);
char random_direction_AI();
void attack(int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[], int pos_y, int pos_x, int allie);

int main() {
	srand(time(NULL));
	menu();
	
}

//////////////////////////////// PART 5 //////////////////////////////////////

void menu() {
	pokemon user_Pokemons[5];
	user_Pokemons[4] = 9; //In Oaks's labaratory it helps to print user's pocket. In show_Pokemons() if Pokemons[4] = 9 it prints the pocket. Sent user_Pokemons as show_Pokemons()'s parameter Pokemons in the options 3 and 4(When it has to print the pocket)
	pokemon Pokemons[10];
	Pokemons[4] = 10; //As parameter of show_Pokemons when it has to print all pokemons sent Pokemons as a parameter. If it has to print the pocket, sent user_Pokemons as a Pokemons parameter. It tests what to print as if (Pokemons[4] = 9) so i assigned 10 to Pokemons[4] to not make a confusion.(Pokemons[4] can be randomly 4 if i dont assign anything to it)
	Pokemons[0] = 0; //Used first index of Pokemons as an counter in oaks_labaratory().
	int choice;
	char Pokemon_name[10][11] = {"Charmander", "Pikachu", "Squirtle", "Bulbasaur", "Pidgeotto", "Ratata", "Mug", "Caterpie", "Zubat", "Krabby"};
	int range[] = {1,3,4,3,2,2,1,2,3,2};
	int attack_power[] = {500,350,300,400,250,250,350,200,350,300};
	int stamina[] = {2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
	attack_type type[] = {0,0,0,0,1,0,1,1,0,0};
	do {
		printf("Please select an choice to continue:\n\n1)  Open Pokedex\n2)  Go to Oak's Labaratory\n3)  Enter the tournament");
		scanf("%d",&choice);
		switch(choice) {
			case 1: pokedex(Pokemon_name, range, type, attack_power, stamina); break;
			case 2: oaks_labaratory(Pokemon_name, Pokemons, user_Pokemons); break;
			case 3: if (Pokemons[0] == 4) battle(Pokemon_name, range, type, attack_power, stamina, user_Pokemons); else printf("You don't have amount number of pokemon to enter the tournament! You can go to Oak's Labaratory for catch some.\n");
			 break;
			default : printf("This is an invalid choice. Try again...\n");
		}
	}while(choice != 3 || Pokemons[0] != 4);
}

//////////////////////////////// PART 1 //////////////////////////////////////

void pokedex(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[]) {
	char name[15];
	int i, j, typet; //i defined typet for print the specifications of pokemon. All pokemons have the same index of all specification arrays. (Charmander's index is 0 in all the arrays.)
	do {
		printf("Please type name of the pokemon(type exit to close pokedex): ");
		scanf("%s",name);
		typet = strcompare(Pokemon_name, name); // 
		if (typet > -1) { // typet = -3 if user types exit, and typet = -2 if user doesnt type "exit" or a pokemon name. So if typet is bigger than -1 it means user typed a Pokemon name. So there it prints the specifications. 
			printf("Name: %s\n",Pokemon_name[typet] );
			if (type[typet] == Linear)
				printf("A. Type: Linear\n");
			if (type[typet] == Quadratic)
				printf("A. Type : Quadratic\n");
			printf("Range: %d block\n",range[typet] );
			printf("A. Power: %d\n",attack_power[typet]);
			printf("Stamina: %d\n",stamina[typet]);
		}
		if (typet == -2)
			printf("That is not a pokemon name! Type exit if you want to quit.\n");
	}while(typet != -3); //Loop doesnt stop until user types exit. Strcompare returns -3 only if user types "exit".
}

int strcompare(char str1[][11], char str2[]) { //This function compares the strings to test if they are the same.
	int i, j, counter;
	if (str2[0] >= 'a' && str2[0] <= 'z') //Accepts if the entry doesnt start with capital letter. So makes it capital there for the check.
		str2[0] -= 32;
	for (i = 0; i < 10; ++i) {
		counter = 0; //It has to start as zero every line. 
		for (j = 0; j < 10; ++j) {
			if (str1[i][j] == str2[j] && str1[i][j] != '\0') //Increases counter if characters are the same. 
				counter++;
			else
				break;
		}
		if (counter == strlength(str1, i) && str2[counter] == '\0') { //Tests if counter is equal to length of that Pokemons name. If both characters and the length is equal it returns the index of that pokemon to typet.
			return i;
		}
	}
	if ((str2[0] == 'e' || str2[0] == 'E') && str2[1] == 'x' && str2[2] == 'i' && str2[3] == 't' && str2[4] == '\0') //exit.
		return -3;

	return -2;
}

int strlength(char str[][11], int number) { //This function returns number of characters in a character array. Used in strcompare function.
	int i=0;
	while (str[number][i] != '\0') { //Goes until end of string.
		i++;
		if (i > 9)
			break;
	}
	return i;
}

////////////////////////////////////// PART 2 /////////////////////////////////////////////////////////

void oaks_labaratory(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons) {
	int choice, pokemon_count;
	do {
		pokemon_count = Pokemons[0]; //Used first index of Pokemons array as a pokemon_count. catch_a_pokemon and release_a_pokemon functions doesn't have a parameter for counter so i used it for this.
		printf("Welcome to Labaratory of Professor Oak. How can i help you?\n  1) Show Pokemons\n  2) Catch a Pokemon\n  3) Release a Pokemon\n  4) Show my pocket\n  5) Back");
		scanf("%d",&choice);
		switch(choice) {
			case 1: show_Pokemons(Pokemon_name, Pokemons, pokemon_count); break;
			case 2: show_Pokemons(Pokemon_name, Pokemons, pokemon_count); catch_a_pokemon(Pokemon_name, Pokemons, my_Pokemons); break;
			case 3: show_Pokemons(Pokemon_name, my_Pokemons, pokemon_count); release_a_pokemon(Pokemon_name, Pokemons, my_Pokemons); break;
			case 4: show_Pokemons(Pokemon_name, my_Pokemons, pokemon_count); break; //Sent my_Pokemons to show_pokemons function to print the pocket. Assigned a specific number to function to know what to print (Pocket or all).
			case 5: break;
			default: printf("This is an invalid number. Please Try again:\n");
		}
	}while(choice != 5); 
}

void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[], int pokemon_count) {
	int i;
		if (Pokemons[4] == 9) {//Shows user's pocket.
			for (int i = 0; i < pokemon_count; ++i) {
				printf("%d - %s\n" ,i, Pokemon_name[Pokemons[i]] );
			}
			if (pokemon_count == 0)
				printf("There is no pokemon in your pocket. You can choose the option 2 to catch some!\n");
		}
		else
			for (i = 0; i < 10; ++i) { //Shows all pokemons.
				printf("\t%d - %s\n",i,Pokemon_name[i] );
			}
		
}

void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons) {
	int selection, permission = 1;
	if (Pokemons[0] == 4) //Tests how many pokemon user has.
		printf("You cant catch more than 4 pokemons!\n");
	else {
		scanf("%d",&selection);
		for (int i = 0; i < Pokemons[0]; ++i) { // Tests invalid numbers.
			if (selection == my_Pokemons[i]) {
				printf("You already caught that pokemon!!!\n");
				permission = 0;
			}
		}
		if (selection < 0 || selection > 9) {
			printf("Invalid number! Try again later...\n");
			permission = 0;
		}
		if (permission == 1) { //Assigns selected pokemon to user_Pokemons and increases the counter by 1. If entry is valid
			my_Pokemons[Pokemons[0]] = selection;
			Pokemons[0]++; //Counts the pokemons in the pocket.
		}
	}
}

void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons) {
	int selection, permission = 0;
	if (Pokemons[0] == 0) { //Tests how many pokemon user has.
		printf("There is no pokemon in your pocket!\n");
	}
	else {
		scanf("%d",&selection);
		while (permission == 0) {
			if (selection < 0 || selection >= Pokemons[0]) { //Tests invalid numbers.
				printf("Invalid number. Please enter pokemon's ID to release:");
				scanf("%d",&selection);
			}
			else
				permission = 1;
		}
		if (permission == 1) { // It releases a pokemon if the entry is valid. 
			for (int i = selection; i < Pokemons[0]; ++i) { //Shifts the pokemons after releasing one.
				my_Pokemons[i] = my_Pokemons[i+1];
			}
			Pokemons[0]--; //Reduces the counter by 1 after releasing one
		}
	}
}


////////////////////////////////////// PART 3 /////////////////////////////////////////////////////////

void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]) {
	int y, x;
	int pokemon_staminas_view[8][8], area[8][8], AI_pokemons[4], team[8][8]; // team[][] decides which team's pokemon stands in that area. If team[y][x] == 0 it means there is user's pokemon. If team[y][x] == 1 it means there is AI's pokemon.
	int alive_user, alive_AI;
	for (y = 0; y < 8; ++y) {
		for (x = 0; x < 8; ++x) {
			area[y][x] = -1;
		}
	}
	show_area_location();
	printf("Battle is about the start! Place your pokemons to battle area\n");
	locate_your_pokemons(Pokemon_name, user_Pokemons, area, stamina, pokemon_staminas_view, team);
	locate_AI_pokemons(AI_pokemons, area, stamina, pokemon_staminas_view, team);
	show_area(Pokemon_name, area, pokemon_staminas_view);
	do {
		alive_user = move_user(Pokemon_name, area, team, pokemon_staminas_view, range, attack_power, type);
		show_area(Pokemon_name, area, pokemon_staminas_view);
		alive_AI = move_AI(Pokemon_name, area, team, pokemon_staminas_view, range, attack_power, type);
		show_area(Pokemon_name, area, pokemon_staminas_view);
	} while(alive_user != 0 && alive_AI != 0);

	if (alive_user != 0)
		printf("Congratulations. You won the battle\n");
	else
		printf("You lose\n");

} 

void show_area(char Pokemon_name[][11], int area[][8], int pokemon_staminas_view[][8]) {
	int x,y,i;
	for (y = 0; y < 8; ++y) {
		for (int i = 0; i < 57; ++i) {
			printf("-");
		}
		printf("\n");
		for (x = 0; x < 8; ++x) {
			if (area[y][x] >= 0)
				printf("|  %c%c  ",Pokemon_name[area[y][x]][0],Pokemon_name[area[y][x]][1]);
			else
				printf("|      ");
		}
		printf("|\n");
		for (x = 0; x < 8; ++x) {
			if (area[y][x] >= 0) {
				if (pokemon_staminas_view[y][x] >= 1000)
				printf("|(%d)", pokemon_staminas_view[y][x]);
				else if (pokemon_staminas_view[y][x] >= 100)
					printf("|(%d) ", pokemon_staminas_view[y][x]);
				else
					printf("|(%d)  ", pokemon_staminas_view[y][x]);
			}
			else
				printf("|      ");
		}
		printf("|\n");
	}
	for (int i = 0; i < 57; ++i) {
			printf("-");
		}
	printf("\n");
}

void show_area_location() {
	int i,x,y;
	for (y = 0; y < 8; ++y) {
		for (int i = 0; i < 41; ++i) {
			printf("-");
		}
		printf("\n");
		for (x = 0; x < 9; ++x) {
			if (x < 8) {
				if(x + y*8 > 9)
					printf("| %d ",x + (y*8));
				else
					printf("| %d  ",x + (y*8));
			}
			else
				printf("|    ");
		}
		printf("\n");
		for (x = 0; x < 9; ++x) {
			printf("|    ");
		}
		printf("\n");
	}
	for (int i = 0; i < 41; ++i) {
			printf("-");
	}
	printf("\n");
	printf("Those are location of this area. You are gonna see this once. You can place your pokemons to the locations 0 to 15.\n");
}

void locate_your_pokemons(char Pokemon_name[][11], pokemon user_Pokemons[], int area[][8], int stamina[], int pokemon_staminas_view[][8], int team[][8]) {
	int selection, location, test[4];
	int i, y, x, j, green_light, mistake = 0;
	for (i = 0; i < 4; ++i) {
		green_light = 0; 
		show_Pokemons(Pokemon_name, user_Pokemons, 4);
		printf("Please select a pokemon: ");
		scanf("%d",&selection);
		while (green_light == 0) { //This loop just prevents the user from selecting invalid numbers and helps to place his/her pokemons. 
			for (j = 0; j < i; ++j) {
				if (selection == test[j]) {
					printf("You already placed that pokemon. Please select a pokemon that didnt placed yet: \n");
					scanf("%d",&selection);
					mistake ++;
					break;
				}
			}
			if (selection < 0 || selection > 3) {
				printf("This is an invalid choice. Please select one of your pokemons to place: ");
				scanf("%d",&selection);
				mistake++;
			}
			if (mistake == 0)
				green_light = 1;
			mistake = 0;
		}
		test[i] = selection;
		green_light = 0;
		printf("Please select its location: ");
		scanf("%d",&location);
		while (green_light == 0) { //Tests the entries. If the entry is invalid asks again until user enters valid entry.
			y = location / 8;
			x = location % 8;
			if(location < 0 || location > 15) {
				printf("Invalid number. Please select a location between 0 - 15(included): ");
				scanf("%d",&location);
			}
			else if (area[y][x] >= 0) {
				printf("This location is not empty. Please select another location: ");
				scanf("%d",&location);
			}
			else
				green_light = 1;
		}
		area[y][x] = user_Pokemons[selection];
		team[y][x] = 0;
		pokemon_staminas_view[y][x] = stamina[area[y][x]];
		show_area(Pokemon_name, area, pokemon_staminas_view);
	}
}

void locate_AI_pokemons(int AI_pokemons[], int area[][8], int stamina[], int pokemon_staminas_view[][8], int team[][8]) {
	int i, j, y, x, temp, test, mistake = 0;
	for (i = 0; i < 4; ++i) {
		test = 0; 
		temp = random_number_generator(0, 9);
		while (test == 0) { //Tests the numbers. If the number is invalid assigns another random number until the number is valid.
			for (j = 0; j < i; ++j) {
				if (temp == AI_pokemons[j]) {
					temp = random_number_generator(0, 9);
					mistake++;
					break;
				}
			}
			if (mistake == 0)
				test = 1;
			mistake = 0;
		}
		AI_pokemons[i] = temp;
	}

	for (i = 0; i < 4; ++i) {
		temp = random_number_generator(48, 63);
		while (test == 0) { //Tests the numbers. If the number is invalid assigns another random number until the number is valid
			if (area[temp / 8][temp % 8] > 0)
				temp = random_number_generator(48, 63);
			else
				test = 1;
		}
		y = temp / 8;
		x = temp % 8;
		area[y][x] = AI_pokemons[i];
		team[y][x] = 1;
		test = 0;
		pokemon_staminas_view[y][x] = stamina[area[y][x]];
	}
}



int random_number_generator(int lower_limit, int upper_limit) { //Limits are included.
	return rand() %(upper_limit - lower_limit + 1) + lower_limit;
}

int move_user(char Pokemon_name[][11], int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[]) {
	int distance, location;
	char direction;
	int y, x, mistake, vacation = 0; int counter = 0;

	for (y = 0; y < 8; ++y) { //Counts alive pokemons of user.
		for (x = 0; x < 8; ++x) {
			if (area[y][x] >= 0 && team[y][x] == 0)
				counter ++;
		}
	}
	if (counter == 0) //Ends the game if there is not alive pokemon.
		return counter;

	printf("Which pokemon dou yo want to move? Enter location: ");
	scanf("%d", &location);
	while (vacation == 0) { //Tests the entries. If the entry is invalid asks again until user enters valid entry. For location.
		y = location / 8;
		x = location % 8;
		if (area[y][x] < 0) {
			printf("No pokemon stands in that location.\nPlease enter one of your pokemon's location:");
			scanf("%d",&location);
		}
		else {
			if (team[y][x] == 1) {
				printf("Please don't try to move your opponent's pokemon!\n Please enter one of your pokemon's location:");
				scanf("%d",&location);
			}
			else 
				vacation = 1;
		}
	}
	printf("%s(%d, %d) is moving...\n",Pokemon_name[area[y][x]], y, x); //Prints (vertical coordinate, horizontal coordinate)
	vacation = 0;
	printf("W: Up A: Left S: Down D: Right\n");
	scanf(" %c",&direction);
	if (direction >= 'a' && direction <= 'z')
		direction -= 32;
	while (vacation == 0) { //Tests the entries. If the entry is invalid asks again until user enters valid entry. For direction
		if ((y == 7 && direction == 'S') || (y == 0 && direction == 'W') || (x == 0 && direction == 'A') || (x == 7 && direction == 'D')) {
			printf("You can't move in that direction. It is out of the battle area!\n(If you don't want to make a move this turn, choose another direction and enter distance as 0)\nPlease enter another direction:");
			scanf(" %c", &direction);
			if (direction >= 'a' && direction <= 'z')
				direction -= 32; 
		}
		else if (direction != 'W' && direction != 'A' && direction != 'S' && direction != 'D') {
			printf("Invalid entry.\n W: Up A: Left S: Down D: Right");
			scanf(" %c",&direction);
			if (direction >= 'a' && direction <= 'z')
				direction -= 32; 
		}
		else
			vacation = 1;
	}
	vacation = 0;
	printf("Please enter a distance: (Max 2 blocks)");
	scanf("%d", &distance);
	while (vacation == 0) { //Tests the entries. If the entry is invalid asks again until user enters valid entry. For distance
		mistake = 0;
		if (distance < 0 || distance > 2) {
			printf("Invalid entry. Please enter a distance (0 - 2): ");
			scanf("%d",&distance);
			mistake++;
		}
		if (distance == 2) {
			if ((y == 1 && direction == 'W') || (y == 6 && direction == 'S') || (x == 1 && direction == 'A') || (x == 6 && direction == 'D')) {
				printf("You can't move there. It is out of the battle area!\nPlease enter another distance:");
				scanf("%d",&distance);
				mistake++;
			}
		}
		if ((area[y - distance][x] != -1 && direction == 'W') || (area[y + distance][x] != -1 && direction == 'S') || (area[y][x - distance] != -1 && direction == 'A') || (area[y][x + distance] != -1 && direction == 'D')) {
			if (distance != 0) {
				printf("Another pokemon stands in the location that you want to move your pokemon to.\nPlease enter another distance:");
				scanf("%d",&distance);
				mistake++;
			}
		}
		if (mistake == 0)
			vacation = 1;
	}
	switch(direction) { //It first moves the pokemon then carries it's stamina and team number. Lastly changes the x or y position and assigns it's old position -1. (-1 means there is no pokemon) 
		case 'W' :  area[y - distance][x] = area[y][x];
				    pokemon_staminas_view[y - distance][x] = pokemon_staminas_view[y][x];
				    team[y - distance][x] = 0;
				    if (distance != 0) //This statement for if the chosen pokemon doesn't go anywhere and stands in the same location in that move dont remove it(Don't think like that is it's old position).
						area[y][x] = -1;
				    y -= distance;	break;
		case 'A' :  area[y][x - distance] = area[y][x];
				    pokemon_staminas_view[y][x - distance] = pokemon_staminas_view[y][x];
				    team[y][x - distance] = 0;
				    if (distance != 0) //This statement for if the chosen pokemon doesn't go anywhere and stands in the same location in that move dont remove it(Don't think like that is it's old position).
			    		area[y][x] = -1;
				    x -= distance;	break;
		case 'S':   area[y + distance][x] = area[y][x];
				    pokemon_staminas_view[y + distance][x] = pokemon_staminas_view[y][x];
				    team[y + distance][x] = 0;
				    if (distance != 0) //This statement for if the chosen pokemon doesn't go anywhere and stands in the same location in that move dont remove it(Don't think like that is it's old position).
						area[y][x] = -1;
				    y += distance;	break;
		case 'D':   area[y][x + distance] = area[y][x];
				    pokemon_staminas_view[y][x + distance] = pokemon_staminas_view[y][x];
				    team[y][x + distance] = 0;
				    if (distance != 0) //This statement for if the chosen pokemon doesn't go anywhere and stands in the same location in that move dont remove it(Don't think like that is it's old position).
						area[y][x] = -1;
				    x += distance;	break;		 
	}
	

	attack(area, team, pokemon_staminas_view, range, attack_power, type , y, x, 0);

	return counter;
}

int move_AI(char Pokemon_name[][11], int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[]) {
	int distance, location;
	char direction;
	int y, x, mistake, vacation = 0; int counter = 0;

	for (y = 0; y < 8; ++y) { //Counts alive pokemons of AI.
		for (x = 0; x < 8; ++x) {
			if (area[y][x] >= 0 && team[y][x] == 1)
				counter++;
		}
	}
	if (counter == 0) //Ends the game if there is not alive pokemon.
		return counter;

	location = random_number_generator(0, 63);
	while (vacation == 0) {  //Tests the location. Assigns another random number until it generates valid number for location
		y = location / 8;
		x = location % 8;
		if (area[y][x] < 0) {
			location = random_number_generator(0, 63);
		}
		else {
			if (team[y][x] == 0) {
				location = random_number_generator(0, 63);
			}
			else 
				vacation = 1;
		}
	}
	printf("%s(%d, %d) is moving...\n",Pokemon_name[area[y][x]], y, x); //Prints(Vertical coordinate, Horizontal coordinate)
	vacation = 0;
	direction = random_direction_AI();
	while (vacation == 0) { //Tests the direction if it is valid. Generates another direction until it generates valid direction. (To not to move out of the area)
		if ((y == 7 && direction == 'S') || (y == 0 && direction == 'W') || (x == 0 && direction == 'A') || (x == 7 && direction == 'D')) {
			direction = random_direction_AI();
		}
		else
			vacation = 1;
	}
	vacation = 0;
	distance = random_number_generator(0, 2);
	while (vacation == 0) { //Tests distance. Assigns another random number until it generates valid number for distance(Tests the coordinate its going to move in the are is empty).
		mistake = 0;
		if (distance == 2) {
			if ((y == 1 && direction == 'W') || (y == 6 && direction == 'S') || (x == 1 && direction == 'A') || (x == 6 && direction == 'D')) {
				distance = random_number_generator(0, 2);
				mistake++;
			}
		}
		if ((area[y - distance][x] != -1 && direction == 'W') || (area[y + distance][x] != -1 && direction == 'S') || (area[y][x - distance] != -1 && direction == 'A') || (area[y][x + distance] != -1 && direction == 'D')) {
			distance = random_number_generator(0, 2);
			if (distance != 0)
				mistake++;
		}
		if (mistake == 0)
			vacation = 1;
	}
	switch(direction) {
			case 'W' : 	area[y - distance][x] = area[y][x];
					    pokemon_staminas_view[y - distance][x] = pokemon_staminas_view[y][x];
					    team[y - distance][x] = 1;
					    if (distance != 0)
							area[y][x] = -1;
						y -= distance;	break;
			case 'A' :  area[y][x - distance] = area[y][x];
					    pokemon_staminas_view[y][x - distance] = pokemon_staminas_view[y][x];
					    team[y][x - distance] = 1;
					    if (distance != 0)
							area[y][x] = -1;
						x -= distance;	break;
			case 'S':   area[y + distance][x] = area[y][x];
					    pokemon_staminas_view[y + distance][x] = pokemon_staminas_view[y][x];
					    team[y + distance][x] = 1;
					    if (distance != 0)
							area[y][x] = -1;
						y += distance;	break;
			case 'D':   area[y][x + distance] = area[y][x];
					    pokemon_staminas_view[y][x + distance] = pokemon_staminas_view[y][x];
					    team[y][x + distance] = 1;
					    if (distance != 0)
							area[y][x] = -1;
						x += distance;	break;		 
		}

	attack(area, team, pokemon_staminas_view, range, attack_power, type , y, x, 1);

	
	return counter;
}

char random_direction_AI() { //Turns integer to character for AI's direction.
	int direction = random_number_generator(0, 3);
	switch(direction) {
		case 0: return 'W';
		case 1: return 'A';
		case 2: return 'S';
		case 3: return 'D';
	}
	return 0; 
}

void attack(int area[][8], int team[][8], int pokemon_staminas_view[][8], int range[], int attack_power[], attack_type type[], int pos_y, int pos_x, int allie) {
	int attack = 0;
	int i;
	//The pokemons which has a linear attack type, they attack the closest target. 
		// So it first checks 1 block range, attacks every target in 1 block(linear) range. Because if there is more than one pokemon has equal distance it attacks all of them
		//and 1 block is the smallest range. If it attacks some pokemon in i(loops counter) block range it increases the attack and it checks before increasing 'i'(loop's integer).
		 // If it attacked something loop stops and doesnt look further distances.
	if (type[area[pos_y][pos_x]] == Linear) {   
		for (i = 1; i <= range[area[pos_y][pos_x]]; ++i) {
			if (area[pos_y + i][pos_x] >= 0 && team[pos_y + i][pos_x] != allie && pos_y + i <= 7) {
				pokemon_staminas_view[pos_y + i][pos_x] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y + i][pos_x] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y + i][pos_x] = -1; 
				}
				attack++;
			}
			if (area[pos_y - i][pos_x] >= 0 && team[pos_y - i][pos_x] != allie && pos_y - i >= 0) {
				pokemon_staminas_view[pos_y - i][pos_x] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y - i][pos_x] <= 0) { 
					area[pos_y - i][pos_x] = -1; 
				}
				attack++;
			}
			if (area[pos_y][pos_x + i] >= 0 && team[pos_y][pos_x + i] != allie && pos_x + i <= 7) {
				pokemon_staminas_view[pos_y][pos_x + i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y][pos_x + i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y][pos_x + i] = -1; 
				}
				attack++;
			}
			if (area[pos_y][pos_x - i] >= 0 && team[pos_y][pos_x - i] != allie && pos_x - i >= 0) {
				pokemon_staminas_view[pos_y][pos_x - i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y][pos_x - i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y][pos_x - i] = -1; 
				}
				attack++;
			}
			if (attack != 0)
				break;
		}
	}
		
	else { // If attack type is quadratic.
		for (i = 1; i <= range[area[pos_y][pos_x]]; ++i) { //Since the pokemons which has quadratic attack type, they attack all the pokemons in range. So the loop goes until it's range and checks everywhere in range.
			if (area[pos_y + i][pos_x] >= 0 && team[pos_y + i][pos_x] != allie && pos_y + i <= 7) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y + i][pos_x] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y + i][pos_x] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y + i][pos_x] = -1;
				}
			}
			if (area[pos_y - i][pos_x] >= 0 && team[pos_y - i][pos_x] != allie && pos_y - i >= 0) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y - i][pos_x] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y - i][pos_x] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y - i][pos_x] = -1;
				}
			}
			if (area[pos_y][pos_x + i] >= 0 && team[pos_y][pos_x + i] != allie && pos_x + i <= 7) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y][pos_x + i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y][pos_x + i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y][pos_x + i] = -1;
				}
			}
			if (area[pos_y][pos_x - i] >= 0 && team[pos_y][pos_x - i] != allie && pos_x - i >= 0) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y][pos_x - i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y][pos_x - i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y][pos_x - i] = -1;
				}
			}
			//////////////////////////////////// DIAGONALS ///////////////////////////////////////
			if (area[pos_y + i][pos_x + i] >= 0 && team[pos_y + i][pos_x + i] != allie && pos_y + i <= 7 && pos_x + i <= 7) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y + i][pos_x + i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y + i][pos_x + i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y + i][pos_x + i] = -1;
				}
			}
			if (area[pos_y + i][pos_x - i] >= 0 && team[pos_y + i][pos_x - i] != allie && pos_y + i <= 7 && pos_x - i >= 0) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y + i][pos_x - i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y + i][pos_x - i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y + i][pos_x - i] = -1;
				}
			}
			if (area[pos_y - i][pos_x + i] >= 0 && team[pos_y - i][pos_x + i] != allie && pos_y - i >= 0 && pos_x + i <= 7 ) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y - i][pos_x + i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y - i][pos_x + i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y - i][pos_x + i] = -1;
				}
			}
			if (area[pos_y - i][pos_x - i] >= 0 && team[pos_y - i][pos_x - i] != allie && pos_y - i >= 0 && pos_x - i >= 0) { //Checks if there is a pokemon and if it is, checks the pokemon if it is opponent's for attack.
				pokemon_staminas_view[pos_y - i][pos_x - i] -= attack_power[area[pos_y][pos_x]]; //Reduces attacked pokemon's stamina.
				if (pokemon_staminas_view[pos_y - i][pos_x - i] <= 0) { //Removes the pokemon from area if it is dead.
					area[pos_y - i][pos_x - i] = -1;
				}
			}
		}
	}
}














