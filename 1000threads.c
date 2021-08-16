#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define NUM_THREADS 1000

static void *thf_thousand_inc(void *args);

unsigned int a = 0;

int main(void)
{
    int i = 0;
    int ret = 0;
    void *res = NULL;
//    unsigned int status[NUM_THREADS] = { 0 };
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
        ret = pthread_join(tid[i], &res);
        if (0 != ret)
        {
            errno = ret;
            perror("Error pthread_join(...)");
            exit(EXIT_FAILURE);
        }

        if (NULL == res)
        {
            puts("Error pthread_join(..., &res), res = NULL");
            exit(EXIT_FAILURE);
        }

        printf("Thread %d joined. Return res = %u, address res: %p\n", i, *(int *)res,
                res);
        free(res);
    }

    printf("Value  a = %d\n", a);

    return 0;
}

void *thf_thousand_inc(void *args)
{
    unsigned int *pret = NULL;
    unsigned int tmp;

    for (int i = 0; i < 1000; i++)
    {
        tmp = a;
        tmp = tmp + 1;
        a = tmp;
    }

    pret = malloc(1 * sizeof(unsigned int));

    if (NULL == pret)
    {
        perror("Error malloc(...)");
        exit(EXIT_FAILURE);   
    }

    *pret = tmp;

    return pret;
}

