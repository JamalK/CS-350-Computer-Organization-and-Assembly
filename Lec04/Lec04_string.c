// CS 350, Fall 2013
//
// string.c: C strings as arrays of characters, terminated by '\0'
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>

int main() {
	/* A string of length 3 is char array of length 4 (with last char '\0')
	 */
	char s[4] = "A9z";
	printf("String <%s>\n", s);
	int i = 0;
	for (i = 0 ; i < 4 ; i++) {
		printf("s[%d] = '%c' = %d\n", i, s[i], s[i]);
	}

	/* A char array of length 4 (with last char = '\0') is a string of length 3
	 */
	char a[4] = {65, 57, 122, 0};
	printf("String <%s>\n", a);
	a[1] = '\0';
	printf("String <%s>\n", a);		// A
}

