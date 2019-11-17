#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define true 1
#define false 0

sem_t TobaccoAndPaper;
sem_t PaperAndMatches;
sem_t MatchesAndTobacco;
sem_t DoneSmoking;

void smoke(char *c)
{
    printf("%s Smoked Cigarette\n", c);
}

void *agent()
{
    while (true)
    {
        sem_wait(&DoneSmoking);
        int r = rand() % (3);
        // Signal which ever combination was chosen.
        switch (r)
        {
        case 0:
            sem_post(&TobaccoAndPaper);
            printf("Agent Produced: Tobacco and Paper\n");
            sleep(1);
            break;
        case 1:
            sem_post(&PaperAndMatches);
            printf("Agent Produced: Paper and Matches\n");
            sleep(1);
            break;
        case 2:
            sem_post(&MatchesAndTobacco);
            printf("Agent Produced: Matches and Tobacco\n");
            sleep(1);
            break;
        }
    }
}

void *Smoker_A()
{
    while (true)
    {
        // Wait for our two ingredients
        sem_wait(&TobaccoAndPaper);
        smoke("A");
        sleep(1);
        sem_post(&DoneSmoking);
    }
}

void *Smoker_B()
{
    while (true)
    {
        // Wait for our two ingredients
        sem_wait(&PaperAndMatches);
        smoke("B");
        sleep(1);
        sem_post(&DoneSmoking);
    }
}

void *Smoker_C()
{
    while (true)
    {
        // Wait for our two ingredients
        sem_wait(&MatchesAndTobacco);
        smoke("C");
        sleep(1);
        sem_post(&DoneSmoking);
    }
}

int main()
{
    // Seed our random number since we will be using random numbers
    srand(time(0));

    // Initialize semaphores
    sem_init(&DoneSmoking, 0, 1);
    sem_init(&TobaccoAndPaper, 0, 0);
    sem_init(&MatchesAndTobacco, 0, 0);
    sem_init(&PaperAndMatches, 0, 0);

    // Create Threads
    pthread_t t1, t2, t3, t4;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&t4, &attr, agent, NULL);
    pthread_create(&t1, &attr, Smoker_A, NULL);
    pthread_create(&t2, &attr, Smoker_B, NULL);
    pthread_create(&t3, &attr, Smoker_C, NULL);

    pthread_join(t4, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    return 0;
}