#include<stdio.h>
#include<signal.h>

void signal_handler( int no ) {
printf("Signals received : %d\n", no );
if ( no == SIGHUP ) {
printf( "Signal handler got a SIGHUP!\n" );
}
else if ( no == SIGINT ) {
printf( "Signal handler got a SIGNINT!\n" );
}
return;
}
void cleanup_handler( int no ) {
return; // Cleanup here
}
int main( void ) {
struct sigaction new_action, old_action; // Setup the signal actions
new_action.sa_handler = signal_handler;
new_action.sa_flags = SA_NODEFER | SA_ONSTACK;
sigaction( SIGINT, &new_action, &old_action );
signal( SIGHUP, signal_handler ); // Setup the signal handlers
signal( SIGTERM, cleanup_handler );
while (1) {
printf( "Sleeping ...zzzzz ....\n" );
select( 0, NULL, NULL, NULL, NULL );
printf( "Woken up!!\n" );
}
// Return successfully
return( 0 );
}
