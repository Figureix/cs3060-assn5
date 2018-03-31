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
	int count = i;

	// -------- Send Arrays to Functions/Modules ----------------
	//start with first come first serve
	//FCFS(run_time, ready_q_add, count);
	STRF(run_time, ready_q_add, count);

	return 0;
}


// Make my Module/Function for STRF
void STRF(int *reqRunTime, int *submit_q, int count){
	// my arrays are essentially constatns that I will compare against.
	// Declare my queue(s) for keeping track of jobs.
	int jobQ[100];
	int runLeft[100];
	int firstRun[100];
	int finish[100];
	// Declare my variable for keeping track of numbers/times/clocks
	int clk, pclk = 0, debt, pick = 0, i = 0;
	
	// start doing calculations.
	for (i; i < count; i++;){
		// set the clock to current/submitted job. Add job to que along with required time
		clk = submit_q[i];
		pclk = clk;
		jobQ[i] = submit_q[i];
		runLeft[i] = reqRunTime[i]; 
		
		pick = i; // set pick to i -- assuming A: it's the first job, B: New job has less time than last run job
		// pick the sortest time left
		int j = 0, check;
		for (j; j <= i; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
		// pick has been set.
		
		if (i == 0) {
			runLeft[i] = reqRunTime[i]; // add first job to que
			firstRun[i] = clk;
		}
		else {
			pclk = submit_q[i - 1]; // update preveious clock
			// do math, check start time(s)
			debt = runLeft[pick] - (clk - pclk);
			if (debt <= 0){
				finish[pick] = clk;
				runLeft[pick] = 0;
				while (debt < 0) {
					// set pick jobs finish time
					finish[pick] = clk + debt;
					// pick next smallest time remainging (depending on debt, may have to run severa jobs)
					j = 0;
					check = pick;
					for (j; j <= i; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
					if (pick == check) break; // All jobs in Q have finished -- there must be a gap in processes
					// or we have new smallest time.
					if (reqRunTime[pick] == runLeft[pick]) firstRun[pick] = clk + debt;
					// Run the next process
					runLeft[pick] += debt;
					if (runLeft[pick] >= 0) debt = 0;
					else {
						// we still have debt
						printf("uh oh, didn't plan for extra debt");
						debt = 0;
						//debt = runLeft[pick];
						//runLeft[pick] = runLeft[pick] * -1;
						// the more I write this,the more I thin I would need a recursive case......
					}
				}
			}
			else {
				// perhaps the job finished intime for next job
				if (reqRunTime[pick] == runLeft[pick]) firstRun[pick] = clk;
				runLeft[pick] = debt;
			}
		}
	}
}


void RoundRobin(int *reqRunTime, int *submit_q, int count){
	// todo
}
























