#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"

#define CHILD 0
#define NumOfPlacementAttempt 10

// create random number with min and max bound
int Grand(int min, int max)
{
    return rand() % max + min;
}

int main()
{
    int smoker_match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int smoker_paper = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int smoker_tobacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int run = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

    sem_create(agent, 1);
    sem_create(smoker_match, 0);
    sem_create(smoker_paper, 0);
    sem_create(smoker_tobacco, 0);
    sem_create(run, 1);

    srand(time(NULL));
    int randNum = 0;
    int pid, pid1, pid2, pid3;
    int status;

    pid = fork();

    if (pid == CHILD)
    {
        int index = 0;
        do
        {
            index++;
            randNum = Grand(1, 3); // Pick a random number from 1-3
            if (randNum == 1)
            {
                // Put tobacco on table
                // Put paper on table
                printf("Agent put's tobacco and paper on the table\n");
                V(smoker_match); // Wake up smoker with match
            }
            else if (randNum == 2)
            {
                // Put tobacco on table
                // Put match on table
                printf("Agent put's tobacco and match on the table\n");
                V(smoker_paper); // Wake up smoker with paper
            }
            else
            {
                // Put match on table
                // Put paper on table
                printf("Agent put's match and paper on the table\n");
                V(smoker_tobacco);
            }         // Wake up smoker with tobacco
            P(agent); //  Agent sleeps
            sleep(1);

            if (index == NumOfPlacementAttempt)
                run = 0;
        } while (index < NumOfPlacementAttempt);
    } //

    else
    {
        pid1 = fork();

        if (pid1 == CHILD)
        {
            int index = 0;
            do
            {
                P(smoker_match);
                ++index;
                printf("Smoker1 pick up tobacco and paper\n");
                // Pick up tobacco
                // Pick up paper
                V(agent);
            } while (run);
        }

        else
        {
            pid2 = fork();
            if (pid2 == CHILD)
            {
                int index = 0;
                do
                {
                    P(smoker_paper);
                    ++index;
                    printf("Smoker2 pick up tobacco and match\n");
                    // Pick up match
                    // Pick up tobacco
                    V(agent);
                } while (run);
            }
            else
            {
                pid3 = fork();
                if (pid3 == 0)
                {
                    int index = 0;
                    do
                    {
                        P(smoker_tobacco);
                        ++index;
                        printf("Smoker3 pick up paper and match\n");
                        // Pick up match
                        // Pick up paper
                        V(agent);
                    } while (run);
                }

                else
                    wait(&status);
            }
        }
    }
}