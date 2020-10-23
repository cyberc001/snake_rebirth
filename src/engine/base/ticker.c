#include "engine/base/ticker.h"

#include <math.h>

void* ticker_thread(void *args)
{
	struct ticker *ticker_self = (struct ticker*)args;
	struct timespec ctime, stime;
	long time_ms_beg, time_ms_diff;

	while(ticker_self->state == 1)
	{
		clock_gettime(CLOCK_MONOTONIC, &ctime);
		time_ms_beg = round(ctime.tv_nsec / 1.0e6) + ctime.tv_sec * 1000;

		ticker_self->tick_func(ticker_self, ticker_self->args);

		clock_gettime(CLOCK_MONOTONIC, &ctime);
		time_ms_diff = round(ctime.tv_nsec / 1.0e6) + ctime.tv_sec * 1000 - time_ms_beg;
		time_ms_diff = ticker_self->ms_betwn_ticks > time_ms_diff ? ticker_self->ms_betwn_ticks - time_ms_diff : 0;
		stime.tv_sec = time_ms_diff / 1000;
		stime.tv_nsec = (time_ms_diff % 1000) * 1000000;
		nanosleep(&stime, NULL);
	}
}

int ticker_run(struct ticker *ticker_self, void *args)
{
	ticker_self->state = 1;
	ticker_self->args = args;
	pthread_create(&(ticker_self->thread), NULL, &ticker_thread, ticker_self);
}
