// David C
// I worked on the following two alorithms
// I have declared the functions directly into this header file, rather than make multipule files.

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
		clk = submit_q[i];;
		runLeft[i] = reqRunTime[i]; 

		if (i == 0) {
			firstRun[i] = clk;
		}
		else {
			pclk = submit_q[i - 1]; // update preveious clock
			
			
			int j = 0;
			pick = i; // set pick to i -- assuming A: it's the first job, B: New job has less time than last run job
			// pick the sortest time left
			while (runLeft[j] == 0 && j < i) j++;
			while (runLeft[pick] == 0 && pick > j) pick--;
			for (j; j < i; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
			// pick has been set.
			
			// do math, check start time(s)
			debt = runLeft[pick] - (clk - pclk);
			if (debt <= 0){
				finish[pick] = clk;
				//if (reqRunTime[pick] == runLeft[pick]) firstRun[pick] = clk - debt;
				runLeft[pick] = 0;
				while (debt < 0) {
					// set pick jobs finish time
					finish[pick] = clk + debt;
					
					// pick next smallest time remainging before new add
					j = 0;
					pick = i - 1;
					while (runLeft[j] == 0 && j <= pick) j++;
					while (runLeft[pick] == 0 && pick > j) pick--;
					if (j == pick && runLeft[j] == 0) break; // We have had idle time since recieving new job.
					for (j; j < pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
					
					// or we have a new smallest time.
					if (reqRunTime[pick] == runLeft[pick]) firstRun[pick] = clk + debt;
					
					// Run the next process
					runLeft[pick] += debt;
					if (runLeft[pick] >= 0) debt = 0;
					else {
						// we still have debt -- We'll have to get the next shortest job and run again.
						runLeft[pick] = 0;
						printf("uh oh, didn't plan for extra debt");
						debt = 0;
						//debt = runLeft[pick];
						//runLeft[pick] = runLeft[pick] * -1;
						// the more I write this,the more I think I would need a recursive case......
					}
				}
			}
			else {
				// Job is not done
				if (reqRunTime[pick] == runLeft[pick]) firstRun[pick] = clk - debt;
				runLeft[pick] = debt;
				
				
			}
		}
	}
}


void RoundRobin(int *reqRunTime, int *submit_q, int count){
	// todo
}