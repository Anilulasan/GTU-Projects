#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 25

struct person{
	char name[SIZE];
	char surname[SIZE];
	char musical_work[SIZE];
	int age;
	struct person *next;
}*top;
typedef struct person person;

void menu();
void addNode(char name[SIZE], char surname[SIZE], char creation[SIZE], int age);
void deleteNode();
void Sort_Alphabetically();
void Sort_Increasingly();
void print_stack();

int main() {
	menu();
}

void menu() {
	char name[SIZE], surname[SIZE], creation[SIZE];
	int choice, age;
	top = (person*) malloc(sizeof(person));
	top->age = -1;
	do {
		printf("\t*************** MENU ****************\n\t1-\tAdd a Person to the Stack\n\t2-\tPop a Person from the Stack\n\t3-\tSort Alphabetical Order\n\t4-\tSort Age in Increasing Order\n\t5-\tExit menu\n************************************************\n");
		printf("Select your choice: ");
		scanf("%d",&choice);
		switch(choice) {
			case 1: 
					printf("Name: "); scanf(" %[^\n]",name);
					printf("Surname: "); scanf(" %[^\n]",surname);
					printf("Creation: "); scanf(" %[^\n]",creation);
					printf("Age: "); scanf("%d",&age);
					addNode(name, surname, creation, age);
					print_stack(); break;
			case 2: deleteNode(); print_stack(); break;
			case 3: Sort_Alphabetically(); print_stack(); break;
			case 4: Sort_Increasingly(); print_stack(); break;
			case 5: break;
			default: printf("Please enter a valid choice...");
		}
	}while(choice != 5);
}

void addNode(char name[SIZE], char surname[SIZE], char creation[SIZE], int age) {
	person *temp = top;
	int i, counter = 1;
	if (top->age != -1) { //It tests if top is empty or not. If top is empty, function fills top, if not it goes to top's next until it finds the last node before NULL.
		while(temp->next != NULL) {
			temp = temp->next;
			counter++;
		}
		counter++;
		temp->next = (person*) malloc(sizeof(person));
		temp->next->next = NULL;
	}
	if (counter == 1)
		top->next = NULL;

	while (counter > 1) { //Counter holds how many nodes are filled (including the one is getting filled now), In this algorithm temp goes to last node which is filled, and carries the variables to it's next which has memory allocated in 63th line. Then goes to previous of last node (by decreasing counter by 1), carries the variables to last node. Goes like that and shifts all values and lefts the head empty, and fills the head with the new entered values(parameters of addNode function). If counter is 1(which means top is empty, its the first entered value), it passes that loop and just fills the top.
		temp = top;
		for (i = 2; i < counter; i++) {
			temp = temp->next;
		}
		strcpy(temp->next->name, temp->name);
		strcpy(temp->next->surname, temp->surname);
		strcpy(temp->next->musical_work, temp->musical_work);
		temp->next->age = temp->age;
		counter--;
	}

	strcpy(top->name, name); //Fills head with new entered values.
	strcpy(top->surname, surname);
	strcpy(top->musical_work, creation);
	top->age = age;


	

}

void print_stack() {
	person *temp = top;
	int counter = 1;
	while (temp != NULL) {
		printf("%d)%s\n%s\n%s\n%d\n", counter, temp->name, temp->surname, temp->musical_work, temp->age );
		temp = temp->next;
		counter++;
	}
}

void deleteNode() {
	person *temp = top;
	person *t = temp;
	while (temp->next != NULL) { //Shifts the list to the left every step, and goes to next node until reaches NULL. Then deletes the last node which has variables shifted to previous node.
		t = temp;
		strcpy(temp->name, temp->next->name);
		strcpy(temp->surname, temp->next->surname);
		strcpy(temp->musical_work, temp->next->musical_work);
		temp->age = temp->next->age;
		temp = temp->next;
	}
	free(t->next); //t is the node before temp. This is the last node that its variables shifted to previous node.
	t->next = NULL;
}

void Sort_Alphabetically() {
	person *iter = top;
	int i, j, counter = 1, temp;
	char tempo[SIZE];
	while (iter->next != NULL) { //Counts how many node is filled. Needed for sort.
		counter++;
		iter = iter->next;
	}
	iter = top;
	for (i = 1; i < counter; i++) { //BUBBLE SORT
		for (j = 1; j < counter; j++) {
			if (strcmp(iter->next->name, iter->name) < 0) { //Checks the name's ASCII numbers, then changes all variables.
				strcpy(tempo, iter->name);
				strcpy(iter->name, iter->next->name);
				strcpy(iter->next->name, tempo);

				strcpy(tempo, iter->surname);
				strcpy(iter->surname, iter->next->surname);
				strcpy(iter->next->surname, tempo);

				strcpy(tempo, iter->musical_work);
				strcpy(iter->musical_work, iter->next->musical_work);
				strcpy(iter->next->musical_work, tempo);

				temp = iter->age;
				iter->age = iter->next->age;
				iter->next->age = temp;

			}
			iter = iter->next;
		}
		iter = top;
	}
}

void Sort_Increasingly() { //Sort_Alphabetically and Sort_Increasingly does the same job. Only difference is the if statement. Sort_Alphabetically tests name's ASCII with strcmp, Sort_Increasingly compares ages. 
	person *iter = top;
	int i, j, counter = 1, temp;
	char tempo[SIZE];
	while (iter->next != NULL) {
		counter++;
		iter = iter->next;
	}
	iter = top;
	for (i = 1; i < counter; i++) { //BUBBLE SORT
		for (j = 1; j < counter; j++) {
			if (iter->next->age < iter->age) {
				strcpy(tempo, iter->name);
				strcpy(iter->name, iter->next->name);
				strcpy(iter->next->name, tempo);

				strcpy(tempo, iter->surname);
				strcpy(iter->surname, iter->next->surname);
				strcpy(iter->next->surname, tempo);

				strcpy(tempo, iter->musical_work);
				strcpy(iter->musical_work, iter->next->musical_work);
				strcpy(iter->next->musical_work, tempo);

				temp = iter->age;
				iter->age = iter->next->age;
				iter->next->age = temp;
			}
			iter = iter->next;
		}
		iter = top;
	}
}


















