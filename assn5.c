/*
Collaborative Extra Credit Effort
David C
Jason S
ECE 3060-601
Assignment 5

Originality Disclaimer: The following code we have written under our own efforts -- we have not used anothers work(s) to pass as ours
*/

#include <stdio.h>

//function prologues
void FCFS(int*, int*, int);
void SJF(int*, int*, int);


int main(int argc, char *argv[]){
	printf("Hello World!\n");

//arrays to hold the process run-time and the time the process was added to the ready queue
int run_time[100];
int ready_q_add[100];

//open the file
FILE *fp = stdin;
if(argc > 1)
{
fp = fopen(argv[1], "r");
        if(fp==NULL)
                {
                perror("error opening file");
                return -1;
                }
}

//while loop index
int i = 0;
int number;

//read run times into arrays
while(fscanf(fp, "%d", &number) != EOF)
{
ready_q_add[i] = number;
//read a new number
fscanf(fp, "%d", &number);
run_time[i] = number;
i++;
}

//number of processes is i
int count = i;

//start with first come first serve
FCFS(run_time, ready_q_add, count);

//shortest job first
SJF(run_time, ready_q_add, count);

	return 0;
}
