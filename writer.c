// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "main.h"
#include "queue.h"

#define BUFFSIZE buffsize()

void* write(void* v) {
	Queue* q = (Queue*) v;
	char buffer[BUFFSIZE];

	while (1) {
		strcpy(buffer, dequeueString(q));
		if (strcmp(buffer, eot())) { // not end of thread
			printf("%s\n", buffer);
		} else {
			return NULL;
		}
	}
}
