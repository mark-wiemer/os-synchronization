// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "main.h"
#include "queue.h"

void* write(void* v) {
	Queue* q = (Queue*) v;
	char buffer[BUFFSIZE];

	while (1) {
		char *dequeued = dequeueString(q);
		if (dequeued != NULL) { // not end of thread
			strcpy(buffer, dequeued);
			printf("%s\n", buffer);
		} else {
			return NULL;
		}
	}
}
