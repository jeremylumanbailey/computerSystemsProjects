////////////////////////////////////////////////////////////////////////////////
//
//  File          : client.c
//  Description   : Client file for assignment 5 of CMSC-257.
//                  
//
//  Author        : Jeremy Bailey
//  Created       : April 2019
//

//Imported files and libraries for client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>


//127.0.0.1 = localhost
#define MAXDATASIZE 50 // max number of bytes we can get at once 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : *get_in_addr
// Description  : get_in_addr() gets socket address for IPv4 or IPv6
//
// Inputs       : sockaddr *sa
// Outputs      : returns struct for IPv6 or IPv4
////////////////////////////////////////////////////////////////////////////////

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : This is the main function for the cmsc257 assignment 5 client side program.
//
// Inputs       : none
// Outputs      : 0 if successful, -1 otherwise
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	//Check that user enters in all required arguments.
	if (argc != 4) {
	    fprintf(stderr,"Not enough arguments: [IP] [PORT] [FILENAME]\n");
	    exit(1);
	}

	//Create local file that client will be downloading from server
	// will return -1 if can't create 
	int fd = open(argv[3], O_RDWR | O_CREAT, 0666); 

	//Check that file was created
	if (fd == -1) {
		fprintf(stderr,"Could not create file. closing program\n");
		exit(1);
	}
	
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	//Pass in IP and port for server that client wishes to connect to
	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	//Walk through until available socket is found. 
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
	//When socket is found try to connect until connection is established.
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("client: connect");
			close(sockfd);
			continue;
		}

		break;
	}
	//No open socket on IP and port was found
	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure

	//Send filename to server
	if (send(sockfd, argv[3], 50, 0) == -1) {
		perror("send");
		exit(1);
	}

	//Loop for receiving bytes from server
	while(1) { 

	//Receive data
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}

	//Everything that has been sent is recieved
	buf[numbytes] = '\0';

	//If string terminator is a substring of the recieved data, write the last bit and break out of loop
	if(strstr(buf, "/CMSC257")) {
		write(fd, buf, strlen(buf)-8);
		break;
	}

	//Write data to file
	write(fd, buf, strlen(buf));

	}

	//Close socket
	close(sockfd);

	return 0;
}

