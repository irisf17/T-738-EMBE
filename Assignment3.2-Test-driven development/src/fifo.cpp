#include <fifo.h>

Fifo::Fifo()
{
}

// ---- Fifo list -----
// int Fifo::get()
// {
//     if (!is_empty())
//     {
//         int value = buffer[0];
//         for (int i = 0; i < 4; i++)
//         {
//             buffer[i] = buffer[i + 1];
//         }
//         position--;
//         return value;
//     }
//     else
//     {
//         return 0;
//     }
// }


// ------ Fifo list ------
// void Fifo::put(int value)
// {
//     if (position == 5)
//     {
//         get();
//     }
//     buffer[position] = value;
//     position++;
// }

// ----- Fifo circle with pointers -----
void Fifo::put(int value)
{
    *tail = value;
    if (position == 5)
    {
        tail = tail - (sizeof(buffer)-1);
        get();
    }
    tail++;
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