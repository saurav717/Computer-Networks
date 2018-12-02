#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char**argv)
{
		/* the size (in bytes) of shared memory object */
	int SIZE = 4096;
		/* name of the shared memory object */
	const char *name = "OS";

	int shm_fd;

	struct timeval *start, end;	
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd, SIZE);
	
	start = (struct timeval *)mmap(0, SIZE,PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	pid_t pid;
	pid = fork();
	

	if (pid < 0) 
	{ 	
		cout  << " fork failed\n"; 		
		return 1;	
	}	

	else if (pid == 0)
	{ 	/* child process */
		gettimeofday(start, NULL);	
		execvp(argv[1] , argv + 1);	
			
	}
	
	else 
	{	/* parent process */
		/* parent will wait for the child to complete */

		wait(NULL);
		gettimeofday(&end, NULL);
		float end_utimes=  (end.tv_usec - start->tv_usec)/1000000.0;
		float end_timeS = (end.tv_sec - start->tv_sec);
		float total_time = end_timeS + end_utimes;
		cout << end_utimes;
	}
}

