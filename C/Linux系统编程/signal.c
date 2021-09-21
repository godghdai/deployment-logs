#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <signal.h>
#include <unistd.h>

int main2()
{

    time_t end;
    int64_t count=0;
    end=time(NULL)+5;
    while(time(NULL)<=end)
        count++;
    printf("%lld\n",count);
    exit(0);
}

static volatile int loop=1;
static void alrm_handler(int s)
{
    loop=0;
}

int main()
{
    int64_t count=0;

    alarm(5);
    signal(SIGALRM,alrm_handler);

    while(loop)
        count++;

    printf("%lld\n",count);
    exit(0);
}
