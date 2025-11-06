#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid > 0)
	{
		printf("CHILD PROCESS PID: %d\n", pid);
		printf("I AM PARENT PROCESS PID: %d\n", getpid());
		printf("I AM PARENT AND WILL GO TO SLEEP\n");
		sleep(5);
		printf("I WAS SLEEPING AND WOKE UP AFTER 5 SECONDS\n");
	}
	else if(pid == 0)
	{
		printf("I AM CHILD PROCESS AND EXITING\n");
		exit(0);
	}
	else
	{
		printf("FORK FAILED\n");
		return 1;
	}
	return 0;
}
