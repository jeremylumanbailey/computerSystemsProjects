/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <fcntl.h>


 // #define PORT "8570"  // the port users will be connecting to



#define BACKLOG 10	 // how many pending connections queue will hold

//Jeremy added this
#define MAXDATASIZE 50 // max number of bytes we can get at once 



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
	char *D;

	int PORT = strtol(argv[1], &D, 10);		

	if(PORT == -1) {
		exit(1);
	}

	 int numbytes;
	 char stringFromClient[MAXDATASIZE];
	//will return -1 if cant open 
	// int fd = open(argv[3], O_RDWR);

	// MAKE SURE PORT IS WITHIN SPECIFIED RANGE

	if(PORT < 50000 || PORT > 60000) {
		fprintf(stderr,"Port out of range \n");
	    exit(1);
	}


	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	int yes=1;

	char s[INET6_ADDRSTRLEN];
	int rv;

		if (argc != 2) {
	    fprintf(stderr,"Need port argument\n");
	    exit(1);
	}



	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server: waiting for connections...\n");

    int PID;

	while(1) {  // main accept() loop
	
       
        sin_size = sizeof their_addr;
		
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}//	wait(NULL);
        PID = fork();


        //if statement is child function, else is parent function

        /* everything inside if(PID ==0) statement could be put into a separate child function childFun() */
        if(PID == 0) {
		    inet_ntop(their_addr.ss_family,
			    get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		    printf("server: got connection from %s\n", s);

	/////////////////////////////////////////////////////////////////

		    if ((numbytes = recv(new_fd, stringFromClient, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}

	 char arr[] = {'/','C','M','S','C','2','5','7'};
	// stringFromClient[0] = 'B';
	stringFromClient[numbytes] = '\0';

	printf("String from client:  %s\n",stringFromClient);

	//will return -1 if cant open 
	int fd = open(stringFromClient, O_RDWR, 0666);

	// printf("open return %d\n", fd);

	if(fd == -1) {
		printf("inside if statement %d\n", fd);
		if(send(new_fd, arr, 8, 0) == -1) {
			perror("send");
			exit(0);
		}
		close(new_fd);
		exit(0);
	}

	/* read() and send() in while loop, somewhere around here */

	int nread;
	
    char buffer[128];
    nread = read(fd, buffer, 50);
    while(nread > 0) {



	if(nread < 50) {
		send(new_fd,buffer,nread,0);
		send(new_fd,arr,8,0);
		break;
	}

	send(new_fd,buffer,nread,0);

	nread = read(fd, buffer, 50);

	}

	close(new_fd);
	exit(0);
	//while nread > 0

	//////////////////////////////////////////////////////////////////////////

		  //   if (send(new_fd, buffer, nread, 0) == -1)
				// perror("send");
    //         close(new_fd);
    //         exit(0);
        }
        // else { 
        //     close(new_fd);
        // }
	}

	return 0;
}


/*
close welcome socket
With Parent SIGINT: Loop, for each child, chill(child.pid, SIGUSR1;)

another loop, for each child, wait(NULL), exit(1);

1) Parent SIGINT
	{
	

		//we need 2 structs for newact and old act. leve oldact as NULL. newact you actually need to set the value
		//
	newact.sa_sigaction = sig_func;
	
	newact.sa_flags = SA_NOCLDWAIT | SA_SIGINFO;

	void sig_func(int signum, siginfo *info, *ucontext);

	info->si_pid;

	remove pid from pool.

	The "pool" meaning array[5].

	sigaction(SIGCHLD, &newact, &oldact);



	}

2) Parent SIGCHLD


3) Child SIGINT	
{
	sa_handler = IGN;

}
4) Child SIGCHLD
{
	sa_handler = SIG_DFL;
}

5) Child SIGUSER1

	{
	notify client close file
	close socket
	exxit
	}


*/