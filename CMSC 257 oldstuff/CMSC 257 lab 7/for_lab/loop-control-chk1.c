// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include "lab3header.h"

/* loop-control-chk1.c - This program requests a positive integer. Functionalities include
reversing a number, determining if the number is even or odd, and determining if the number is
prime. */
int main(int argc, char *argv[]) {
	char ch = 'N'; /* variable to accept the user's choice, N represents the condition not to exit from the program */
	int num; /* variable to accept a number */
	while( (ch != 'Y') && (ch != 'y') ) {
		printf("Enter R to reverse the digits of the number \n");
		printf("Enter E to determine if the number is even or odd \n");
		printf("Enter P to determine if the number is prime \n");
		printf("Enter Y or y to exit the program\n");
		printf("Enter your choice: ");
		/*The fflush() function writes any buffered data for the stream specified by the 
		stream parameter and causes any unwritten data for that stream to be written to the file. 
		In this case, the stream parameter 'stdin' takes input from the prompt. */
		fflush(stdin);
		scanf("\n%c", &ch);
		switch(ch) {
			case 'R':
			case 'r':
				printf("Enter the number to be reversed:\n");
				scanf("%d", &num);
				break;
			case 'E':
			case 'e':
				printf("Enter the number to check if it is even or odd:\n");
				scanf("%d", &num);
				break;
			case 'P':
			case 'p':
				printf("Enter the number to check if it is prime or not:\n");
				scanf("%d", &num);
				break;
			case 'Y':
			case 'y':
				printf("Exiting the program.\n");
				break;
			default:
				printf("You have entered a wrong choice. Try again\n");
				break;
		} /* switch */
	} /* while */
return(0);
} /* main */
