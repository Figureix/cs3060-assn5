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
	int clk, nclk = 0, jobQ = 0, pick = 0, i = 0, j = 0, timeQ = 100, debug = 0;
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
		// set the clock to current/submitted job. Add job to queue along with required time
		clk = submit_q[i];		
		runLeft[i] = reqRunTime[i];
		jobQ++; // a new job has shown up, add it to the Q
		
		
		
		// Evaluate clock times and runtime
		// set nclk
		//if (i > 0) j++;
		if ((i + 1) < count) {
			nclk = submit_q[i + 1];
			
			printf("\n\n");
			for (debug; debug <= i; debug++)	printf("***165 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
			debug = 0;
			printf("\n\n");
			
			
			// is the timeQ sooner than the next job??
			while ((nclk - clk) >= timeQ && jobQ > 0) {
				// time between jobs is greater/equal to timeQ -- we can run 1 or more jobs before next job
				// use the timeQ
				// get the next job 
				// loop through runLeft array looking for job
				printf("171 while (runLeft[j % (i + 1)] == 0) j++;\n[runLeft[j % (i + 1)] == 0]:%d\n", runLeft[j % (i + 1)]);
				for (debug; debug <= i; debug++)	printf("172 %d\ti:%d\t j:%d\t clk:%d\t nclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
				debug = 0;
				//j++;
				if (i == 0){
					j = i;
				}else {
					while (runLeft[j] == 0) {
						j = (j + 1) % (i + 1);
						for (debug; debug <= i; debug++)	printf("180 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
						debug = 0;
					}
				}
				pick = j; // we should have the next job OR the last job that had ran -- no new jobs added to array
				//j++;
				// Check and set first run time
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
				
				// Do Maths
				// check if runLeft is greater than timeQ
				if (runLeft[pick] >= timeQ){
					runLeft[pick] -= timeQ;
					clk += timeQ; // move clock forward
					// timeQ expired, move to run next job
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}else j++;
					for (debug; debug <= i; debug++)	printf("198 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
				}else{
					// runLeft is less than timeQ
					// the job will finish within the timeQ
					// set finish time
					clk += runLeft[pick];
					finish[pick] = clk;
					runLeft[pick] = 0;
					jobQ--;
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}else j++;
					for (debug; debug <= i; debug++)	printf("211 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
				}
			}
			// time between jobs is less than a timeQ
			while (clk < nclk && jobQ > 0){
				// get next job
				printf("218 while (runLeft[j % (i + 1)] == 0) j++;\t[runLeft[j % (i + 1)]:%d\n", runLeft[j % (i + 1)]);
				for (debug; debug <= i; debug++)	printf("219 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
				debug = 0;
				//j++;
				if (i == 0){
					j = i;
				}else {
					while (runLeft[j] == 0) {
						j = (j + 1) % (i + 1);
						for (debug; debug <= i; debug++)	printf("227 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
						debug = 0;
					}
				}
				pick = j; // we should have the next job OR the last job that had ran -- no new jobs added to array
				//j++;
				// check first run
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;

				// check if job runleft is greater than time till next job
				if (runLeft[pick] >= (nclk - clk)) {
					// update runLeft
					runLeft[pick] -= (nclk - clk);
					clk += (nclk - clk);
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}else j++;
					for (debug; debug <= i; debug++)	printf("244 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
					break; // clk += (nclk - clk); should also cause while loop to end
				}else {
					// runLeft is less than differnece between clks
					// the job will finsih
					clk += runLeft[pick];
					finish[pick] = clk;
					runLeft[pick] = 0;
					jobQ--;
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}else j++;
					for (debug; debug <= i; debug++)	printf("257 %d\ti:%d\t j:%d\t clk:%d\tnclk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, nclk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
				}
			}
		}else {
			// there is no nclk, we must be at the end of job list
			while (jobQ > 0){
				// get next job
				printf("\n\n");
				for (debug; debug <= i; debug++)	printf("***271 %d\ti:%d\t j:%d\t clk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", debug, i, j, clk, runLeft[debug], reqRunTime[debug], jobQ, pick);
				debug = 0;
				printf("\n\n");
				//j++;
				if (i == 0){
					j = i;
				}else {
					while (runLeft[j] == 0) {
						j = (j + 1) % (i + 1);
						printf("173 j:%d\n", j);
					}
				}
				pick = j; // we should have the next job OR the last job that had ran -- no new jobs added to array
				//j++;
				printf("i:%d\tpick:%d\tjobQ:%d\t\tclk:%d\n", i, pick, jobQ, clk);
				// check first run
				if (runLeft[pick] == reqRunTime[pick]) firstRun[pick] = clk;
				
				// check, is runleft > timeQ
				if (runLeft[pick] >= timeQ) {
					// update runLeft
					runLeft[pick] -= timeQ;
					// update clk
					clk += timeQ;
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}
					for (debug; debug <= i; debug++)	printf("292 i:%d\t j:%d\t clk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", i, j, clk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
				}else {
					clk += runLeft[pick];
					finish[pick] = clk;
					runLeft[pick] = 0;
					jobQ--;
					if (i > 0) {
						j = (j + 1) % (i + 1);
					}
					for (debug; debug <= i; debug++)	printf("302 i:%d\t j:%d\t clk:%d\t runLeft[i]:%d\t reqRunTime[i]:%d\t jobQ:%d\t pick:%d\n", i, j, clk, runLeft[debug], reqRunTime[debug], jobQ, pick);
					debug = 0;
				}
				
				
			}
			
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

