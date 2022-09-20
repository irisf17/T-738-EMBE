/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;

int buffer[5];
int position = 0;
int val;
void get()
{
    val = buffer[0];
    for(int i=0; i<4; i++)
    {
        buffer[i] = buffer[i+1];
    }  
    // buffer[4] = 0;
    position--;
}

void put(int val){
    if(position == 5){
        get();
    }
    buffer[position] = val;
    position++;
}

int main()
{
    for (int i=0; i< 5; i++)
    {
        cout << buffer[i] << endl;
        
    }
    put(1);
    put(2);
    get();
    get();
    get();
    
    for (int i=0; i< 5; i++)
    {
        cout << buffer[i] << endl;
    }
    cout << "put position is: " ;
    cout << position << endl;
    
    for (int i=0; i< 5; i++)
    {
        cout << buffer[i] << endl;
    }

    return 0;
}
