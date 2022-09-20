#include <Arduino.h>
// -------- PART 1 -------

//int array[1000];
//int8_t array8[1000];
//int16_t array16[1000];
//int32_t array32[1000];
//int64_t array64[1000];

//int main()
//{
  //return array[45];
  //return array8[45];
  //return array16[45];
  //return array32[45];
  //return array64[45];
//}


// ------- PART 2 -------

//GLOBAL VARIABLE
//int a;

int main()
{
  //LOCAL VARIABLE
  //int a;
  //STATIC VARIABLE
  //static int a;
  //CONSTANT VARIABLE
  //const int a;
  //DYNAMICALLY ALLOCATED VARIABLE
  int* a = new int[10];
  return a;
}

