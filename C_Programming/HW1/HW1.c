#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3
#define Square 1
#define Rectangular 2
#define Circular 3
#define Red 0
#define Yellow 1
#define Blue 2
#define Black 3
#define White 4

double CreateBody(int shape);
int SetColor(int color);
double LoadMoves(int shape, double body_size);
int SetAttackPower(int lower_bound, int upper_bound);
void ShowPokemon(int shape, double size_of_body, int color, double move_length, int attack_power);

int main() {
	int shape, color, attack_power;
	double size_of_body, move_length;
	shape = Circular; 
	size_of_body = CreateBody(shape);
	color = 798;
	color = SetColor(color);
	move_length = LoadMoves(shape, size_of_body);
	attack_power = SetAttackPower(0, 150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);
}

double CreateBody(int shape) {
	int length,length2;
	if (shape == Square) {
		printf("Please enter one edge of your Square Pokemon: \n");
		scanf("%d",&length);
		return pow(length,2);
	}
	if (shape == Rectangular) {
		printf("Please enter the edges of your Rectangular Pokemon \n");
		scanf("%d %d",&length,&length2);
		return length*length2;
	}
	if (shape == Circular) {
		printf("Please enter the radius of your circular pokemon: \n");
		scanf("%d",&length);
		return PI*pow(length,2);
	}
	return -1;
}
int SetColor(int color) {
	if (color >= 0 && color <=1000)
		return color%5;
	return 1;
}
double LoadMoves(int shape, double body_size) { // All returns calculates perimeter from area.
	if (shape == Square) 
		return sqrt(body_size)*4;
	if (shape == Rectangular) 
		return 2*(body_size/5 + 5);
	if (shape == Circular)
		return 2*PI*sqrt(body_size/PI);
	return -1;
}
int SetAttackPower(int lower_bound, int upper_bound) {
	srand(time(NULL));
	return rand()%(upper_bound - lower_bound) + lower_bound;
}
void ShowPokemon(int shape, double size_of_body, int color, double move_length, int attack_power) {
	int radius = sqrt(size_of_body/PI);
	int edge;
	if (shape == Square) { 
		edge = move_length/4;
		for (int i = 0; i < edge; ++i) { //Drawing Square
			for (int i = 0; i < edge; ++i) {
				printf("X");
			}
			printf("\n");
		}
		printf("Name: Square Pokemon\n");
	}
	if (shape == Rectangular) {
		edge = size_of_body/5;
		for (int i = 0; i < 5; ++i) { //Drawing Rectangle
			for (int j = 0; j < edge; ++j) {
				printf("X");
			}
			printf("\n");
		}
		printf("Name: Rectangular Pokemon\n");
	}
	if (shape == Circular) { //Drawing Circle
		int t,x;
		if (radius == 1)
			printf("X\n");
		else if (radius%2 == 1) { // IF RADIUS IS ODD NUMBER
			for (int i = 0; i < radius; ++i) { //LINE
				t = radius/2;
				while (i!=t) { //TABS BEFORE X
					printf("\t");
					if (i > t) // Integer t equals to radius/2 because thats the middle line and we use less tabs after the middle line.
						t++;
					else 
						t--;
				}
				printf("X");
				if (i!= radius -1 && i!= 0) { //SPACE BEFORE SECOND X(EXCEPT FİRST AND LAST LINE)
					if (i <= radius/2) { //Number of tabs are increasing between two X until the middle line so i had to seperate them. Thats before the middle line.
						for (int j = 0; j < i; ++j) {	
							printf("\t\t");
						}
					}
					if (i > radius/2) { //After the middle line. (Number of tabs are decreasing)
						x = i;
						while (x < radius-1) {
							printf("\t\t");
							x++;
						}
					}
					printf("X");
				}
				printf("\n");
			}
		}
		else if (radius%2 == 0) { // IF RADIUS IS EVEN NUMBER
			for (int i = 0; i < (radius/2 -1); ++i) { //TABS BEFORE FIRST LINE X.
				printf("\t");
			}
			printf("    X\n"); //FIRST LINE X

			for (int i = 0; i < radius-1; ++i) { //LINE
				t = radius/2-1;
				while (i!=t) { //TABS BEFORE X
					printf("\t");
					if (i > t) // Integer t equals to radius/2 because thats the middle line and we use less tabs after the middle line.
						t++;
					else 
						t--;
				}
				printf("X"); //FIRST X
				printf("\t");// Thats because if the radius is even number of tabs are increasing like 1-3-5-7, so my algorithm increases tabs like 1 + 2n.
				if (i < radius/2) { // Number of tabs are increasing between two X until the middle line so i had to seperate them. Thats before the middle line.
					for (int j = 0; j < i; ++j) {
						printf("\t\t");
					}
					printf("X"); //SECOND X
				}
				if (i >= radius/2) { // After the middle line. (Number of tabs are decreasing)
					for (int k = i; k < radius-2; ++k) {
						printf("\t\t");
					}
					printf("X"); // SECOND X
				}
				printf("\n");
			}

			for (int i = 0; i < (radius/2 -1); ++i) { //LAST LINE X.
				printf("\t");
			}
			printf("    X\n");
		}
		printf("Name: Circular Pokemon\n");
	}
	printf("Size: %0.2lf\n",size_of_body );
	if (color == Red)
		printf("Color: Red\n");
	if (color == Yellow)
		printf("Color: Yellow\n");
	if (color == Blue)
		printf("Color: Blue\n");
	if (color == Black)
		printf("Color: Black\n");
	if (color == White)
		printf("Color: White\n");
	printf("Move: %0.2lf\n",move_length);
	printf("Attack power: %d\n",attack_power );

}













