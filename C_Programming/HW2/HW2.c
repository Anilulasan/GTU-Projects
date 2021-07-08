#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void menu();
void show_scores(int score_human, int score_program);
void LuckyNumberGame(int *, int *); //make_a_guess is inside this function.
void hourglass(); //draw_hourglass is inside this function.
void mountain_road(); //draw_mountain_road is inside this function.

int main() {
	srand(time(NULL));
	menu();
}

void menu() {
	int choice;
	int score_human = 0; int score_program = 0;
	do {
		printf("***** MENU *****\n 1. Play Lucky Number \n 2. Draw Hourglass \n 3. Draw Mountain Road \n 4. Exit \n Choice:");
		scanf("%d",&choice);
		switch(choice) {
			case 1: LuckyNumberGame(&score_human, &score_program); show_scores(score_human, score_program); break;
			case 2: hourglass(); break;
			case 3: mountain_road(); break;
			case 4: break;
			default: printf("This is an invalid number. Try again!\n");
		}
	}while (choice != 4);
}

int make_a_guess(int trial, int min, int max) {
	int guess;
	printf("(Trial: %d) Make a guess between %d and %d: ",trial,min,max );
	scanf("%d",&guess);
	return guess;
}

void LuckyNumberGame(int *score_human, int *score_program) {
	int LN, GN, distance, difference;
	int trial = 10; int min = 1; int max = 1024; //You can change the values here if you want.
	LN = rand()%1024 + 1;
	printf("---%d---\n",LN );
	for (int i = 1; i <= trial; ++i) { //Main loop of the game. 
		GN = make_a_guess(i,min,max);
		difference = abs(LN - GN);
		if (GN < min || GN > max) { //Warning. I decreased the 'i' here for not to decrease the trial because of invalid number.
			printf("This number is not in interval. Please try again.\n");
			i--;
		}
		else if (GN > LN) //For the limits
			max = GN;
		else //For the limits
			min = GN;
		for (int k = 0; k < 9; ++k) { //The loop finds the distance from exponents of 2. 
			if (difference >= pow(2,k))
				distance = k+1;
			else if(difference == 0)
				distance = 0;
		}
		printf("Distance: %d\n",distance );
		if (LN == GN) {
			printf("You win\n");
			break;
		}
	}
	if (distance == 0)
		*score_human += 1;
	else
		*score_program += 1;
}

void show_scores(int score_human, int score_program) { //Prints the scores.
	printf("Your score: %d Program Score: %d\n",score_human, score_program );
}

void draw_hourglass(int height) {
	int t = height/2;
	for (int i = 0; i < height; ++i) {
		if (i <= t)  //SPACES UNTİL THE MIDDLE LINE(Number of spaces are increasing until the middle line)
			for (int j = 0; j < i; ++j) {
				printf(" ");
			}
		else //SPACES AFTER THE MIDDLE LINE(Number of spaces are decreasing after the middle line)
			for (int j = height; j > i+1; --j) {
				printf(" ");
			}
		printf("*"); //There is a star because my algorithm goes like 1 + 2n. 2n is in the loops and thats the 1.
		for (int j = t; j > i; --j) { //Prints stars until the middle line.
			printf("**");
		}
		if(i > t)
			for (int j = t; j < i; ++j) { //Prints star after the middle line.
				printf("**");
		}
		printf("\n");
	}
	printf("\n");
}

void hourglass() {//It gets the height from user and executes draw_hourglass function.
	int height = 0;
	while (height%2 == 0) {
		printf("Please enter the height of the hourglass: ");
		scanf("%d",&height);
		if (height % 2 == 0)
			printf("Invalid number! Please enter an odd number.\n");
	}
	draw_hourglass(height);
}

void whitespaces(size) { //For the mountain_road function.
	for (int i = 0; i < size; ++i) { 
			printf(" ");
	}
}

void draw_mountain_road(int length, int max_radius) {
	int radius, space;
	space = max_radius+1; // This is for prevent the road from going left too much.
	for (int i = 0; i < length; ++i) { //Main loop. 
		radius = rand() % (max_radius + 1); //+1 for include the maximum radius.
		if (i % 2 == 0) { //If the road goes through left then right
			for (int j = 0; j < radius; ++j) { //It prints '/'. So i reduced number of spaces for the bottom lines.
				space--;
				whitespaces(space);
				printf("/\n");
			}
			space--; //This is for '|'. Loop ends after the last '/' so i need to decreased the space for the bottom line that prints '|'
			whitespaces(space);
			printf("|\n"); //If random radius is zero it prints just '|'.
			for (int k = 0; k < radius; ++k) { //It prints '\'. So i increased number of spaces for the bottom lines. 
				space++;
				whitespaces(space);
				printf("\\\n");
			}
		}
		else { // If the road goes through right then left. Same loops here.
			for (int k = 0; k < radius; ++k) { 
				space++;
				whitespaces(space);
				printf("\\\n");
			}
			space++;//This is for '|'. Loop ends after the last '\' so i need to increase the space for the bottom line that prints '|'
			whitespaces(space);
			printf("|\n");
			for (int j = 0; j < radius; ++j) { 
				space--;
				whitespaces(space);
				printf("/\n");
			}
		}
	}
}

void mountain_road() { //It gets the N and R values from user and executes draw_mountain_road function.
	int length, max_radius;
	printf("Please enter the length of the road: ");
	scanf("%d",&length);
	printf("Please enter the maximum radius of the half circles: ");
	scanf("%d",&max_radius);
	draw_mountain_road(length, max_radius);
}












