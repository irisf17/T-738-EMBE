#include <fifo.h>

Fifo::Fifo()
{
    
}

// ---- Fifo list TESTING-----
int Fifo::get()
{
    if (!is_empty())
    {
        int value = buffer[0];
        for (int i = 0; i < 4; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        position--;
        return value;
    }
    else
    {
        return 0;
    }
}

// ------ Fifo list ------
void Fifo::put(int value)
{
    if (position == 5)
    {
        get();
    }
    buffer[position] = value;
    position++;
}

bool Fifo::is_empty()
{
    if (position < 0)
    {
        position = 0;
    }
    return position == 0;
}

bool Fifo::is_full()
{
    return position == 4;
}

void Fifo::reset()
{
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = 0;
    }
    position = 0;
}

void Fifo::test_normal_flow()
{
    position = 0;
}

void Fifo::test_underflow()
{
    position = 0;
}

void Fifo::test_overflow()
{
    position = 4;
}

void Fifo::test_overwrite()
{
}

// -- Circular TESTING

int Fifo::circular_get()
{
    if (!is_empty())
    {
        int front = *head;
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
}

void Fifo::circular_put(int item)
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
    return position == 4;
}

void Fifo::circular_reset()
{
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = 0;
    }
    head = buffer;
    tail = buffer;
    position = 0;
    init = 0;
}