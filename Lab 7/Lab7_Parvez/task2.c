#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>

#define THREAD_NUM 4
#define NumOfPlacementAttempt 10

bool isrunning = true;

sem_t agent_semaphore;
sem_t smoker1_semaphore;
sem_t smoker2_semaphore;
sem_t smoker3_semaphore;

// create random number with min and max bound
int Grand(int min, int max)
{
    return rand() % max + min;
}

void *agent(void *args)
{
    srand(time(NULL));
    for (int i = 0; i < NumOfPlacementAttempt; ++i)
    {
        int randNum = 0;
        randNum = Grand(1, 3); // Pick a random number from 1-3
        if (randNum == 1)
        {
            // Put tobacco on table
            // Put paper on table
            printf("Agent put's tobacco and paper on the table\n");
            sem_post(&smoker1_semaphore);
        }
        else if (randNum == 2)
        {
            // Put tobacco on table
            // Put match on table
            printf("Agent put's tobacco and match on the table\n");
            sem_post(&smoker2_semaphore);
        }
        else
        {
            // Put match on table
            // Put paper on table
            printf("Agent put's match and paper on the table\n");
            sem_post(&smoker3_semaphore);
        }

        sem_wait(&agent_semaphore);
        sleep(1);
    } //

    isrunning = false;
    sem_post(&smoker1_semaphore);
    sem_post(&smoker2_semaphore);
    sem_post(&smoker3_semaphore);

    free(args);
}

void *smoker1(void *args)
{
    while (isrunning)
    {
        sem_wait(&smoker1_semaphore);
        if (isrunning)
        {
            printf("Smoker1 pick up tobacco and paper\n");
            sem_post(&agent_semaphore);
        }
    } //
    free(args);
}

void *smoker2(void *args)
{
    while (isrunning)
    {
        sem_wait(&smoker2_semaphore);
        if (isrunning)
        {
            printf("Smoker2 pick up tobacco and match\n");
            sem_post(&agent_semaphore);
        }
    } //
    free(args);
}

void *smoker3(void *args)
{
    while (isrunning)
    {
        sem_wait(&smoker3_semaphore);
        if (isrunning)
        {
            printf("Smoker3 pick up paper and match\n");
            sem_post(&agent_semaphore);
        }
    } //
    free(args);
}

int main()
{
    // init semaphores
    sem_init(&agent_semaphore, 0, 1);
    sem_init(&smoker1_semaphore, 0, 0);
    sem_init(&smoker2_semaphore, 0, 0);
    sem_init(&smoker3_semaphore, 0, 0);

    // create threads
    pthread_t th[THREAD_NUM];
    pthread_create(&th[0], NULL, &agent, NULL);
    pthread_create(&th[1], NULL, &smoker1, NULL);
    pthread_create(&th[2], NULL, &smoker2, NULL);
    pthread_create(&th[3], NULL, &smoker3, NULL);

    // join threads
    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    pthread_join(th[2], NULL);
    pthread_join(th[3], NULL);

    // destroy semaphore on end
    sem_destroy(&agent_semaphore);
    sem_destroy(&smoker1_semaphore);
    sem_destroy(&smoker2_semaphore);
    sem_destroy(&smoker3_semaphore);
}