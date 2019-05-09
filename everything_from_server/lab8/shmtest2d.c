#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int (*mem);

////////////////////////////////////////////////////////////////////
//
//          parent_fun()
//
///////////////////////////////////////////////////////////////////
    void parent_fun(int pid) {

    printf("parent (inside fun): new child is %d\n", pid);

    }

/////////////////////////////////////////////////////////////////
//
//       child_fun()
//
/////////////////////////////////////////////////////////////////

    void child_fun(int i, int n) {

    usleep(1000);
    printf("child %d, parent is %d\n", i, getppid());
	mem[i*n+i] = mem[i*n+i] * mem[i*n+i];
    exit(mem[i*n+i]);
    }


int main ( int argc, char **argv ) {
	int n,i, pid, kids, shmfd;
     
	kids = argc > 1 ? atoi(argv[1]) : 5; //Number of kids created
	n = argc > 2 ? atoi(argv[2]) : 5; //Number of columns for the 2-d array
	shmfd = shm_open ( "/baileyj6_memory", O_RDWR | O_CREAT, 0666 );
	if ( shmfd < 0 ) {
		fprintf(stderr,"Could not create brs_memory\n");
		exit(1);
	}
	
	ftruncate ( shmfd, n*n*sizeof(int));
	
	mem = (int (*))mmap ( NULL, (kids*n)*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0 );
	if ( mem == NULL ) {
		fprintf(stderr,"Could not map brs_memory\n");
		exit(1);
	}
	
	close ( shmfd );
	shm_unlink ( "/bailyj6_memory" );

	for ( i = 0; i < kids; i++ ) {
		mem[i*n+i] = i+1;
}	for ( i = 0; i < kids; i++ ) {
		pid = fork();
		if ( pid < 0 ) {
			fprintf(stderr,"fork failed at %d\n",i);
			exit(1);
		} else if ( pid > 0 ) {

            parent_fun(pid);
	//		printf("parent: new child is %d\n",pid);
		} else {
                child_fun(i,n);
	//		usleep ( 1000 );
	//		printf("child %d, parent is %d\n",i, getppid());
	//		mem[i*n+i] = mem[i*n+i] * mem[i*n+i];
	//		exit(0);
		}
  	}
	
	for ( i = 0; i < kids; i++ ) { 
	      int exit_status;
        //exit() waits for process to change state
        wait(&exit_status);

        if(exit_status > 0) {
            //WEXITSTATUS() returns the exit status of the child.
            //WEXITSTATUS() is under wait() man page
            printf("Exit status of child is: %d\n",WEXITSTATUS(exit_status));
//not doing the %d causes seg fault. but why?!
        }
    }

	for ( i = 0; i < kids; i++ ) 
		printf("mem[%d] = %d\n",i*n+i,mem[i*n+i]);
	
	return 0;
}
