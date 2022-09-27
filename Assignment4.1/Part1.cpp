


// PART1

// main.cpp
#include <iostream>
using namespace std;

int main(){
        cout << "Hello World" << endl;
        return 0;
}

// makefile                              
hello: src/main.cpp
        g++ -o make src/main.cpp

clean:
        rm -f make

