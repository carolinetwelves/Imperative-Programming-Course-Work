// SYSC 2006 - Lab 2 Solution template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"
/* main: Lab 2 - functions to test*/

/* Replace these lines with your information */
const char *author = "Caroline Twelves";
const char *student_number = "101301400";

// Type your solution to exercise 1 inside the body of the function. You need to update the return statement
int alarm_clock(int day, _Bool vacation)
{
  // Weekend
  if (day == 0 || day == 6)
  {
    if (vacation)
    {
      return -1; // vacation + weekend
    }
    else
    {
      return 10; // normal weekend
    }
  }
  // Weekday
  else
  {
    if (vacation)
    {
      return 10; // vacation weekday
    }
    else
    {
      return 7; // normal weekday
    }
  }
  return 1;
}
// Type your solution to exercise 2 inside the body of the function.
void count_replace(int value)
{
  for (int i = 1; i <= value; i++)
  {
    if (i % 15 == 0) // multiple of both 3 and 5
    {
      printf("FizzBuzz ");
    }
    else if (i % 3 == 0) // multiple of only 3
    {
      printf("Fizz ");
    }
    else if (i % 5 == 0) // multiple of only 5
    {
      printf("Buzz ");
    }
    else
    {
      printf("%d ", i); // not multiple of either
    }
  }
  printf("\n");
  return;
}
// Type your solution to exercise 3 inside the body of the function. You need to update the return statement
_Bool is_prime(int value)
{
  if (value == 1) // 1 - weird case on own
  {
    return false;
  }

  if (value == 2) // 2 - weird case on own
  {
    return true;
  }

  // loop through all numbers under value to see if any are divisible
  for (int i = 2; i <= value / 2; i++)
  {
    // not prime
    if (value % i == 0)
    {
      return false;
    }
  }

  return true;
}
// Type your solution to exercise 4 inside the body of the function. You need to update the return statement
int sum_even(int value)
{
  int sum = 0;

  for (int i = 0; i <= value; i += 2)
  {
    sum += i;
  }

  return sum;
}