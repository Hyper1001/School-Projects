#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int i; //integer used for "for loop" later on-
	pid_t pid; //creating a process
	pid=fork(); //forking the process
	if(pid != 0) //if this is a child then...
	{
		int status; 
		for(i=10;i>0;i--)//for loop that counts down from 10
		{
			printf("Time Remaining: %d seconds\n",i); //prints time left
			sleep(1);//stop everything for a second 
		}
		waitpid(pid,&status,NULL); //get parent to wait for process to complete
	}
	else
	{
		sleep(11); //wait 11 seconds while the others print.
		printf("Countdown Completed\n"); //Finished
	}
	return 0; //Exit program
}
