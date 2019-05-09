// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include "lab3header.h"

// Function Implementations

int reverse_number(int num)
{

while(num > 0) {
    printf("%d", num%10); num = num/10;
}

return 0;

}


int reverse_number_do_while(int num)
{

    do {
  printf("%d", num%10); num = num/10;
    }while(num > 0);

    return 0;

}


int even_odd(int num)
{

    if(num%2==0) {
        printf("Is even");
    }
    else {
        printf("is odd");
    }
    return 0;
}


int prime(int num)
{
    int i = 2;
    int flag = 0;
    for(i; i<=num/2;i++) {
        if(num%i == 0) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        printf("Number is prime\n");
    }
     else {
        printf("Number is not prime\n");
    }
    return 0;
}
