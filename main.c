/* 
  Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. 
  Add the modulus (%) operator and provisions for negative numbers.

  Exercise 4-4. Add the commands to print the top elements of the stack without popping, 
  to duplicate it, and to swap the top two elements. Add a command to clear the stack.

  Exercise 4-5. Add access to library functions like sin, exp, and pow. 
  See <math.h> in Appendix B, Section 4.

  Exercise 4-6. Add commands for handling variables. 
  (It's easy to provide twenty-six variables with single-letter names.) 
  Add a variable for the most recently printed value.

  Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input.
  Should ungets know about buf and bufp, or should it just use ungetch?

  Exercise 4-8. Suppose that there will never be more than one character of pushback. 
  Modify getch and ungetch accordingly.

  Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. 
  Decide what their properties ought to be if an EOF is pushed back, then implement your design.

  Exercise 4-10. An alternate organization uses getline to read an entire input line; 
  this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
*/

#include <stdio.h>
#include <stdlib.h>  /* for atof()                      */
#include "calc.h"    /* the shared header file          */

#define  MAXOP 100   /* max size of operand or operator */
#define  NUMBER '0'  /* signal that a number was found  */

/* reverse Polish calculator */
int main()
{
  int    type;     /* the return signal from getop  */
  char   s[MAXOP]; /* the getop input buffer        */
  double op2;      /* a temp variable for non-commutative operators */

  while ((type = getop(s)) != EOF) 
  {
    switch (type) 
    {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push((int)pop() % (int)op2);
        else
          printf("error: zero divisor\n");
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }

  return 0;
}

