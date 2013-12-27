// Compile this file on alpha.cs.iit.edu with gcc -lm Lab00_sample.c

// CS 350, Fall 2013
// Lab 0: Basic C Programming
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>  // to access printf, scanf

// Prototype for square root routine
//
double sqrt(double);

int main() {
  // Just some playing around with strings and character printing.
  // The printf format codes %s and %c are for strings and characters
  // respectively.
  //
  char ch = '!';
  char *a_string = "This is a string";
  char *empty_string = "";
  printf("%s%s%c\n\n", a_string, empty_string, ch);

  int x = 17, y;
  double d = sqrt(x);

  // To print an expression, use the format code %d for integers
  // and %f for floating point & double-precision floating point.
  // 
  printf("The square root of %d = %f\n", x, d);
  printf("Enter an integer >= 0 (and then return): ");

  // To read into a variable of basic type (e.g., int, double, char),
  // use the same format codes as for printf, but insert an ampersand
  // before the variable in the list of variables.  We'll study the
  // ampersand in detail later, but basically it says to get the memory
  // address where y is stored.
  //
  scanf("%d", &y);
  printf("The square root of %d = %f\n", y, sqrt(y));

  // If we read a value too large to be stored as an integer, we'll
  // get the wrong value stored, possibly a negative number.
  //
  printf("Now enter an integer >= 2147483648: ");
  scanf("%d", &y);
  printf("The square root of %d = %f\n", y, sqrt(y));
  if (y < 0) {
    printf("\"nan\" means Not A Number (= sqrt of negative number)\n");
  }

  // To read/print a long integer, use format code %ld
  //
  long int z;
  printf("Try the same value (we'll read it as a long integer): ");
  scanf("%ld", &z);
  printf("The square root of %ld = %f\n", z, sqrt(z));

  return 0;
}
