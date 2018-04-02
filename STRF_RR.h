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
	int clk, nclk = 0, jobQ = 0, pick = 0, i = 0, j = 0;
	double TAav = 0, Waitav = 0, Respav = 0;
	
	// set all entries in arrays to zero
	for (i; i < count; i++){
		runLeft[i] = 0;
		firstRun[i] = 0;
		finish[i] = 0;
		TA[i] = 0;
		Wait[i] = 0;
		Resp[i] = 0;
	}
	i = 0; // reset i
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
	
	for (i; i < count; i++) {
		TA[i] = finish[i] - submit_q[i];
		Wait[i] = TA[i] - reqRunTime[i];
		Resp[i] = firstRun[i] - submit_q[i];
		TAav += TA[i];
		Waitav += Wait[i];
		Respav += Resp[i];
	}
	TAav = TAav / i;
	Waitav = Waitav / i;
	Respav = Respav / i;
	printf("TA(avg):%.2f\t\tWait(avg):%.2f\t\tResp(avg):%.2f\n", TAav, Waitav, Respav);
}
	

void RoundRobin(int *reqRunTime, int *submit_q, int count){
	// my arrays are essentially constatns that I will compare against.
	// Declare my queue(s) for keeping track of jobs.
	int runLeft[100];
	int firstRun[100];
	int finish[100];
	int TA[100];
	int Wait[100];
	int Resp[100];
	// Declare my variable for keeping track of numbers/times/clocks
	int clk, nclk = 0, jobQ = 0, pick = 0, i = 0, j = 0, timeQ;
	double TAav = 0, Waitav = 0, Respav = 0;
	
	// set all entries in arrays to zero
	for (i; i < count; i++){
		runLeft[i] = 0;
		firstRun[i] = 0;
		finish[i] = 0;
		TA[i] = 0;
		Wait[i] = 0;
		Resp[i] = 0;
	}
	i = 0; // reset i
	
	// Evaluate job completion vs time quantum
	// get nclk
	// loop through numbers, and set clock as needed
	for (i; i < count; i++){
		// set the clock to current/submitted job. Add job to que along with required time
		clk = submit_q[i];		
		runLeft[i] = reqRunTime[i];
		jobQ++; // a new job has shown up, add it to the Q
		timeQ = 100;
		// Evaluate clock times and runtime
		// set nclk
		if ((i + 1) < count) {
			nclk = submit_q[i + 1];
			// is the timeQ sooner than the next job??
			while ((nclk - clk) > timeQ && jobQ > 0) {
				// time between jobs is greater than timeQ
				// use the timeQ
				// get the next job 
				// loop through runLeft array looking for job
				while (runLeft[j % (i + 1)] == 0 && jobQ > 0) j++;
				pick = j; // we should have the next job OR the last job that had ran -- no new jobs added to array

				// Check and set first run time
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
				
				// Do Maths
				// check if runLeft is greater than timeQ
				if (runLeft[pick] > timeQ){
					runLeft[pick] -= timeQ;
					clk += timeQ; // move clock forward
				}else{
					// runLeft is less than timeQ
					// the job will finish within the timeQ
					// set finish time
					clk += runLeft[pick];
					finish[pick] = clk;
					runLeft[pick] = 0;
					jobQ--;				
				}
			}
			// time between jobs is less than a timeQ
				
				
				
				// Set runLeft
				runLeft[pick] = clk;
				clk += timeQ - runLeft[pick];
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

