// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdio.h>
#include <string.h>
#include "main.h"

#define BUFFSIZE buffsize()

void read() {
	char buffer[BUFFSIZE];
	int validLine = 0;
	int lastLine = 0;
	int c;
	while (1) {
		//printf("Beginning of while\n");
		validLine = 0;
		for (int i=0 ; i < BUFFSIZE ; i++) {
			c = getchar();
			if (c == '\n') {
				buffer[i] = '\0';
				validLine = 1;
				break;
			}
			if (c == EOF) {
				buffer[i] = '\0';
				printf("%s", buffer);
				validLine = 1;
				lastLine = 1;
				break;
			}
			buffer[i] = c;
		//	printf("Current buffer: %s\n", buffer);
		}
		if (!validLine){
			//read rest of line or to end of file
			while ((c = getchar()) != '\n' && c != EOF) {
		//		printf("Last char: %c\n", c);
			}
			// if EOF, we are done
			if (c == EOF) {return; }
		} else {
		//	printf("Final valid buffer ");
			if (lastLine) {
				printf("%s", buffer);
				return;
			} else {
				printf("%s\n", buffer);
			}
		}
	}

}

