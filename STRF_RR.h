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
	int TA[100];
	int Wait[100];
	int Resp[100];
	// Declare my variable for keeping track of numbers/times/clocks
	int clk, nclk = 0, jobQ = 0, pick = 0, i = 0, j = 0, debt = 0;
	
	// set all entries in arrays to zero
	for (i; i < count; i++){
		runLeft[i] = 0;
		firstRun[i] = 0;
		finish[i] = 0;
		TA[i] = 0;
		Wait[i] = 0;
		Resp[i] = 0;
	}
	i = 0;
	
	
	// start doing calculations.
	for (i; i < count; i++){
		// set the clock to current/submitted job. Add job to que along with required time
		clk = submit_q[i];		
		runLeft[i] = reqRunTime[i];
		jobQ++; // a new job has shown up, add it to the Q
		j = 0;
		// Pick a job
		while (runLeft[j] == 0 && j <= i) j++;
		pick = i;
		while (runLeft[pick] == 0 && pick > j) pick--;
		for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
		// We have picked a job
		// Check and set first run time
		if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
		// Evaluate clock times and runtime
		// set nclk
		if ((i + 1) < count) {
			nclk = submit_q[i + 1];
			if ((runLeft[pick] + clk) < nclk) {
				// Job can run before next job arrives
				// advance the clock
				clk += runLeft[pick];
				// set finish time
				finish[pick] = clk;
				runLeft[pick] = 0;
				jobQ--;
				// find another job while jobs is > 0 and clk < nclk
				while(jobQ > 0 && clk < nclk){
					// get next shortest job
					// Pick a job
					j = 0;
					while (runLeft[j] == 0 && j <= i) j++;
					pick = i;
					while (runLeft[pick] == 0 && pick > j) pick--;
					for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
					// check for first run
					if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
					// check if run goes past nclk
					if ((runLeft[pick] + clk) < nclk) {
						// update values
						clk += runLeft[pick];
						finish[pick] = clk;
						runLeft[pick] = 0;
						jobQ--;
					}else {
						// run time will overflow nclk
						runLeft[pick] = (runLeft[pick] + clk) - nclk;
						break;
					}
				}
			}else {
				// runLeft[pick] + clk is greater than nclk
				// job will run till next job arrives / preempts
				runLeft[pick] = (runLeft[pick] + clk) - nclk;
			}
		}else {
			// we are at the end of the job list
			do{
				clk += runLeft[pick];
				finish[pick] = clk;
				runLeft[pick] = 0;
				jobQ--;
				// get next job and check first run
				j = 0;
				while (runLeft[j] == 0 && j <= i) j++;
				pick = i;
				while (runLeft[pick] == 0 && pick > j) pick--;
				for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
				// check for first run
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
				
			}while (jobQ > 0);
		}
	}
	// gather statistics
	i = 0;
	j = 0;
	pick = 0;
	debt = 0;
	printf("\n\n\n");
	for (i; i < count; i++) {
		printf("174 submit: %d\treqRun: %d\t\t1stRun: %d\tfinish: %d\n", submit_q[i], reqRunTime[i], firstRun[i], finish[i]);
		TA[i] = finish[i] - submit_q[i];
		Wait[i] = TA[i] - reqRunTime[i];
		Resp[i] = firstRun[i] - submit_q[i];
	}
	i = 0;
	for (i; i < count; i++) {
		//printf("174 submit: %d\treqRun: %d\t\t1stRun: %d\tfinish: %d\n", submit_q[i], reqRunTime[i], firstRun[i], finish[i]);
		j += TA[i];
		pick += Wait[i];
		debt += Resp[i];
	}
	j = j / i;
	pick = pick / i;
	debt = debt / i;
	printf("TA(avg):%d\tWait(avg):%d\tResp(avg):%d\n", i, pick, debt);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	
	// start doing calculations.
	for (i; i < count; i++){
		// set the clock to current/submitted job. Add job to que along with required time
		clk = submit_q[i];
		runLeft[i] = reqRunTime[i]; 
		jobQ++; // a new job has shown up, add it to the Q
		j = 0;
		
		
		
		debug = 0;
		for (debug; debug <= i; debug++){
			printf("\nclk: %d \t nclk: %d \nrunLeft: %d \t jobQ: %d \t\t firstRun: %d \t finish: %d", clk, nclk, runLeft[debug], jobQ, firstRun[debug], finish[debug]);
			if (debug == i) {
				printf("\npick: %d\t debt: %d\t\n\n\n");
			}
			else printf("\n\n\n");
				
		}
		debug = 0;
		//printf("START OF FOR LOOP    runLeft: %d \t jobQ: %d \ti: %d \tclk: %d \treqRun: %d \n", jobQ, i, clk, runLeft[i], reqRunTime[i]);
		
		
		
		// look ahead for next clock
		if ((i + 1) >= count) {
			
			printf("\nIN (i + 1) >= count   \n");
			
			
			// We must be at the end of our process list.
			// We will do addition to the clock instead.
			while (jobQ > 0){
				j = 0;
				// Pick shortest job from jobQ
				while (runLeft[j] == 0 && j <= i) j++;
				pick = i;
				while (runLeft[pick] == 0 && pick > j) pick--;
				for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
				
				
				printf("IN END OF PROC   pick: %d \tjobQ: %d \ti: %d\tj: %d \tclk: %d \trunLeft: %d \t\n", pick, jobQ, i, j, clk, runLeft[pick]);
				
				
				
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
			
			
			printf("IN MID PROC\npick: %d    \tjobQ: %d\ti: %d\tj: %d\tclk: %d\trunLeft: %d\t\n", pick, jobQ, i, j, clk, runLeft[pick]);
			
			
			// check, negative or zero, a job has finished, another job can run before next job shows up.
			if ((debt - runLeft[pick]) <= 0){
				// if runLeft[pick] == 0, job finsihed.
				// update finish times
				
				
				printf("IN MID PROC/debt <= 0   pick: %d\tjobQ: %d\ti: %d\tj: %d\tclk: %d\trunLeft: %d\tfinish: %d\tdebt: %d\n", pick, jobQ, i, j, clk, runLeft[pick], finish[pick], (debt - runLeft[pick]));
				
				
				
				if ((debt - runLeft[pick]) == 0) {
					finish[pick] = clk + debt;
					jobQ--;
					
					
					printf("IN MID PROC/debt == 0   pick: %d\tjobQ: %d\ti: %d\tj: %d\tclk: %d\trunLeft: %d\tfinish: %d\tdebt: %d\n", pick, jobQ, i, j, clk, runLeft[pick], finish[pick], (debt - runLeft[pick]));
					
					
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
				
				
				printf("IN MID PROC/debt > 0   pick: %d\tjobQ: %d\ti: %d\tj: %d\tclk: %d\trunLeft: %d\tfinish: %d\tdebt: %d\n", pick, jobQ, i, j, clk, runLeft[pick], finish[pick], (debt - runLeft[pick]));
				
				
				// run any other remaining jobs if any
				while (jobQ > 0 && debt >= 0){
					// Get next shortest job
					j = 0;
					while (runLeft[j] == 0 && j <= i) j++;
					pick = i;
					while (runLeft[pick] == 0 && pick > j) pick--;
					for (j; j <= pick; j++) if (runLeft[j] < runLeft[pick] && runLeft[j] != 0) pick = j;
					// we have next job.
					
					
					printf("IN MID PROC/debt >>> 0   pick: %d\tjobQ: %d\ti: %d\tj: %d\tclk: %d\trunLeft: %d\tfinish: %d\tdebt: %d\n", pick, jobQ, i, j, clk, runLeft[pick], finish[pick], (debt - runLeft[pick]));
					
					
					
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
	printf("\n\n\n");
	for (i; i < count; i++) {
		printf("submit: %d\treqRun: %d\t1stRun: %d\tfinish: %d\n", submit_q[i], reqRunTime[i], firstRun[i], finish[i]);
		
	}
}
		
		
		
		
		*/
		
		
		
		
		
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