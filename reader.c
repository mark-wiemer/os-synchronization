// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "queue.h"

#define BUFFSIZE buffsize()

void* read(void* v) {
	Queue* queue = (Queue*) v;
	char buffer[BUFFSIZE];
	char* copy = (char*) malloc(BUFFSIZE * sizeof(char));
	int validLine = 0;
	int lastLine = 0;
	int c;
	while (1) {
		validLine = 0;
		lastLine = 0;
		for (int i=0 ; i < BUFFSIZE ; i++) {
			c = getchar();
			if (c == '\n') {
				buffer[i] = '\0';
				validLine = 1;
				break;
			}
			if (c == EOF) {
				if (i == 0) { // file ends on newline
					enqueueString(queue, NULL);
					return NULL;
				}
				buffer[i] = '\0';
				validLine = 1;
				lastLine = 1;
				break;
			}
			buffer[i] = c;
		}
		if (!validLine){
			fprintf(stderr, "ERROR: line too long, it was discarded\n");
			//read rest of line or to end of file
			while ((c = getchar()) != '\n' && c != EOF) {
				// printf("Last char: %c\n", c);
			}
			// if EOF, we are done
			if (c == EOF) {
				enqueueString(queue, NULL);
				return NULL;
			}
		} else {
			strcpy(copy, buffer);
			enqueueString(queue, copy);
			if (lastLine) {
				enqueueString(queue, NULL);
				return NULL;
			}
		}
	}
}

