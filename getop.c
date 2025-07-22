#include <stdio.h>
#include <ctype.h>
#include "calc.h"    /* the shared header file  */

int getop(char s[])
{
	int i, c, d;

    /* skip over whitespace */
	while((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';

    /* if c is an operator, not part of a number */
	if(!isdigit(c) && c != '.' && c != '-')
		return c;

    /* look ahead to decide if "-" is 
       an operator or a minus sign */
	if(c == '-')
	{
		d = getch();
		if(d == ' ')
			return c;
		else
			ungetch(d);
	}

    /* OK, scoop up the rest of the number 
       and save it in the string */
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}
