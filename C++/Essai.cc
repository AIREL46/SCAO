#include <iostream>
#include<time.h>
#include<stdio.h>
using namespace std;
int main(void)
{
  time_t timer1;
	time_t timer2;
  timer1=time(NULL);
  
  timer2=time(NULL);
  printf("The current time is %s.\n",asctime(localtime(&timer1)));
  for (int i(0); i<=100; ++i)
  printf("The current time is %s.\n",asctime(localtime(&timer2)));
  return 0;
}
