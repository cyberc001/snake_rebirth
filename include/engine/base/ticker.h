#ifndef TICKER_H
#define TICKER_H

#include <pthread.h>
#include <stdarg.h>

typedef struct ticker ticker;
struct ticker
{
	pthread_t thread;
	void *args;
	long ms_betwn_ticks; // minimum amount of milliseconds between ticks

	int state; // 0 - stopped, 1 - running

	// a function that called every tick inside the ticker.
	void (*tick_func)(struct ticker *ticker_self, void *args);
};

int ticker_run(struct ticker *ticker_self, void *args);

#endif
