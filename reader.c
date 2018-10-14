// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdio.h>
#include <string.h>
#include "main.h"

#define BUFFSIZE buffsize()

void read() {
	// reading the standard input
	char buffer[BUFFSIZE];
	// We need the error check
	for (int i=0 ; i < BUFFSIZE ; i++) {
		int c = getchar();
		if (c == '\n') {
			buffer[i] = '\0';
			break;
		}
		buffer[i] = c;
	}

	printf("Testing newline : %s\n", buffer);

}

