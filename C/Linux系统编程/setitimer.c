#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>


static int count=1;
static void signalHandler(int s)
{
    printf("Get a SIGALRM, %d counts!\n", count++);
}

int main()
{

    signal(SIGALRM, signalHandler);
    struct itimerval tick;
    tick.it_value.tv_sec = 1;
    tick.it_value.tv_usec = 0;
    tick.it_interval.tv_sec = 1;
    tick.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
        printf("Set timer failed!\n");
        
    while(1)
        pause();

    exit(0);
}
