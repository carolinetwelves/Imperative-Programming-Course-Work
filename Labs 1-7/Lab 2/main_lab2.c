// SYSC 2006 - Lab 2 Template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"
/* main: Lab 2 - learing c with test cases */

/* Replace these lines with your information */
const char *author_main = "Caroline Twelves";
const char *student_number_main = "101301400";

int main(void)
{
  // Tests exercise 1 - Complete for a comprehensive test harness
  printf("\nTesting function 1: int alarm_clock(int day, bool vacation)\n");
  // expected values
  int expected_week_non_vac = 7;
  int expected_weekend_vac = -1;
  int other_values = 10;

  // weekday values
  for (int day = 1; day <= 5; day++)
  {
    // no vacation weekday
    int alarm_time_false = alarm_clock(day, false);
    if (alarm_time_false == expected_week_non_vac)
    {
      printf("Weekday %d, Non vacation: TEST PASS.\n", day);
    }
    else
    {
      printf("Weekday %d, Non vacation: TEST FAIL.\n", day);
    }

    // vacation and weekday
    int alarm_time_true = alarm_clock(day, true);
    if (alarm_time_true == other_values)
    {
      printf("weekday %d,     Vacation: TEST PASS.\n", day);
    }
    else
    {
      printf("Weekday %d,     Vacation: TEST FAIL.\n", day);
    }
  }

  // weekend values
  for (int day = 0; day <= 6; day += 6)
  {
    // no vacations weekend
    int alarm_time = alarm_clock(day, false);
    if (alarm_time == other_values)
    {
      printf("Weekend %d, Non vacation: TEST PASS.\n", day);
    }
    else
    {
      printf("Weekend %d, Non vacation: TEST FAIL.\n", day);
    }

    // vacation and weekend
    alarm_time = alarm_clock(day, true);
    if (alarm_time == expected_weekend_vac)
    {
      printf("Weekend %d,     Vacation: TEST PASS.\n", day);
    }
    else
    {
      printf("Weekend %d,     Vacation: TEST FAIL.\n", day);
    }
  }

  // Type your test cases for exercise 2. Make sure to include border line cases
  printf("\n\nTesting function 2: void count_replace(int value)\n");

  // random test cases
  printf("Test 02: 1 2\nPrinted: ");
  count_replace(2); // no multiples of either
  printf("Test 10: 1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz\nPrinted: ");
  count_replace(10);
  printf("Test 14: 1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14\nPrinted: ");
  count_replace(14);
  printf("Test 17: 1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16 17\nPrinted: "); // include multiples of both
  count_replace(17);

  // Type your test cases for exercise 3. Make sure to include border line cases
  printf("\n\nTesting function 3: _Bool is_prime(int value)\n");

  // random test cases prime numbers
  (is_prime(2)) ? (printf("2:   Test Pass.\n")) : (printf("2:   Test Fail.\n"));   // 2 - odd case
  (is_prime(7)) ? (printf("7:   Test Pass.\n")) : (printf("7:   Test Fail.\n"));   // 7 - random
  (is_prime(277)) ? (printf("23:  Test Pass.\n")) : (printf("23:  Test Fail.\n")); // 277 - large num

  // not prime multiples of 2 and 3
  for (int value = 2; value <= 6; value++)
  {
    (is_prime(2 * value)) ? (printf("2*%d: Test Fail.\n", value)) : (printf("2*%d: Test Pass.\n", value));
    (is_prime(3 * value)) ? (printf("2*%d: Test Fail.\n", value)) : (printf("3*%d: Test Pass.\n", value));
  }

  // Type your test cases for exercise 4. Make sure to include border line cases
  printf("\n\nTesting function 4: int sum_even(int value)\n");

  (sum_even(1) == 0) ? (printf("1:  Test Pass.\n")) : (printf("1:  Test Fail.\n"));     // 1 - test low num
  (sum_even(10) == 30) ? (printf("10: Test Pass.\n")) : (printf("10: Test Fail.\n"));   // 10 - test even num
  (sum_even(15) == 56) ? (printf("15: Test Pass.\n")) : (printf("15: Test Fail.\n"));   // 15 - test odd num
  (sum_even(19) == 90) ? (printf("19: Test Pass.\n")) : (printf("19: Test Fail.\n"));   // 19
  (sum_even(98) == 2450) ? (printf("98: Test Pass.\n")) : (printf("98: Test Fail.\n")); // 98 - test larger num

  printf("\nTest harness finished\n");
  return EXIT_SUCCESS;
}
