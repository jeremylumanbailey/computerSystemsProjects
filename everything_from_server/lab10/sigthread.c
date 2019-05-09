#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
int x = 0;
typedef struct data {
 char name[10];
 int age;
} data;

void sig_handler(int sig) {
  write(1, "Caught signal 11\n", 17);

}

void sig_handler2(int sig) {
    printf("sig_hander2 fired\n");
    x++;
    if(x >= 3) exit(1);

}

void sig_handler3(int sig) {
    printf("sig_hander3 fired\n");
}

void sig_func(data *p) {
     fprintf(stderr, "This is from thread function\n");
     strcpy(p->name,"Mr. Linux");
     p->age=30;
    // int x = 0;
    // while(x != 3) {

     select(1, NULL, NULL, NULL, NULL);
    // x++;
   //  sleep(2);
    // }
}

int main() {
     pthread_t tid;
     pthread_attr_t attr;
     data d;
     data *ptr = &d;

	 // Register signal handler before going multithread
     signal(SIGSEGV,sig_handler);

     struct sigaction new_action, old_action;
     new_action.sa_handler = sig_handler2;
     new_action.sa_flags = SA_NODEFER | SA_ONSTACK;

     sigaction(SIGINT, &new_action, &old_action);
	
     signal(SIGHUP, sig_handler3);

     pthread_attr_init(&attr);
     pthread_create(&tid,&attr,(void*)sig_func,ptr);
	 
   //  sleep(1); // Leave time for initialisation
     pthread_kill(tid,SIGSEGV);
   //  pthread_kill(tid,SIGINT);
     pthread_kill(tid,SIGHUP);
     pthread_join(tid,NULL);
	 
     fprintf(stderr, "Name:%s\n",ptr->name);
     fprintf(stderr, "Age:%d\n",ptr->age);
}
