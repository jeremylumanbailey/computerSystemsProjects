////////////////////////////////////////////////////////////////////////////////
//
//  File          : server.c
//  Description   : Main server file for assignment 5 of CMSC-257.
//                  
//
//  Author        : Jeremy Bailey
//  Created       : April 2019
//

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

#define BACKLOG 5	 // how many pending connections queue will hold
#define MAXDATASIZE 50 // max number of bytes we can send at once 

//Global variables
int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
int numKids = 0; 
int kids[] = {0, 0, 0, 0, 0};
char terminator[] = {'/', 'C', 'M', 'S', 'C', '2', '5', '7'};
char s[INET6_ADDRSTRLEN];
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr; // connector's address information
int numbytes;
char stringFromClient[MAXDATASIZE];

////////////////////////////////////////////////////////////////////////////////
//
// Function     : intfunc
// Inputs       : signum
// Description  : intfunc() allows the parent to terminate 
//				  children and properly shutdown. 
//
// Outputs      : none
////////////////////////////////////////////////////////////////////////////////

void intfunc(int signum)
{

    int j;
    printf("	intfunc fired! Exiting server!\n");
    close(sockfd);
    //notify children
    for(j = 0; j < 5; j++)
    {
        if(kids[j] != 0)
        {
            kill(kids[j], SIGUSR1);
            numKids++;
        }
    }
    for(j = 0; j < numKids; j++)
    {
        wait(NULL);
    }

    exit(1);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : chldfunc
// Inputs       : signum, siginf0_t *info, *ucontext
// Description  : chldfunc() allows the server to remove processes from the pool.
//
// Outputs      : none
////////////////////////////////////////////////////////////////////////////////

void chldfunc(int signum, siginfo_t *info, void *ucontext)
{
   
    int pid = info->si_pid;

    int k;

    for(k = 0; k < 5; k++)
    {
        if(kids[k] == pid)
        {
            kids[k] = 0;
            break;
        }
    }

    waitpid(pid, NULL, 0);

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : usr1func
// Inputs       : signum
// Description  : usr1func() allows the child to properly shut 
//				  down when the parent terminates them.
//
// Outputs      : none
////////////////////////////////////////////////////////////////////////////////


void usr1func(int signum)
{
    printf("	usr1func fired! Exiting server!\n");
    
    if(send(new_fd, terminator, 8, 0) == -1)
    {
        perror("send");
        exit(1);
    }
    close(new_fd);
    exit(0);

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : *get_in_addr
// Inputs       : sockaddr *sa
// Description  : get_in_addr() gets socket address for IPv4 or IPv6
//
// Outputs      : returns struct for IPv6 or IPv4
////////////////////////////////////////////////////////////////////////////////

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : childProcess
// Inputs       : none
// Description  : childProcess() opens the file the client is requesting 
//				  and sends the bytes of the file to the client
//
// Outputs      : 0 if successful, -1 otherwise
////////////////////////////////////////////////////////////////////////////////

void childProcess()
{
	//Connection established  
    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
    printf("server: got connection from %s\n", s);

    //Receive filename 
    if ((numbytes = recv(new_fd, stringFromClient, MAXDATASIZE - 1, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }

    char arr[] = {'/', 'C', 'M', 'S', 'C', '2', '5', '7'};

    stringFromClient[numbytes] = '\0';

    printf("String from client:  %s\n", stringFromClient);

    //will return -1 if cant open
    int fd = open(stringFromClient, O_RDWR, 0666);

    //If server does not have file, send terminator string, close socket and kill process
    if(fd == -1)
    {
        printf("Client wanted file that server does not have. %d\n", fd);
        if(send(new_fd, arr, 8, 0) == -1)
        {
            perror("send");
            exit(0);
        }
        close(new_fd);
        exit(0);
    }

    int nread;

    char buffer[128];
    nread = read(fd, buffer, 50);


    //While there is data left 
    while(nread > 0)
    {

    	//If end of file is reached, send last of it and then send terminator string and break out of while()
        if(nread < 50)
        {
            send(new_fd, buffer, nread, 0);
            send(new_fd, arr, 8, 0);
            break;
        }
        //Send 50 bytes to client
        send(new_fd, buffer, nread, 0);

        //Read 50 bytes from file
        nread = read(fd, buffer, 50);

      // Testing purposes sleep(2);

    }

    //Close socket & kill child process
    close(new_fd);
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Inputs       : argc, *argv[]
// Description  : This is the main function for the cmsc257 assignment 5 server side program.
//
// Outputs      : 0 if successful, -1 otherwise
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

	//Set up signal handlers for parent processes
	struct sigaction intact, chldact;

	intact.sa_handler = intfunc;

	chldact.sa_sigaction = chldfunc;

	chldact.sa_flags = SA_NOCLDWAIT | SA_SIGINFO | SA_RESTART;

	sigaction(SIGINT, &intact, NULL);

	sigaction(SIGCHLD, &chldact, NULL);

	//Convert argument to int and check that it is valid
    char *D;

    int PORT = strtol(argv[1], &D, 10);

    if(PORT == -1)
    {
        exit(1);
    }

    //Checks that port is within range 
    if(PORT < 50000 || PORT > 60000)
    {
        fprintf(stderr, "Port out of range \n");
        exit(1);
    }

    socklen_t sin_size;
    int yes = 1;


    int rv;

    if (argc != 2)
    {
        fprintf(stderr, "Need port argument\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    int PID;

    while(1)    // main accept() loop
    {


        sin_size = sizeof their_addr;

        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }//	wait(NULL);

        PID = fork();

        //Child 
        if(PID == 0)
        {
        	//Set up signal handlers for child processes
	    	struct sigaction noact;

	    	noact.sa_handler = SIG_IGN;

	    	sigaction(SIGINT, &noact, NULL);

	    	sigaction(SIGCHLD, &noact, NULL);

	    	struct sigaction usr1act;

	    	usr1act.sa_handler = usr1func;

	    	sigaction(SIGUSR1, &usr1act, NULL);

            childProcess();
        }

        //Parent
        else
        {
        	//Close parent & add child to pool
            close(new_fd);
            int k;
            for(k = 0; k < 5; k++)
            {
                if(kids[k] == 0)
                {
                    kids[k] = PID;
                    break;
                }
            }
        }

    }

    return 0;
}

