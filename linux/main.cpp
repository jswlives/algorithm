#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

static void OnChildExit(int signal)
{
	int status = 0;
	pid_t pid = wait(&status);
	std::cout << "pid: " << pid << "exist status:" << status << "signal:" << signal << std::endl;
	sleep(1000);
}

int main()
{
	signal(SIGCHLD, OnChildExit);
	pid_t pid = fork();
	if (pid == 0)
	{
		std::cout << "this is in child" << std::endl;
		exit(1);
	}
	else
	{
		std::cout << "this is in father!" << std::endl;
		sleep(1000);
	}
	return 0;
}