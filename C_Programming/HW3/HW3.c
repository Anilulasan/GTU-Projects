#include <stdio.h>


void Calculator();
void Grades();
void draw_Triangle();
void menu();

int main() {	
	menu();
}

void menu() {
	int choice;
	do {
		printf("***** MENU *****\n 1.Calculator \n 2.Average Grade \n 3.Triangle \n 4.Exit ");
		scanf("%d",&choice);
		switch(choice) {
			case 1: Calculator(); break;
			case 2: Grades(); break;
			case 3: draw_Triangle(); break;
			case 4: break;
			default: printf("Invalid number! Try again.\n");
		}
	}while(choice != 4);
}

////////////////////////////// PART 1 ////////////////////////////////////////////////////////

int add(int number1, int number2) {
	return number1 + number2;
}
int sub(int number1, int number2) {
	return number1 - number2;
}
int mult(int number1, int number2) {
	return number1 * number2;
}
int div(int number1, int number2) {
	return number1 / number2;
}
int mod(int number1, int number2) {
	return number1 % number2;
}
int power(int number1, int number2) {
	double result = 1;
	if (number2 > 0) 
		for (int i = 0; i < number2; ++i) {
			result *= number1;
		}
	if (number2 < 0)
		for (int i = 0; i > number2; --i) {
			result /= number1;
		}
	return result;
}

int doit(int f(int number1, int number2), int first_number, int second_number) {
	return f(first_number, second_number);
}

void Calculator() { //YOU HAVE TO ENTER THE OPERATOR AND NUMBERS LIKE OPERATOR -> SPACE -> NUMBER -> SPACE -> NUMBER -> ENTER. PRESS ENTER AFTER YOU TYPE ALL THE VARIABLES.
	int number1, number2, result = 0;
	char operator, check, check2;
	do {
		scanf(" %c",&operator);
		scanf("%c",&check2);
		scanf("%d",&number1);
		scanf("%c",&check);
		if (check == ' ') //This is for check the second number. If you press space after the first number that means you are gonna enter another number. So there it takes number2 from user.
			scanf("%d",&number2);
		else { //If you press enter after the first number that means you are not gonna enter another number. So for the doit functions first i assigned number1 to number2 then the last result to number1. 
			number2 = number1;
			number1 = result;
		}
		switch(operator) {
			case '+':result = doit(add, number1, number2); break;
			case '-':result = doit(sub, number1, number2); break;
			case '*':result = doit(mult, number1, number2); break;
			case '/':result = doit(div, number1, number2); break;
			case '%':result = doit(mod, number1, number2); break;
			case '.':result = doit(power, number1,number2); break;
		}
		if (operator == '*' && check2 == '*') //'**' this power sign cannot assignable to one character variable. So i used another scanf(check2) to check if it is multiplication or power.
			result = doit(power, number1, number2);
		printf("%d\n",result);
	}while(operator != 's'); //WHEN YOU TYPE 's' FOR OPERATOR CALCULATOR STOPS.
}

////////////////////////////// PART 2 ////////////////////////////////////////////////////////

int take_grades(int array[]) { //This function gets homework and lab grades. 
	for (int i = 0; i < 10; ++i) {
		scanf("%d",&array[i]);
	}
	return 0;
}	

int take_exam_grades(int array[]) {
	printf("Please enter your midterm grade: ");
	scanf("%d",&array[0]);
	printf("Please enter your final grade: ");
	scanf("%d",&array[1]);
	return 0;
}

double calculate_homework(int array[]) {
	double sum = 0;
	for (int i = 0; i < 10; ++i) {
		sum += array[i];
	}
	return sum / 10;
}

double calculate_lab(int array[]) {
	double sum = 0;
	for (int i = 0; i < 10; ++i) {
		sum += array[i];
	}
	return sum / 10;
}

double calculate_all(int homework, int array[], int labaratory) { //It doesnt calculate perfectly because homework and labaratory variables are integer type.
	double midterm = array[0];
	double final = array[1];
	return homework/10 + labaratory/5 + 3*midterm/10 + 2*final/5;
}

void Grades() { //I used all the functions here.
	double lab, homework;
	int grades[10],exam_grades[2];
	printf("Please enter your homework grades:\n");
	take_grades(grades);
	homework = calculate_homework(grades);
	printf("Please enter your labaratory grades\n");
	take_grades(grades);
	lab = calculate_lab(grades);
	take_exam_grades(exam_grades);
	printf("Average of your grades : %.2f\n",calculate_all(homework, exam_grades, lab));
}

///////////////////////////////// PART 3 //////////////////////////////////////////////////////

void draw_Triangle() {
	int height, line;
	printf("Please enter the height of the triangle: ");
	scanf("%d",&height);

	for (int i = 1; i <= 2*height; ++i) {// Main loop 
		line = i;
		while(line != height && line != height + 1) { //SPACES
			printf(" ");
			if (line >= height)
				line --;
			else
				line++;
		}
		if (i <= height) //Thats because upper triangle starts with '/' and lower triangle starts with '\'
			printf("/");
		else
			printf("\\");

		if (i > 1 && i <= height) //STARS
			for (int j = 1; j < i; ++j) {
					printf("**");
			}
		else if(i > height && i < 2*height) // There is two loops for stars because in the upper triangle number of stars are increasing, in the lower triangle its decreasing every line.
			for (int k = i; k < 2*height; ++k) {
				printf("**");
			}

		if (i > height) //Thats because upper triangle ends with '\' and lower triangle ends with '/'
			printf("/"); 
		else
			printf("\\");

		printf("\n");
	}
}






















