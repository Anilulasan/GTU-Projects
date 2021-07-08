#include <stdio.h>

#define ARR_SIZE 50

void part5();
char find_Capital(char sentence[], int n);
void part4();
int find_digits(int digits[], int number, int n);
int is_equal(int number, int digits[], int n, int digit_number);
void part3();
void function(int number);
void part2();
void print_array(int arr[], int size);
void merge(int arr[], int size, int temp1[], int temp2[]);
void part1();
int common(int big_number, int small_number, int divisor, int multipliers_1[], int multipliers_2[], int *n1, int *n2);
int is_prime(int number);
void print_multipliers(int array[], int limit); 
void menu();
int power(int base, int exponent);

int main() {
	menu();
}

void menu() {
	int choice;
	do {
		printf("1. Greatest common divisor \n2. Sort numbers \n3. Go until 1\n4. Is equal \n5. Find first Capital \n6. Exit\n\tChoice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: part1(); break;
			case 2: break;
			case 3: part3(); break;
			case 4: part4(); break;
			case 5: part5(); break;
		}
	}
	while (choice != 6);

}

void part5() {
	char sentence[100], test;
	printf("Please type something and do not use space between words: ");
	scanf("%s",sentence);
	test = find_Capital(sentence, 0);
	if (test >= 'A' && test <= 'Z')
		printf("%c\n",test );
	else
		printf("There is no capital letters in this sentence\n");
}

char find_Capital(char sentence[], int n) {
	if (sentence[n] <= 'Z' && sentence[n] >= 'A')
		return sentence[n];
	if (sentence[n] == '\0')
		return 0;
	return find_Capital(sentence, n + 1);
}

int power(int base, int exponent) {
	if (exponent == 0)
		return 1;
	if (exponent == 1) 
		return base;
	return base * power(base, exponent - 1);
}

void part4() {
	int number, answer, digits[10], digit_number;
	printf("Please enter an integer: ");
	scanf("%d",&number);
	answer = is_equal(number, digits, 100, digit_number);
	if (answer == number)
		printf("Equal\n");
	else
		printf("Not Equal\n");
}

int find_digits(int digits[], int number, int n) {
	if (number < power(10,n)) 
		return n;
	digits[n] = (number / power(10,n)) % 10;
	return find_digits(digits, number, n+1);
}

int is_equal(int number, int digits[], int n, int digit_number) {
	int answer=0;
	if (n == 0)
		return answer;
	if (n == 100) {
		n = find_digits(digits, number, 0);
		digit_number = n;
	}
	answer = power(digits[n - 1], digit_number);
	return answer + is_equal(number, digits, n - 1, digit_number);
}

void part3() {
	int number;
	printf("Please enter an integer: ");
	scanf("%d",&number);
	function(number);
	printf("\n");
}

void function(int number) {
	if (number % 2 == 0) {
		number /= 2;
	}
	else
		number = (number*3) + 1;
	printf("%d ",number );
	if (number != 1)
		function(number);
}

void part2() {
	int list, numbers[ARR_SIZE], temp1[ARR_SIZE / 2], temp2[ARR_SIZE / 2];
	printf("Enter the length of the list: ");
	scanf("%d", &list);
	for (int i = 0; i < list; ++i) {
		scanf("%d",&numbers[i]);
	}
	merge(numbers, list, temp1, temp2);
	print_array(numbers, list);
}

void merge (int numbers[], int n, int temp1[], int temp2[]) { // I cant divide the numbers until it cant be divided then sort them. Because i have to declare an array for each part.
	int temp, i, j, h;
	h = n / 2;
	for (i = 0; i < h; ++i) {
		temp1[i] = numbers[i];
	}
	for (i = h; i < n; ++i) {
		temp2[i] = numbers[i];
	}
	for (i = 0; i < h; ++i) {
		for (j = 0; j < h - 1; ++j) {
			if (temp1[j + 1] < temp1[j]) {
				printf("%d %d\n",temp1[j], temp1[j + 1] );
				temp = temp1[j];
				temp1[j] = temp1[j + 1];
				temp1[j + 1] = temp;
			}
		}
	}
	for (i = h; i < n; ++i) {
		for (j = 0; j < n - h - 1; ++j) {
			if (temp2[j + 1] < temp2[j]) {
				temp = temp2[j];
				temp2[j] = temp2[j + 1];
				temp2[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < h; ++i) {
		numbers[i] = temp1[i];
	}
	for (i = h; i < n; ++i) {
		numbers[i] = temp2[i];
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n - 1; ++j) {
			if (numbers[j + 1] < numbers[j]) {
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}
	}
	if (n != 1) 
		merge(numbers, n/2, temp1, temp2);
}

void print_array(int arr[], int size) {
	int i;
	for (i = 0; i < size; ++i) {
		printf("%d ",arr[i] );
	}
}

void part1() {
	int gcd, i, temp, number1, number2, multipliers_1[20], multipliers_2[20], n1 = 0, n2 = 0;
	printf("Please enter two numbers to find their great common divisor: \n");
	scanf("%d %d", &number1, &number2);
	if (number1 < number2) { //In common function divisor increases until big_number/2 so to be sure i made the number1 bigger number.
		temp = number2;
		number2 = number1;
		number1 = temp;
	}
	gcd = common(number1, number2, 2, multipliers_1, multipliers_2, &n1, &n2);
	printf("Multipliers of %d: ",number1 );
	print_multipliers(multipliers_1, n1); // This function just prints.
	printf("Multipliers of %d: ",number2 );
	print_multipliers(multipliers_2, n2); //This function just prints.
	printf("Greatest common divisor is: %d\n",gcd);
	
}

int common(int big_number, int small_number, int divisor, int multipliers_1[], int multipliers_2[], int *n1, int *n2) { //Finds all prime multipliers of the two numbers seperately and stores them in multipliers_ arrays. n1 and n2 are pointers because i have to send them to main func of this part (part1 function) to print the multipliers of numbers.
	int flag, gcd = 1;
	int i, i1 = 1, i2 = 1;
	if (divisor - 2 == 0) 
		gcd = 1;
	if (divisor > big_number / 2) {
		return gcd;
	}

	flag = 0;
	while(flag == 0) {
		if (big_number % power(divisor, i1) == 0 && is_prime(divisor) == 1) { //If the divisor is multiplier of the number, it tests further to see how many of that divisor it has.
			multipliers_1[*n1] = divisor;
			*n1 += 1;
			i1++;
		}
		else {
			flag = 1;
		}
	}
	flag = 0;
	while(flag == 0) {
		if (small_number % power(divisor, i2) == 0 && is_prime(divisor) == 1) {
			multipliers_2[*n2] = divisor;
			*n2 += 1;
			i2++;
		}
		else 
			flag = 1;
	}
	for (i = 2; i <= i1; ++i) { //i1 increases if divisor is a multiplier of number1. i2 does for number2. It tests how much they increased for that divisor, if they both increased this turn(turn means "for that divisor" (divisor gonna increase by 1 next turn)) it means that divisor is common multiplier. If both i1 and i2 increased more than one this turn it means power of this divisor is common multiplier, so it multiplies gcd as how much they both increased. Loop goes until i1 but it doesnt matter since there is an if statement downwards, which tests both values. 
		if (i1 >= i && i2 >= i) {
			gcd *= divisor;
		}
		else
			break;
	}
	return gcd * common(big_number, small_number, divisor + 1, multipliers_1, multipliers_2, n1, n2);
}

void print_multipliers(int array[], int limit) {
	int i;
	printf("{");
	for (i = 0; i < limit; ++i) {
		printf("%d",array[i] );
		if (i != limit -1)
			printf(", ");
	}
	printf("}");
	printf("\n");
}

int is_prime(int number) {
	int i, counter = 0;
	for (i = 2; i <= number / 2; ++i) {
		if (number % i == 0) {
			counter ++;
			break;
		}
	}
	if (counter == 0)
		return 1;
	return 0;
}
















