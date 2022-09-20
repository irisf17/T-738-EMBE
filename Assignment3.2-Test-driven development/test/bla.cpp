// /******************************************************************************

//                               Online C++ Compiler.
//                Code, Compile, Run and Debug C++ program online.
// Write your code in this editor and press "Run" button to compile and execute it.

// *******************************************************************************/

// #include <iostream>
// using namespace std;

// int buffer[5];
// int position = 0;
// int val;
// void get()
// {
//     val = buffer[0];
//     for(int i=0; i<4; i++)
//     {
//         buffer[i] = buffer[i+1];
//     }  
//     // buffer[4] = 0;
//     position--;
// }

// void put(int val){
//     if(position == 5){
//         get();
//     }
//     buffer[position] = val;
//     position++;
// }

// int main()
// {
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
        
//     }
//     put(1);
//     put(2);
//     get();
//     get();
//     get();
    
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
//     }
//     cout << "put position is: " ;
//     cout << position << endl;
    
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
//     }

//     return 0;
// }



// // Online C++ compiler to run C++ program online
// #include <iostream>
// using namespace std;

// int buffer[5];

// int *tail = buffer;
// int *head = buffer;
// int position = 0;
// int val;
// void get()
// {
//     val = buffer[0];
//     for(int i=0; i<4; i++)
//     {
//         buffer[i] = buffer[i+1];
//     }  
//     // buffer[4] = 0;
//     position--;
// }

// void put(int value)
// {
//     *tail = value;
//     if (position == 4)
//     {
//         tail = tail - (5-1);
//         // get();
//     }
//     else{
//         tail++;
//     }
//     if (position < 4){
//         *head = value;
//     }
//     position = (position+1)%5;
// }

// int main()
// {
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
        
//     }
//     put(1);
//     put(2);
//     put(3);
//     put(4);
//     put(5);
//     put(6);
//     put(7);
    
    
//     cout << "after change" << endl;
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
//     }
//     cout << "put position is: " ;
//     cout << position << endl;
    
//     cout << "tail-1 points at: ";
//     cout << *(tail-1) << endl;
//     cout << "head points at: ";
//     cout << *head << endl;

//     return 0;
// }



// // Online C++ compiler to run C++ program online
// #include <iostream>
// using namespace std;

// int buffer[5];
// int init = 0;
// int *tail = buffer;
// int *head = buffer;

// int bufferlength = 0;

// int counter = 0;

// int get(){
//     int front = *head;
//     head++;
//     if (bufferlength > 0){
//         bufferlength--;
//     }
//     if (head == &buffer[0] + 5){
//         head = &buffer[0];
//     }
//     return front;
// }

// void put(int item){
//     *tail = item;
    
//     if (head == tail && init != 0){
//         head++;
//         if (head == &buffer[0] + 5){
//             head = &buffer[0];
//         }
//     }else{
//         init = 1;
//     }
//     tail++;
//     if (tail == &buffer[0] + 5){
//         tail = &buffer[0];
//     }
//     if (bufferlength < 5){
//         bufferlength++;
//     }
// }



// int main()
// {
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
        
//     }
//     put(1);
//     put(2);
//     put(3);
//     put(4);
//     // get();
//     put(5);
//     put(6);
//     put(7);
//     get();
//     // get();
//     // put(8);
//     // put(9);
//     // put(10);
//     // put(11);
//     // put(12);
//     // put(13);
//     // put(14);
//     // put(15);
//     // put(16);
    
//     cout << "after change" << endl;
//     for (int i=0; i< 5; i++)
//     {
//         cout << buffer[i] << endl;
//     }
//     // cout << "put position is: " ;
//     // cout << position << endl;
    
//     cout << "tail-1 points at: ";
//     cout << *(tail-1) << endl;
    
//     cout << "head points at: ";
//     cout << *head << endl;

//     return 0;
// }
