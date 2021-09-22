#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM 20
static int count=0;
static pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

static void * func_add(void* p)
{
    pthread_mutex_lock(&mut);
    count++;
    pthread_mutex_unlock(&mut);
    pthread_exit(NULL);
}


int main()
{
    int err;
    pthread_t threads[NUM];
    count=0;
    for(int i=0; i<NUM; i++)
    {
        err=pthread_create(&threads[i],NULL,func_add,NULL);
        if(err)
        {
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(0);
        }
    }
    for(int i=0; i<NUM; i++)
    {
        pthread_join(threads[i],NULL);

    }
    pthread_mutex_destroy(&mut);
    printf("%d\n",count);
    exit(0);
}
