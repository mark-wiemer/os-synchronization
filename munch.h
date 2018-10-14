// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#ifndef MUNCH_H
#define MUNCH_H

#include <pthread.h>

#include "queue.h"

typedef struct MunchArgs {
	Queue* in;
	Queue* out;
} MunchArgs;

void* munch1(void* queues);
void* munch2(void* queues);
#endif
