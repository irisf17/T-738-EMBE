
// PART 2
// main.cpp

#include <pthread.h>
#include <stdint.h>
#include "increment.h"
#include "decrement.h"
#include "fifo.h"

pthread_t incrementTaskObj;
pthread_t decrementTaskObj;


pthread_mutex_t sharedVariableMutex;
int32_t gSharedVariable = 0;

int main(void)
{
/* Create the mutex for accessing the shared variable using the
* default attributes. */
    pthread_mutex_init(&sharedVariableMutex, NULL);
/* Create the increment and decrement tasks using the default task
* attributes. Do not pass in any parameters to the tasks. */
    pthread_create(&incrementTaskObj, NULL, incrementTask, NULL);
    pthread_create(&decrementTaskObj, NULL, decrementTask, NULL);
/* Allow the tasks to run. */
    pthread_join(incrementTaskObj, NULL);
    pthread_join(decrementTaskObj, NULL);
    return 0;
}

// increment.cpp


#include <unistd.h>
#include "increment.h"
#include <pthread.h>
#include "fifo.h"

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;

void *incrementTask(void *param)
{
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        gSharedVariable++;
        printf("Increment Task: shared var is %d\n", gSharedVariable);
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}

// decrement.cpp

void *decrementTask(void *param)
{
    while (1)
    {
        /* Delay for 7 seconds. */
        sleep(7);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        gSharedVariable--;
        printf("Decrement Task: shared var is %d\n",
        gSharedVariable);
        /* Release the mutex. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}


// header files

// increment.h
void *incrementTask(void *param);

// decrement.h
void *decrementTask(void *param);


// Part 2 & 3 
// MAKEfile

OBJECTS = main.o increment.o decrement.o fifo.o
SOURCE = src/main.cpp src/increment.cpp src/decrement.cpp src/fifo.cpp

all: $(OBJECTS)
        g++ $(OBJECTS) -lpthread -o output

main.o:
        g++ -c -lpthread src/main.cpp -I include

increment.o:
        g++ -c -lpthread src/increment.cpp -I include

decrement.o:
        g++ -c -lpthread src/decrement.cpp -I include
fifo.o:
        g++ -c -lpthread src/fifo.cpp -I include

clean:
        rm -f main.o increment.o decrement.o fifo.o  output


