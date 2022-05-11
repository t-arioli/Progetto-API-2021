
/*LAST UPDATE: 18/08/2021 19:44*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define ADD_GRAPH "AggiungiGrafo"
#define TOP_K "TopK"
#define MAX_SIZE 13

int d, k;

typedef struct _vertice{
	int id;
	int estimatedWeight;
	struct _vertice *next;
}vertice;

typedef struct _graph{
	int id;
	int minimumPath;
	struct _graph *next;
	struct _graph *prev;
}graph;

struct rank{
	int tot;
	graph *head;
	graph *tail;
};

//gets the input from stdin
void getInput(int d, int k);
//adds the graph to a matrix
struct rank addGraph(struct rank best, int d, int index);
//dijsktra alg
int minimumPath(int matrix[d][d]);
//add vertice to queue
vertice *enqueue(vertice *q, vertice *new);
//relax the neightbours
int relax(int uWeight, int vWeight, int weightFromUToV);
//saves graphs if it's a minimum path lesser than one in rank
struct rank savePath(struct rank best, int index, int minimumPath);
//prints the best k graphs
void topK(struct rank best);
//initialize heap
struct rank initialize(struct rank best);
//insert the new in the top k rank structure 
struct rank insert(struct rank best, graph *new);

int main(int argc, char *argv[])
{
	if(fscanf(stdin, "%d%*c%d", &d, &k)>0)
		getInput(d, k);
	return 0;
}

void getInput(int d, int k){

	int count = 0;

	struct rank best;
	best = initialize(best);
	
	while(!feof(stdin)){
		char *input = (char *)malloc(sizeof(char));
		if(fscanf(stdin, "%s", input)>0){
			if(strcmp(input, ADD_GRAPH)==0){
				best = addGraph(best, d, count);
				count++;
				//topK(best);
			}
			else if(strcmp(input, TOP_K)==0)
				topK(best);
		}
		free(input);
	}
	
}

struct rank addGraph(struct rank best, int d, int index){
	int adjancencyMatrix[d][d];
	int minPath;
	
	for(int i=0; i<d; i++){
		char *input = (char *)malloc(10*d*sizeof(char));
		int j=0;
		int value = 0;
		int stop = 0;
		if(fscanf(stdin, "%s", input))
			;
		
		for(int k=0; stop == 0 ; k++){
			if(input[k] == ',' || input[k]=='\0'){
				adjancencyMatrix[i][j]=value;
				if(input[k]=='\0')
					stop=1;
				else{
					j++;
					value = 0;
				}
			}
			else{
				value *= 10;
				value += (int)input[k]-'0';
			}
		}
		free(input);
	}

	minPath = minimumPath(adjancencyMatrix);
	best = savePath(best, index, minPath);	
	return best;
}

int minimumPath(int matrix[d][d]){
	int sum = 0;
	vertice *queueHead = NULL;
	
	for(int i=0; i<d; i++){
		vertice *new = (vertice *)malloc(sizeof(vertice));
		new -> id = i;
		if(i == 0)
			new ->estimatedWeight = 0;
		else
			new ->estimatedWeight = INT_MAX;
		new->next = NULL;
		queueHead = enqueue(queueHead, new);
	}
	while(queueHead!=NULL){

		vertice *u = queueHead;
		queueHead = queueHead->next;
		if(u->estimatedWeight < INT_MAX){
			sum += u->estimatedWeight;
			//runs all the queue members (possible inefficiency here)
			vertice *prev = NULL;
			for(vertice *ptr = queueHead; ptr; ptr = ptr->next){
				//if there's an edge from u to ptr
				if(matrix[u -> id][ptr -> id]>0){
					//relax the weight
					int weight =  relax(u -> estimatedWeight, ptr -> estimatedWeight, matrix[u -> id][ptr -> id]);
					if(weight!=0){
						if(prev!=NULL){
							prev -> next = ptr -> next;
						}
						else{
							queueHead = ptr->next;
						}
						ptr -> estimatedWeight = weight;
						ptr -> next = NULL;
						queueHead = enqueue(queueHead, ptr);
					}
				
				}
				prev = ptr;
			}
			free(u);
		}
		else{
			free(queueHead);
			queueHead = NULL;
		}
	}
	free(queueHead);
	return sum;
}

//CHECK THIS FOR INEFFICIENCY
//insert ordered
vertice *enqueue(vertice *q, vertice *new){
	if(q==NULL)
		//first
		q=new;
	else{
		vertice *ptr = NULL;
		vertice *prev = NULL;
		for(ptr = q; ptr; ptr = ptr->next){
			if(ptr->estimatedWeight>=new ->estimatedWeight){
				if(prev!=NULL){
					//others
					prev->next = new;
					new->next = ptr;

				}
				else{
					new->next = q;
					q = new;
				}
				break;
			}	
			prev = ptr;	
		}
		if(ptr==NULL)
			prev ->next = new;
	}
	return q;
}


int relax(int uWeight, int vWeight, int weightFromUToV){
	if(vWeight>uWeight+weightFromUToV && uWeight+weightFromUToV>0){
		vWeight = uWeight+weightFromUToV;
		return vWeight;
	}
	return 0;	
}


struct rank savePath(struct rank best, int index, int minimumPath){
	graph *new = (graph *)malloc(sizeof(graph));
	new->id = index;
	new->minimumPath = minimumPath;
	new->prev = NULL;
	new->next = NULL;
	best = insert(best, new);
	return best;
}

void topK(struct rank best){
	for(graph *ptr = best.head; ptr; ptr = ptr->next){
		if(ptr->next == NULL)
			fprintf(stdout, "%d", ptr->id);
		else
			fprintf(stdout, "%d ", ptr->id);
		}
	fprintf(stdout, "\n");
}

struct rank initialize(struct rank best){
	best.tot = 0;
	best.tail = NULL;
	best.head = NULL;
	return best;
}
//efficiency O(n)?
struct rank insert(struct rank best, graph *new){

	if(best.tot < k){
		if(best.head == NULL){
			//head setup
			best.head = new;
			best.tail = new;
		}
		else{
			if(best.head->minimumPath < new->minimumPath){
				//the new is highest than the end 
				new->next = best.head;
				best.head->prev = new;
				best.head = new;
			}
			else if(best.tail->minimumPath > new->minimumPath){
				best.tail->next = new;
				new->prev = best.tail;
				best.tail = new;
			}
			else{
				for(graph *ptr = best.head; ptr; ptr=ptr->next){
					if(ptr->minimumPath < new->minimumPath){
						//neighbours
						ptr->prev->next = new;
						new->prev = ptr->prev;
						new->next = ptr;
						ptr->prev = new;
						break;
					}
				}
			}
		}
		best.tot=best.tot+1;
	}
	else if(new->minimumPath < best.head->minimumPath){
		//erase highest
		graph *tmp = best.head;
		best.head = best.head->next;
		best.head->prev = NULL;
		free(tmp);
		//check new head and tail first
		if(new->minimumPath > best.head->minimumPath){
			new->next = best.head;
			best.head->prev = new;
			best.head = new;
		}
		else if(new->minimumPath <= best.tail->minimumPath){
			//last = minimum probability of being erased -> the first minimum stays minimum (if equals) ???
			best.tail->next = new;
			new->prev = best.tail;
			best.tail = new;
		}
		else{
			for(graph *ptr = best.head; ptr; ptr=ptr->next){
					if(ptr->minimumPath < new->minimumPath){
						//neighbours
						ptr->prev->next = new;
						new->prev = ptr->prev;
						new->next = ptr;
						ptr->prev = new;
						break;
					}
				}
		}

	}

	return best;
	
}




