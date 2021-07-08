#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

int random_number_generator(int lower_limit, int upper_limit) { //Generates random letters for the puzzle
	return rand() % (upper_limit - lower_limit + 1) + lower_limit;
}

void fill_the_puzzle_random(char area[][DICT_SIZE]) { //Fills the puzzle with random letters.
	int y, x;
	for (y = 0; y < DICT_SIZE; ++y) {
		for (x = 0; x < DICT_SIZE; ++x) {
			area[y][x] = random_number_generator(97, 122);
		}
	}
}

void fill_the_puzzle_words(char area[][DICT_SIZE], char *dict[DICT_SIZE], int coord[][4]) { //Fills the puzzle with the words in dict array with coordinates.
	int y, x, counter_y, counter_x, counter_dict;
	for (y = 0; y < DICT_SIZE; ++y) {
		for (x = 0; x < 2; x++) {
			counter_y = 0;
			counter_x = 0;
			counter_dict = 0;
			if ((coord[y][0] + counter_y != coord[y][2]) && (coord[y][1] + counter_x!= coord[y][3])) { //It first checks if the word is going diagonal by the difference in coordinates. If not checks horizontal and vertical lines. I hold a counter for dont ruin the coord and dict arrays. It stops when the difference is 0. Everytime a assigned a letter to area from dict array, i increased the counter by 1. It checks if it is done by summarize or substracts the counter with the first value and if it is equal to finish coordinate of the word.
				while ((coord[y][0] + counter_y != coord[y][2]) && (coord[y][1] + counter_x != coord[y][3])) {
					area[coord[y][x] + counter_y][coord[y][x + 1] + counter_x] = dict[y][x + counter_dict];
					counter_dict++;

					if (coord[y][2] > coord[y][0])
						counter_y++;
					else
						counter_y--;
					if (coord[y][3] > coord[y][1])
						counter_x++;
					else
						counter_x--;

					if (coord[y][x] + counter_y == coord[y][x + 2] && coord[y][x + 1] + counter_x == coord[y][x + 3]) {
						area[coord[y][x] + counter_y][coord[y][x + 1] + counter_x] = dict[y][x + counter_dict];
						x = 2; // To stop the lower for loop and increase y.
						break;
					}
				}
			}
			else if ((coord[y][x] + counter_y != coord[y][x + 2]) && x == 0) { //Checks if the word is horizontal by the difference in coordinates. I hold a counter for dont ruin the coord and dict arrays.
				while ((coord[y][x] + counter_y != coord[y][x + 2]) && x == 0) {
					area[coord[y][x] + counter_y][coord[y][x + 1]] = dict[y][x + counter_dict];
					counter_dict++;

					if (coord[y][x + 2] > coord[y][x])
						counter_y++;
					else
						counter_y--;

					if (coord[y][x] + counter_y == coord[y][x + 2]) {
						area[coord[y][x] + counter_y][coord[y][x + 1]] = dict[y][x + counter_dict];
						break;
					}
				}
			}
			else if ((coord[y][x] + counter_x != coord[y][x + 2]) && x == 1) { //Checks if the word is vertical by the difference in coordinates. 
				while (coord[y][x] + counter_x != coord[y][x + 2] && x == 1) {
					area[coord[y][x - 1]][coord[y][x] + counter_x] = dict[y][(x - 1) + counter_dict];
					counter_dict++;

					if (coord[y][x + 2] > coord[y][x])
						counter_x++;
					else
						counter_x--;

					if (coord[y][x] + counter_x == coord[y][x + 2]) {
						area[coord[y][x - 1]][coord[y][x] + counter_x] = dict[y][(x - 1) + counter_dict];
						break;
					}
				}
			}
			
		}
	}
}
void print_puzzle(char area[][DICT_SIZE]) { //Prints the puzzle
	int i, y, x;
	printf("  ");
	printf("\t\t");
	for (i = 0; i < (DICT_SIZE * 2) + 3; ++i) {
		printf("-");
	}
	printf("\n");
	for (y = 0; y < DICT_SIZE; ++y) {
		printf("\t\t");
		for (x = 0; x < DICT_SIZE; ++x) {
			if (x == 0)
				printf("|");
			printf(" %c",area[y][x]);
			if (x == DICT_SIZE - 1)
				printf(" |\n");
		}
	}
	printf("\t\t");
	for (i = 0; i < (DICT_SIZE * 2) + 3; ++i) {
		printf("-");
	}
	printf("\n");
}

void reverse_string(char str1[], char str2[]) { // If user enters the finish coordinate of the word, i reversed the word and checked.
	int i;
	for (i = 0; i < get_line_size(str2); ++i) {
		str1[i] = str2[get_line_size(str2) - i - 1];
	}
	str1[i] = '\0';
}

int compare_string(char str1[], char str2[]) { //Used it for checks
	int j, counter;
		counter = 0;
		for (j = 0; j < DICT_SIZE; ++j) {
			if (str1[j] == str2[j]) 
				counter++;
			if (counter == get_line_size(str1))
				return 1;
			if (str1[j] != str2[j]) 
				break;
		}
	return -1;
}

int compare_dict(char str1[], char *dict[DICT_SIZE]) { //To test the word that user typed is in dictionary. 
	int i,j,counter;
	for (i = 0; i < DICT_SIZE; ++i) {
		for (j = 0; j < DICT_SIZE; ++j) {
			if ((str1[j] == dict[i][j]) && dict[i][j + 1] == 13) {
				return 1;
			}
			if (str1[j] != dict[i][j]) {
				break;
			}
		}
	}
	return 0;
}

int check_east(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays east of the given coordinate, then tests the word user typed in that east array. If so makes the word uppercase and and returns 1.
	int x, check = 0; int counter = 0;
	char east[DICT_SIZE] = "               ";
	for (x = 0; x < DICT_SIZE; ++x) {
		east[x] = area[coord_y][coord_x + x];
		if (east[x] >= 'A' && east[x] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				east[x] += 32;
		}
		if (coord_x + x == DICT_SIZE - 1)
			break;
	}
	if (compare_string(guess, east) == 1) {
		printf("east\n");
		for (x = 0; x < get_line_size(guess); ++x) {
			if (area[coord_y][coord_x + x] > 'Z')
			area[coord_y][coord_x + x] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_west(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays west of the given coordinate, then tests the word user typed in that west array. If so makes the word uppercase and and returns 1.
	int x, check = 0; int counter = 0;
	char west[DICT_SIZE] = "               ";
	for (x = 0; x < DICT_SIZE; ++x) {
		west[x] = area[coord_y][coord_x - x];
		if (west[x] >= 'A' && west[x] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				west[x] += 32;
		}
		if (coord_x - x == 0)
			break;
	}
	if (compare_string(guess, west) == 1) {
		printf("west\n");
		for (x = 0; x < get_line_size(guess); ++x) {
			if (area[coord_y][coord_x - x] > 'Z')
				area[coord_y][coord_x - x] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_north(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays north of the given coordinate, then tests the word user typed in that north array. If so makes the word uppercase and and returns 1.
	int y, check = 0; int counter = 0;
	char north[DICT_SIZE] = "               ";
	for (y = 0; y < DICT_SIZE; ++y) {
		north[y] = area[coord_y - y][coord_x];
		if (north[y] >= 'A' && north[y] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				north[y] += 32;
		}
		if (coord_y - y == 0)
			break;
	}
	if (compare_string(guess, north) == 1) {
		printf("north\n");
		for (y = 0; y < get_line_size(guess); ++y) {
			if (area[coord_y - y][coord_x] > 'Z')
				area[coord_y - y][coord_x] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_south(char area[][DICT_SIZE], char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays south of the given coordinate, then tests the word user typed in that south array. If so makes the word uppercase and and returns 1.
	int y, check = 0; int counter = 0;
	char south[DICT_SIZE] = "               ";
	for (y = 0; y < DICT_SIZE; ++y) {
		south[y] = area[coord_y + y][coord_x];
		if (south[y] >= 'A' && south[y] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				south[y] += 32;
		}
		if (coord_y + y == DICT_SIZE - 1)
			break;
	}
	if (compare_string(guess, south) == 1) {
		printf("south\n");
		for (y = 0; y < get_line_size(guess); ++y) {
			if (area[coord_y + y][coord_x] > 'Z')
				area[coord_y + y][coord_x] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_northeast(char area[][DICT_SIZE], char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays northeast of the given coordinate, then tests the word user typed in that northeast array. If so makes the word uppercase and and returns 1.
	int c, check = 0; int counter = 0;
	char northeast[15] = "               "; // I had to fill that string with something, beacuse it can randomly use the same place in ram with other arrays. 
	for (c = 0; c < DICT_SIZE; ++c) {
		northeast[c] = area[coord_y - c][coord_x + c];
		if (northeast[c] >= 'A' && northeast[c] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				northeast[c] += 32;
		}
		if (coord_y - c == 0 || coord_x + c == DICT_SIZE - 1) {
			break;
		}
	}
	if (compare_string(guess, northeast) == 1) {
		printf("northeast\n");
		for (c = 0; c < get_line_size(guess); c++) {
			if (area[coord_y - c][coord_x + c] > 'Z')
				area[coord_y - c][coord_x + c] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_southeast(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays southeast of the given coordinate, then tests the word user typed in that southeast array. If so makes the word uppercase and and returns 1.
	int c, check = 0; int counter = 0;
	char southeast[DICT_SIZE] = "               ";
	for (c = 0; c < DICT_SIZE; ++c) {
		southeast[c] = area[coord_y + c][coord_x + c];
		if (southeast[c] >= 'A' && southeast[c] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				southeast[c] += 32;
		}
		if (coord_y + c == DICT_SIZE - 1 || coord_x + c == DICT_SIZE - 1)
			break;
	}
	if (compare_string(guess, southeast) == 1) {
		printf("southeast\n");
		for (c = 0; c < get_line_size(guess); c++) {
			if (area[coord_y + c][coord_x + c] > 'Z')
				area[coord_y + c][coord_x + c] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_northwest(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays northwest of the given coordinate, then tests the word user typed in that northwest array. If so makes the word uppercase and and returns 1.
	int c, check = 0; int counter = 0;
	char northwest[DICT_SIZE] = "               ";
	for (c = 0; c < DICT_SIZE; ++c) {
		northwest[c] = area[coord_y - c][coord_x - c];
		if (northwest[c] >= 'A' && northwest[c] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				northwest[c] += 32;
		}
		if (coord_y - c == 0 || coord_x - c == 0)
			break;
	}
	if (compare_string(guess, northwest) == 1) {
		printf("northwest\n");
		for (c = 0; c < get_line_size(guess); c++) {
			if (area[coord_y - c][coord_x - c] > 'Z')
				area[coord_y - c][coord_x - c] -= 32; 
		}
		check = 1;
	}
	return check;
}

int check_southwest(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x) { //Takes all the letters in the puzzle map which stays southwest of the given coordinate, then tests the word user typed in that southwest array. If so makes the word uppercase and and returns 1.
	int c, check = 0; int counter = 0;
	char southwest[DICT_SIZE] = "               ";
	for (c = 0; c < DICT_SIZE; ++c) {
		southwest[c] = area[coord_y + c][coord_x - c];
		if (southwest[c] >= 'A' && southwest[c] <= 'Z') {
			counter++;
			if (counter < get_line_size(guess))
				southwest[c] += 32;
		}
		if (coord_y + c == DICT_SIZE - 1 || coord_x - c == 0)
			break;
	}
	if (compare_string(guess, southwest) == 1) {
		printf("southwest\n");
		for (c = 0; c < get_line_size(guess); c++) {
			if (area[coord_y + c][coord_x - c] > 'Z')
				area[coord_y + c][coord_x - c] -= 32; 
		}
		check = 1;
	}
	return check;
}

void check_directions(char area[][DICT_SIZE],char guess[], int coord_y, int coord_x, int *words_found) { //Checks all the directions and if one of them finds a word, and increases words_found by 1.
	*words_found += check_east(area, guess, coord_y, coord_x);
	*words_found += check_west(area, guess, coord_y, coord_x);
	*words_found += check_north(area, guess, coord_y, coord_x);
	*words_found += check_south(area, guess, coord_y, coord_x);
	*words_found += check_northeast(area, guess, coord_y, coord_x);
	*words_found += check_northwest(area, guess, coord_y, coord_x);
	*words_found += check_southeast(area, guess, coord_y, coord_x);
	*words_found += check_southwest(area, guess, coord_y, coord_x);
}

void game(char area[][DICT_SIZE], char *dict[DICT_SIZE]) {
	char guess[10], guess_reverse[10];
	char test, test2[10], test_exit1[5] = "exit"; char test_exit2[5] = "game";
	int coord_y, coord_x, words_found = 0;
	while (words_found < DICT_SIZE) {
		printf("Do you see any word?: ");
		scanf("%s",guess);
		scanf("%c",&test); //If user enters space it gets another string to test if user types "exit game". If user types a word and press enter, it doesnt ask for another string.
		if (test == ' ')
			scanf("%s",test2);
		if (compare_string(guess, test_exit1) == 1 && compare_string(test2, test_exit2) == 1) //If user typed "exit game" stops the game.
			break;
		reverse_string(guess_reverse, guess); //Reverses for if user typed the finish coordinate of the word.
		printf("Please enter the y coordinate(row): ");
		scanf("%d",&coord_y);
		printf("Please enter the x coordinate(column): ");
		scanf("%d",&coord_x);
		if (compare_dict(guess, dict) == 1) { //First checks the word user typed is in dictionary, then looks to all 8 directions to see if there is that word.
			check_directions(area, guess, coord_y, coord_x, &words_found);
			check_directions(area, guess_reverse, coord_y, coord_x, &words_found);
		}

		print_puzzle(area); //Prints the puzzle after every try.
	}
	if (words_found == 15)
		printf("Congratulations!! You found all the hidden words.\n");
}

int main(){
	srand(time(NULL));
	char puzzle[15][15];
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat.txt", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	//print_dictionary(dict);
	//print_coord(coord);
	
	// WRITE HERE...
	fill_the_puzzle_random(puzzle);
	fill_the_puzzle_words(puzzle, dict, coord);
	print_puzzle(puzzle);
	game(puzzle, dict);
	return 0;
}





