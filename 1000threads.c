#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define NUM_THREADS 1000

void *thf_thousand_inc(void *args);

unsigned int a = 0;

int main(void)
{
    int i = 0;
    int ret = 0;
    unsigned int status[NUM_THREADS] = { 0 };
    pthread_t tid[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
    {
        ret = pthread_create(&tid[i], NULL, &thf_thousand_inc, NULL);
        if (0 != ret)
        {
            errno = ret;
            perror("Error pthread_create(...)");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        ret = pthread_join(tid[i], NULL);
        if (0 != ret)
        {
            errno = ret;
            perror("Error pthread_join(...)");
            exit(EXIT_FAILURE);
        }
        //printf("Thread %d joined.\n", i);
    }

    printf("Value  a = %d\n", a);

    return 0;
}

void *thf_thousand_inc(void *args)
{
    static unsigned int tmp;

    for (int i = 0; i < 1000; i++)
    {
        tmp = a;
        tmp = tmp + 1;
        a = tmp;
    }

    return 0;
}

