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
//number of processes is half of i
int count = i;

//start with first come first serve
//FCFS(run_time, ready_q_add, count);

	return 0;
}



//first come first served routine
void FCFS(int *run_time, int *ready_q_add, int count)
{
int ready_q[count];
int process_run_time[count];
int last_job = 0, current_job = 0;
int clock = 0, job_submit_time = 0;
int response = 0, wait_time = 0, turn_around = 0;

//print header
printf("First Come First Served\n");

//run jobs until there are no more left
while( current_job < count)
{

//check for idle time
if((ready_q_add[last_job] > clock) && (clock < ready_q_add[current_job]))
{
//printf("idle time\n");
clock = ready_q_add[last_job];
//current_job = 0;
//last_job = 0;
}

//if the next job is less then the clock, add it to the ready q
if((ready_q_add[last_job] <= clock))
{
//printf("%d\n", last_job);
ready_q[last_job] = ready_q_add[last_job];
process_run_time[last_job] = run_time[last_job];
//printf("%d\n", ready_q[last_job]);
last_job ++;
}

//if there are jobs in the queue, process them
if(last_job > 0)
{
	//move the start clock to the time that the current job was added to the ready q
	int first_run = clock;// + ready_q[current_job];
	
	//advance the clock to the end of the job
	clock = process_run_time[current_job] + clock;
	
	//set the end clock to the time when the process will complete
	job_submit_time = ready_q[current_job];
	
	//compute stats
	response = (response + (first_run - job_submit_time));
	turn_around = (turn_around + (clock - job_submit_time));
	wait_time = (wait_time + ((clock - job_submit_time) - run_time[current_job]));
	//printf("	%d	%d	%d\n", response, turn_around, wait_time);

	//clear the process form the q
	ready_q[current_job] = 0;
	process_run_time[current_job] = 0;
	current_job++;
}

};
//print results
printf("Avg Resp: %d.%d Avg T.A. %d.%d Avg Wait: %d.%d\n", response/count, response%count, turn_around/count, turn_around%count, wait_time/count, wait_time%count);
}


//shortest job first routine
void SJF(int *run_time, int *ready_q_add, int count)
{
int ready_q[count];
int process_run_time[count];
int last_job = 0, current_job = 0;
int clock = 0, job_submit_time = 0;
int response = 0, wait_time = 0, turn_around = 0;
int out_of_order = 0, temp_clock = 0;
int index = -1;

//print header
printf("\nShortest Job First\n");

//run jobs until there are no more left
for(int j = 0; j <= count-1; j++)
{


//check for idle time
if((ready_q_add[last_job] > clock) && (clock < ready_q_add[current_job]))
{
clock = ready_q_add[last_job];
}

//if the next job is less then the clock, add it to the ready q
while((ready_q_add[last_job] <= clock))
{
ready_q[last_job] = ready_q_add[last_job];
process_run_time[last_job] = run_time[last_job];
last_job ++;
//printf("%d\n", last_job);
}

//if there are jobs in the queue, find the one with the least amount of time remaining and process it
if(last_job > 0)
{
index = current_job;
int temp = last_job-1;
	//find which job on the q has the shortest run time
	for(int i = 0; i <= count-1; i++)
	{
		
printf("%d " , process_run_time[i]);
		//if the ith index has a smaller run time then the current job, make that job the current job
		if((process_run_time[i] < 1000) && process_run_time[i] > 0)
		{
		
			//printf("\n	%d	%d", process_run_time[i], process_run_time[current_job]);
		current_job = i;
		temp = i;
		}

	}
printf("\n");

	//move the start clock to the time that the current job was added to the ready q
	int first_run = clock;
printf("%d ", clock);
	//advance the clock to the end of the job
	clock = process_run_time[current_job] + clock;
	
	//set the end clock to the time when the process will complete
	job_submit_time = ready_q[current_job];
	
	//compute stats
	response = response + (first_run - job_submit_time);
//printf("%d", response);
	turn_around = turn_around + (clock - job_submit_time);
//printf("	%d", turn_around);
	wait_time = (wait_time + ((clock - job_submit_time) - run_time[current_job]));
//printf("		%d", wait_time);



	//clear the process form the q
	ready_q[current_job] = 0;
	process_run_time[current_job] = 0;
	current_job = index+1;


}

};

//print results
printf("Avg Resp: %d.%d Avg T.A. %d.%d Avg Wait: %d.%d\n", response/count, response%count, turn_around/count, turn_around%count, wait_time/count, wait_time%count);

}
