#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define MAX_DATA 100
#define MIN_DATA 0

typedef struct bst{
	int data;
	double time;
	struct bst *right;
	struct bst *left;
}bst;

typedef struct queue{
	int data;
	double time;
	struct queue *next;
}queue;

typedef struct stack{
	int data;
	double time;
	struct stack *next;
}stack;



void fill_structures(stack **stack_, queue **queue_, bst **bst_, int data[SIZE]);
void ordered_print(stack *stack_, queue *queue_, bst *bst_);
void search(stack *stack_, queue *queue_, bst *bst_, int val_to_search);
void special_traverse(stack *stack_, queue *queue_, bst *bst_);
void fill_stack(stack **stack_, int data[SIZE]);
void fill_queue(queue **queue_, int data[SIZE]);
void push(stack **stack_);
void data_print(stack *stack_);
void stack_print(stack *stack_);
void queue_print(queue *queue_);
void queue_traverse(queue *queue_);
void stack_traverse(stack *stack_);
void character_print(int number, char c);
void fill_bst(bst **bst_, int data[SIZE]);
void fill_bstt(bst **bst_, int data);
void bst_print(bst *bst);

int main() {
	int data[20] = {5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
	bst *bst_;
	queue *queue_;
	stack *stack_;
	fill_structures(&stack_, &queue_, &bst_, data);
	ordered_print(stack_, queue_, bst_);
	search(stack_, queue_, bst_, 5);
	special_traverse(stack_, queue_, bst_);
	return 0;
}

void fill_structures(stack **stack_, queue **queue_, bst **bst_, int data[SIZE]) {
	fill_stack(stack_, data);
	fill_queue(queue_, data);
	fill_bst(bst_, data);
	character_print(40, '-');
	printf("Fill\n");
	character_print(5, '-');
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",(*stack_)->time ,(*queue_)->time, (*bst_)->time );
	character_print(40, '-');
	
}

void fill_stack(stack **stack_, int data[SIZE]) {
	int i;
	clock_t start, end;
	stack *temp;
	(*stack_) = (stack*)malloc(sizeof(stack));
	temp = (*stack_);
	start = clock();
	for (i = 0; i < 20; i++) {
		if (i != 0) {
			push(stack_);
		}
		else
			temp->next = NULL;
		(*stack_)->data = data[i];
	}
	end = clock();
	(*stack_)->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void fill_queue(queue **queue_, int data[SIZE]) {
	int i;
	clock_t start, end;
	queue *temp;
	(*queue_) = (queue*)malloc(sizeof(queue));
	(*queue_)->data = data[0];
	temp = (*queue_);
	for (i = 1; i < 20; i++) {
		temp->next = (queue*)malloc(sizeof(queue));
		temp = temp->next;
		temp->data = data[i];
	}
	temp->next = NULL;
	end = clock();
	(*queue_)->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void fill_bst(bst **bst_, int data[SIZE]) {
	int i;
	clock_t start, end;
	bst *temp;
	start = clock();
	(*bst_) = (bst*) malloc(sizeof(bst));
	(*bst_)->left = NULL;
	(*bst_)->right = NULL;
	(*bst_)->data = data[0];
	for (i = 1; i < 20; i++) {
		fill_bstt(bst_, data[i]);
	}
	end = clock();
	(*bst_)->time = ((double) (end - start)) /CLOCKS_PER_SEC*1000;

}

void fill_bstt(bst **bst_, int data) {
	bst *temp = (*bst_);
	if (data > temp->data) {
		if (temp->right == NULL) {
			temp->right = (bst*) malloc(sizeof(bst));
			temp->right->data = data;
			temp->right->right = NULL;
			temp->right->left = NULL;
		}
		else {
			fill_bstt(&(*bst_)->right, data);
		}
	}
	else {
		if (temp->left == NULL) {
			temp->left = (bst*) malloc(sizeof(bst));
			temp->left->data = data;
			temp->left->right = NULL;
			temp->left->left = NULL;
		}
		else {
			fill_bstt(&(*bst_)->left, data);
		}
	}
}

void push(stack **stack_) {
	int counter = 1, i;
	stack *temp = (*stack_);
	while (temp->next != NULL) {
		counter++;
		temp = temp->next;
	}
	temp->next = (stack*)malloc(sizeof(stack));
	temp->next->next = NULL;
	while (counter > 0) {
		temp = (*stack_);
		for (i = 1; i < counter; i++) {
			temp = temp->next;
		}
		temp->next->data = temp->data;
		counter--;
	}
}

void ordered_print(stack *stack_, queue *queue_, bst *bst_) {
	printf("Order&Print\n");
	character_print(11, '-');
	printf("Stack ->");
	stack_print(stack_);
	printf("Queue ->");
	queue_print(queue_);
	printf("BST   ->");
	bst_print(bst_);
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_->time ,queue_->time, bst_->time );
	character_print(40, '-');
}

void stack_print(stack *stack_) {
	int max, counter = 0, count_same = 0;
	double max2;
	stack *temp = stack_;
	clock_t start, end;
	max = MIN_DATA; max2 = MAX_DATA; //I put two max values. max just finds the maximum number, max2 helps me to hold the last max number so i can find the number which is biggest from the ones that i didnt print yet. So when i look for the max number i just check if it is smaller than max2.
	start = clock();
	while (counter < 20) {
		while (temp != NULL) {
			if (temp->data == max2) { //If there is same number more than one in all datas, it prints, increases counter.
				count_same++;
				if (count_same > 1) {
					max = temp->data;
					printf("%d ",max);
					counter++;
				}
			}
			else if (temp->data > max && temp->data < max2)
				max = temp->data;

			temp = temp->next;
		}
		
		max2 = max;
		if (count_same > 1) //It prints when program finds a same number with max2, there i increase max2 by 0.5 so next time it cant be equal to max2 and move on to next number.
			max2 -= 0.5;
		else {
			printf("%d ",max);
			counter++;
		}
		max = MIN_DATA;
		count_same = 0;
		temp = stack_;
	}
	printf("\n");
	end = clock();
	stack_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void queue_print(queue *queue_) {
	int max, counter = 0, count_same = 0;
	double max2;
	queue *temp = queue_;
	clock_t start, end;
	max = MIN_DATA; max2 = MAX_DATA;
	start = clock();
	while (counter < 20) {
		while (temp != NULL) {
			if (temp->data == max2) {
				count_same++;
				if (count_same > 1) {
					max = temp->data;
					printf("%d ",max);
					counter++;
				}
			}
			else if (temp->data > max && temp->data < max2)
				max = temp->data;

			temp = temp->next;
		}
		
		max2 = max;
		if (count_same > 1)
			max2 -= 0.5;
		else {
			printf("%d ",max);
			counter++;
		}
		max = MIN_DATA;
		count_same = 0;
		temp = queue_;
	}
	printf("\n");
	end = clock();
	queue_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void bst_print(bst *bst_) {
	bst *tt, *t, *temp = bst_;
	int i, counter = 0;
	clock_t start, end;
	start = clock();
	while (temp->right != NULL) {
		t = temp;
		temp = temp->right;
		counter++;
	}
	temp = bst_;
	while (counter >= 0) {
		for (i = 0; i < counter; i++) {
			temp = temp->right;
		}
		printf("%d ",temp->data );
		tt = temp;
		while (tt->left != NULL) {
			if (tt->right != NULL)
				printf("%d ",tt->right->data );
			printf("%d ",tt->left->data );
			tt = tt->left;
		}
		counter--;
		temp = bst_;
	}
	printf("\n");
	end = clock();
	bst_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void search(stack *stack_, queue *queue_, bst *bst_, int val_to_search) {
	int counter = 1;
	clock_t start, end;
	printf("Search\n");
	character_print(6, '-');

	start = clock();
	while (stack_->next != NULL) {
		if (stack_->data == val_to_search) {
			printf("Stack -> 1 result founded on %d. step\n",counter);
		}
		stack_ = stack_->next;
		counter++;
	}
	if (stack_->data == val_to_search) 
		printf("Stack -> 1 result founded on %d. step\n",counter);

	end = clock();
	stack_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;

	counter = 1;

	start = clock();
	while (queue_->next != NULL) {
		if (queue_->data == val_to_search) {
			printf("Queue -> 1 result founded on %d. step\n",counter);
		}
		queue_ = queue_->next;
		counter++;
	}
	if (queue_->data == val_to_search) 
		printf("Queue -> 1 result founded on %d. step\n",counter);
	
	end = clock();
	queue_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
	
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t\n",stack_->time ,queue_->time );
	character_print(40, '-');
}

void special_traverse(stack *stack_, queue *queue_, bst *bst_) {
	printf("Special Traverse\n");
	character_print(20, '-');
	printf("Stack -> ");
	stack_traverse(stack_);
	printf("Queue -> ");
	queue_traverse(queue_);
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t\n",stack_->time ,queue_->time );
	character_print(40, '-');
}

void queue_traverse(queue *queue_) {
	int max, min, counter = 0, count_same_max = 0, count_same_min = 0, hold_same_max, hold_same_min, flag_max = 0, flag_min = 0;
	double max2, min2;
	queue *temp = queue_;
	clock_t start, end;
	max = MIN_DATA; max2 = MAX_DATA;
	min = MAX_DATA; min2 = MIN_DATA;
	start = clock();
	while (counter < 20) {
		while (temp != NULL) {
			if (temp->data == max2) {
				count_same_max++;
				if (count_same_max > 1) {
					max = temp->data;
					if (flag_max == 0) {
						hold_same_max = count_same_max;
						flag_max = 1;
					}
				}
			}
			else if (temp->data > max && temp->data < max2)
				max = temp->data;

			if (temp->data == min2) {
				count_same_min++;
				if (count_same_min > 1) {
					min = temp->data;
					if (flag_min == 0) {
						hold_same_min = count_same_min;
						flag_min = 1;
					}
				}
			}
			else if (temp->data < min && temp->data > min2)
				min = temp->data;

			temp = temp->next;
		}
		
		max2 = max;
		min2 = min;
		if (count_same_max > 1) {
			if (hold_same_max < 2) {
				max2 -= 0.5;
				flag_max = 0;
			}
			else {
				printf("%d ",max);
				counter++;
				hold_same_max--;
			}
		}
		else {
			printf("%d ",max);
			counter++;
		}
		if (count_same_min > 1) {
			if (hold_same_min < 2) {
				min2 += 0.5;
				flag_min = 0;
			}
			else {
				printf("%d ",min);
				counter++;
				hold_same_min--;
			}
		}
		else {
			printf("%d ",min);
			counter++;
		}
		max = MIN_DATA;
		min = MAX_DATA;
		count_same_max = 0;
		count_same_min = 0;
		temp = queue_;
	}
	printf("\n");
	end = clock();
	queue_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void stack_traverse(stack *stack_) {
	int max, min, counter = 0, count_same_max = 0, count_same_min = 0, hold_same_max, hold_same_min, flag_max = 0, flag_min = 0;
	double max2, min2;
	stack *temp = stack_;
	clock_t start, end;
	max = MIN_DATA; max2 = MAX_DATA;
	min = MAX_DATA; min2 = MIN_DATA;
	start = clock();
	while (counter < 20) {
		while (temp != NULL) {
			if (temp->data == max2) {
				count_same_max++;
				if (count_same_max > 1) {
					max = temp->data;
					if (flag_max == 0) {
						hold_same_max = count_same_max;
						flag_max = 1;
					}
				}
			}
			else if (temp->data > max && temp->data < max2)
				max = temp->data;

			if (temp->data == min2) {
				count_same_min++;
				if (count_same_min > 1) {
					min = temp->data;
					if (flag_min == 0) {
						hold_same_min = count_same_min;
						flag_min = 1;
					}
				}
			}
			else if (temp->data < min && temp->data > min2)
				min = temp->data;

			temp = temp->next;
		}
		
		max2 = max;
		min2 = min;
		if (count_same_max > 1) {
			if (hold_same_max < 2) {
				max2 -= 0.5;
				flag_max = 0;
			}
			else {
				printf("%d ",max);
				counter++;
				hold_same_max--;
			}
		}
		else {
			printf("%d ",max);
			counter++;
		}
		if (count_same_min > 1) {
			if (hold_same_min < 2) {
				min2 += 0.5;
				flag_min = 0;
			}
			else {
				printf("%d ",min);
				counter++;
				hold_same_min--;
			}
		}
		else {
			printf("%d ",min);
			counter++;
		}
		max = MIN_DATA;
		min = MAX_DATA;
		count_same_max = 0;
		count_same_min = 0;
		temp = stack_;
	}
	printf("\n");
	end = clock();
	stack_->time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
}

void data_print(stack *stack_) {
	stack *temp = stack_;
	while (temp->next != NULL) {
		printf("%d ",temp->data );
		temp = temp->next;
	}
	printf("%d\n",temp->data );
}

void character_print(int number, char c) {
	int i;
	for (i = 0; i < number; i++) {
		printf("%c",c );
	}
	printf("\n");
}








