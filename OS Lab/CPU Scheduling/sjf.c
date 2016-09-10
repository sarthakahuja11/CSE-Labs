//
//  sjf.c
//  Simulation of SJF scheduling algorithm (non pre-emptive)
//
//  Created by Avikant Saini on 9/9/16.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum { NO, YES } BOOL;

typedef struct data {
	int id;		// process id
	int at;		// arrival time
	int bt;		// burst time
	int wt;		// wait time
	int tat;	// turnaround time
} DATA_t, *DATA_p_t;

double awt, atat; // Average wait time and average turnaround time
int n;

DATA_p_t *datas;

void inputData () {
	printf("Enter the number of processes: ");
	scanf(" %d", &n);
	int i;
	datas = (DATA_p_t *)calloc(n, sizeof(DATA_p_t));
	for (i = 0; i < n; ++i) {
		*(datas + i) = (DATA_p_t)malloc(sizeof(DATA_t));
		DATA_p_t data = *(datas + i);
		data->id = i;
		printf("Process [%d] Enter arrival time: ", i+1);
		scanf(" %d", &data->at);
		printf("Process [%d]   Enter burst time: ", i+1);
		scanf(" %d", &data->bt);
		data->wt = 0;
		data->tat = 0;
	}
}

void sort () {
	int i;
	for (i = 1; i < n; ++i) {
		int j = i - 1;
		DATA_p_t temp = datas[i];
		while (j >= 0 && datas[j]->bt > temp->bt) {
			datas[j+1] = datas[j];
			j--;
		}
		datas[j+1] = temp;
	}
}

// First come first serve based calculation
void calculate () {
	int i;
	(*datas)->wt = 0;
	atat = (*datas)->tat = (*datas)->bt;
	int btt = (*datas)->bt;
	for (i = 1; i < n; ++i) {
		DATA_p_t datai = *(datas + i);
		datai->wt = btt - datai->at;
		btt += datai->bt;
		awt += datai->wt;
		datai->tat = datai->wt + datai->bt;
		atat += datai->tat;
	}
	atat /= n;
	awt /= n;
}

void display () {
	int i;
	printf("\n ID\t| AT\t| BT\t| WT\t| TAT\n");
	for (i = 0; i < n; ++i) {
		DATA_p_t data = *(datas + i);
		printf(" %d\t| %d\t| %d\t| %d\t| %d\n", data->id, data->at, data->bt, data->wt, data->tat);
	}
	printf("----------------------------------------\n");
}

int main(int argc, char const *argv[]) {
	// Sample input: 4 0 5 1 3 2 8 3 6
	// Sample output: 5.00
	
	inputData();
	
	printf("\nInitially: \n");
	display();
	
	sort();
	calculate();
	
	printf("\nAfter exeggution: \n");
	display();
	
	printf("Average wait time = %.2lf\n", awt);
	printf("Average turnaround time = %.2lf\n\n", atat);
	
	return 0;
}
