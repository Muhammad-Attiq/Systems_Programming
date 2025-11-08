#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int num_children = 3;
	pid_t pid = 0;
	for(int i=0; i<num_children; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("child %d, with pid = %d running\n", i, getpid());
			
			exit(i+1);
		}
		else if(pid < 0)
		{
			perror("fork failed");
			exit(1);
		}
	}

	int status;
	pid_t child_pid;

	for(int i=0; i<num_children; i++)
	{
		int status;
		child_pid = waitpid(-1, &status, 0);
		if(WIFEXITED(status))
		{
			printf("parent: child with pid  %d exited with status %d\n", child_pid, WEXITSTATUS(status));
		}
	}
	return 0;
}
