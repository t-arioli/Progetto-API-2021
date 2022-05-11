#include<stdio.h>
#include<stdlib.h>
#define OUTPUT "output"
#define TEST_OUPUT1 "test/open_tests/output_1" 
#define TEST_OUPUT2 "test/open_tests/output_2" 
#define TEST_OUPUT3 "test/open_tests/output_3" 
#define TEST_OUPUT4 "test/open_tests/output_4" 
#define TEST_OUPUT5 "test/open_tests/output_5"
#define TEST_OUPUT6 "test/open_tests/output_6"  

typedef struct _list{
	int val;
	struct _list *next;
}list;

list *append(list *head, int val){
	list *new;
	if((new = (list *)malloc(sizeof(list)))){
		new -> val = val;
		new ->next = NULL;
		if(head==NULL){
			head = new; 
		}
		else{
			list *ptr;
			for(ptr = head; ptr->next; ptr = ptr ->next);
			ptr->next = new; 	
		}
	}
	else{
		printf("MEMORY ERROR: ABORT\n");
		return NULL;
	}
	return head;
}

list *findAndRemove(list *head, int val){
	list *prev = NULL;
	for(list *ptr = head; ptr; ptr= ptr->next){
		if(ptr->val == val){
			if(prev == NULL)
				head = head->next;
			else{
				prev->next = ptr->next;
				free(ptr);
			}
			return head;
		}
		prev = ptr;
	}
	printf("TEST NOT SUCCESSFULL\n");
	return NULL;
}

list *getTestOutput(char *fileName){
	FILE *output;
	list *head = NULL;
	int val;
	int tmp;

	if((output = fopen(fileName, "r"))){
		tmp = fscanf(output, "%d", &val);
		while(!feof(output)){
			head = append(head, val);
			tmp = fscanf(output, "%d", &val);
		}
		fclose(output);
		if(tmp)
			;
	} 
	else
		printf("ERROR OPENING %s\n", fileName); 

	//for(list *ptr = head; ptr; ptr=ptr->next)
	//	printf("%d ", ptr->val);
	//printf("\n");
	return head;
}

int main(int argc, char *argv[])
{
	FILE *output;
	int val;
	list *test = getTestOutput(argv[1]);
	int tmp;

	printf("START TESTER\n");


	if((output = fopen(OUTPUT, "r"))){
		tmp=fscanf(output, "%d", &val);
		while(!feof(output)){
			//printf("%d ", val);
			test = findAndRemove(test, val);
			tmp=fscanf(output, "%d", &val);
			if(test==NULL && !feof(output)){
				printf("TEST FAILED\n");
				return 0;
			}
		}
		fclose(output);
		printf("TEST SUCCESSFULLY PASSED\n");
		if(tmp)
			;
	}
	else{
		printf("ERROR OPENING %s\n", OUTPUT); 
	}

	return 0;
}