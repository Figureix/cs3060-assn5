/*
Collaborative Extra Credit Effort
David C
Jason S
ECE 3060-601
Assignment 5

Originality Disclaimer: The following code we have written under our own efforts -- we have not used anothers work(s) to pass as ours
*/

#include <stdio.h>


int main(int argc, char *argv[]){
	printf("Hello World!\n");

	//arrays to hold the process run-time and the time the process was added to the ready queue
	int run_time[100];
	int ready_q_add[100];

	//open the file
	FILE *fp = stdin;
	if(argc > 1){
		fp = fopen(argv[1], "r");
        if(fp==NULL){
                perror("error opening file");
                return -1;
        }
	}

	//while loop index
	int i = 0;
	int number;

	//read run times into arrays
	while(fscanf(fp, "%d", &number) == 1){
		ready_q_add[i] = number;
		//read a new number
		fscanf(fp, "%d", &number);
		run_time[i] = number;
		i++;
	}
	//number of processes is half of i
	int count = i;

	// -------- Send Arrays to Functions/Modules ----------------
	//start with first come first serve
	//FCFS(run_time, ready_q_add, count);
	STRF(run_time, ready_q_add, count);

	return 0;
}


// Make my Module/Function for STRF
void STRF(int *run_remin, int *submit_q, int count){
	// my arrays are essentially constatns that I will compare against.
	// Declare my queue(s) for keeping track of jobs.
	int readyQ[100];
	int runLeft[100];
	int firstRun[100];
	int finish[100];
	// Declare my variable for keeping track of numbers/times/clocks
	int clk = submit_q[0], pclk = 0, debt, pick;
	
	// start doing calculations.
	
	
	
}























=======
void STRF(int passinthearraysfrommain){
	// my arrays are essentially constatns that I will compare against.
	// Declare my variable for keeping track of numbers/times/clocks
	// Declare my queue(s) for keeping track of jobs.
	
	
}
>>>>>>> 4b2cefae83b415bd360da05c4facd8b5d462acfd
