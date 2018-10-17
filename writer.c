// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "main.h"
#include "queue.h"

void* write(void* v) {
	Queue* q = (Queue*) v;

	while (1) {
		char *dequeued = dequeueString(q);
		if (dequeued != NULL) { // not end of thread
			printf("%s\n", dequeued);
			free(dequeued);
		} else {
			printf("Strings processed: %d\n", dequeueCount(q) - 1);
			return NULL;
		}
	}
}
