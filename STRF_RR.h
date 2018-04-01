// David C
// I worked on the following two alorithms
// I have declared the functions directly into this header file, rather than make multipule files.

// Make my Module/Function for STRF
void STRF(int *reqRunTime, int *submit_q, int count){
	// my arrays are essentially constatns that I will compare against.
	// Declare my queue(s) for keeping track of jobs.
	int runLeft[100];
	int firstRun[100];
	int finish[100];
	// Declare my variable for keeping track of numbers/times/clocks
	int clk, nclk = 0, jobQ = 0, pick = 0, i = 0, j = 0, debt = 0;
	
	// start doing calculations.
	for (i; i < count; i++;){
		// set the clock to current/submitted job. Add job to que along with required time
		clk = submit_q[i];;
		runLeft[i] = reqRunTime[i]; 
		jobQ++; // a new job has shown up, add it to the Q
		j = 0;
		
		// look ahead for next clock
		if ((i + 1) >= count) {
			// We must be at the end of our process list.
			// We will do addition to the clock instead.
			while (jobQ > 0){
				j = 0;
				// Pick shortest job from jobQ
				while (runLeft[j] == 0 && j <= i) j++;
				pick = i;
				while (runLeft[pick] == 0 && pick > j) pick--;
				for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
				// Check if job has run yet (get 1st run)
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
				// move clock forward
				clk += runLeft[pick];
				// job is done
				finish[pick] = clk;
				runLeft[pick] = 0;
				jobQ--;
			}
		}
		else {
			// we can use next process time
			nclk = reqRunTime[i + 1];
			// calc time difference
			debt = nclk - clk;
			
			// Pick shortest job from jobQ
			while (runLeft[j] == 0 && j <= i) j++;
			pick = i;
			while (runLeft[pick] == 0 && pick > j) pick--;
			for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
			// pick has been set.
			// Check if job has run yet (get 1st run)
			if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
			
			
			// check, negative or zero, a job has finished, another job can run before next job shows up.
			if ((debt - runLeft[pick]) <= 0){
				// if runLeft[pick] == 0, job finsihed.
				// update finish times
				if ((debt - runLeft[pick]) == 0) {
					finish[pick] = clk + debt;
					jobQ--;
				}
				else runLeft[pick] = (debt - runLeft[pick]) * -1;
			}
			// check, positive. Remaing time left before next job
			else {
				// positive time lift, picked job has finished before next clock/job arrival.
				// set finish time
				finish[pick] = clk + runLeft[pick];
				jobQ--;
				clk += runLeft[pick];
				debt -= runLeft[pick];
				// set runleft = 0
				runLeft[pick] = 0;
				
				
				// run any other remaining jobs if any
				while (jobQ > 0 && debt >= 0){
					// Get next shortest job
					j = 0;
					while (runLeft[j] == 0 && j <= i) j++;
					pick = i;
					while (runLeft[pick] == 0 && pick > j) pick--;
					for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
					// we have next job.
					// check if it has been run yet. Set start time
					if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
					// check if job run time exceeds nextclock
					if ((debt - runLeft[pick]) <= 0){
						// if runLeft[pick] == 0, job finsihed.
						// update finish times
						if ((debt - runLeft[pick]) == 0) {
							finish[pick] = clk + debt;
							jobQ--;
						}
						else {
							runLeft[pick] = (debt - runLeft[pick]) * -1;
							break; // we clearly have a gap in processes
						}
					}
					else {
						// else, current processes will end before nextclock
						// set finish time for process
						finish[pick] = clk + runLeft[pick];
						// move clk forward
						clk += runLeft[pick];
						// decrement jobQ
						jobQ--;
						// calc debt
						debt -= runLeft[pick];
						// set runLeft time
						runLeft[pick] = 0;
					}
				}
			}
		}
	}
	
	// Lets round up all the stats and output to terminal
	i = 0;
	j = 0;
	for (i; i < count; i ++) {
		printf("submit: %d\treqRun: %d\t1stRun: %d\tfinish: %d\n", submit_q[i], reqRunTime[i], firstRun[i], finish[i]);
		
	}
}
		
		
		
		
		
		
		
		
		
		
		/*
		
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
*/


void RoundRobin(int *reqRunTime, int *submit_q, int count){
	// todo
}