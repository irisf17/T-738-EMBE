
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




// PART3
// main.cpp
#include <pthread.h>
#include <stdint.h>
#include "increment.h"
#include "decrement.h"                            
#include "fifo.h"

pthread_t incrementTaskObj;
pthread_t decrementTaskObj;

Fifo f;

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
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "increment.h"
#include <pthread.h>
#include "fifo.h"

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;
extern Fifo f;
void *incrementTask(void *param)
{
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        if(!f.circular_is_full()){
                f.circular_put(gSharedVariable++);
                printf("Increment buffer: %d\n", gSharedVariable);
                printf("Number of items in buffer: %d\n", f.position);}
        else{
                printf("FIFO BUFFER is full \n");}
        //printf("Increment Task: shared var is %d\n", gSharedVariable);
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}

// decrement.cpp
#include <stdio.h>
#include <unistd.h>
#include "decrement.h"
#include <pthread.h>
#include <stdint.h>
#include <fifo.h>

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;
extern Fifo f;
void *decrementTask(void *param)
{
    while (1)
    {
        /* Delay for 7 seconds. */
        sleep(7);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        if(!f.circular_is_full()){
                f.circular_get();
                gSharedVariable--;
                printf("Decrement buffer: %d\n", gSharedVariable);
        }
        else{
                printf("FIFO BUFFER is full \n");}
        /* Release the mutex. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}

// fifo.cpp
#include <fifo.h>
#include <stdint.h>

Fifo::Fifo()
{
}
// ---- Fifo circular TESTING-----
int Fifo::circular_get()
{
    if (!circular_is_empty())
    {
        int32_t front = *head;
        head++;

        if (position > 0)
        {
            position--;
        }
        if (head == &buffer[0] + 5)
        {
            head = &buffer[0];
        }
        return front;
    }
return 0;
}

void Fifo::circular_put(int32_t item)
{
    *tail = item;
    if (head == tail && init != 0)
    {
        head++;
        if (head == &buffer[0] + 5)
        {
            head = &buffer[0];
        }
    }
    else
    {
        init = 1;
    }
    tail++;
    if (tail == &buffer[0] + 5)
    {
        tail = &buffer[0];
    }
    if (position < 5)
    {
        position++;
    }
}


bool Fifo::circular_is_empty()
{
    if (position < 0)
    {
        position = 0;
    }
    return position == 0;
}

bool Fifo::circular_is_full()
{
    return position == 5;
}

void Fifo::circular_reset()
{
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = 0;
    }
    position = 0;
}

// Header files
// increment.h
void *incrementTask(void *param);

// decrement.h
void *decrementTask(void *param);

// fifo.h
#ifndef FIFO_H
#define FIFO_H
#include <stdint.h>

const int FIFO_SIZE = 5;

class Fifo
{
public:
    Fifo();
    void test_normal_flow();
    void test_underflow();
    void test_overflow();
    void test_overwrite();

    int *head = buffer;
    int *tail = buffer;
    int init = 0;
    int circular_get();
    void circular_put(int32_t item);
    bool circular_is_empty();
    bool circular_is_full();
    void circular_reset();
    int position = 0;
    int buffer[FIFO_SIZE];

private:
    //int buffer[FIFO_SIZE];
    //int position = 0;
    // add variables pointing to the front and back of the buffer
};

#endif // FIFO_H
