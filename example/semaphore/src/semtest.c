#include <stdio.h>
#include <assert.h>
#include <iguana/memsection.h>
#include <iguana/thread.h>
#include <l4/thread.h>
#include <l4/kdebug.h>
#include <l4/ipc.h>
#include <timer/timer.h>
#include <mutex/mutex.h>

#define CONCURRENT 10

volatile unsigned long shared_resource = 0;

struct mutex mutex = {0, 0};

static void
easy_thread_create(void (*fn) (void), int priority)
{
	char *stack_top;
	L4_ThreadId_t ignore;
	thread_ref_t thread;
	memsection_create(0x1000, (void*) &stack_top);
	stack_top += 0x1000 - sizeof(uintptr_t);
	thread = thread_create_priority(priority, &ignore);
	thread_start(thread, (uintptr_t) fn, (uintptr_t) stack_top);
}

static void
thread_run(void)
{
	int iter = 0;

	//L4_Set_PreemptCallbackIP((L4_Word_t) preempt_restart);

	while(iter < 1000000) {
		//printf("calling fast lock\n");
		assert(mutex.holder != L4_Myself().raw);
		mutex_lock(&mutex);
		//printf("lock: %lx\n", mutex.holder);
		assert(mutex.holder == L4_Myself().raw);
		//printf("called fast lock %lx\n", mutex.holder);

		shared_resource = L4_Myself().raw;

		if (shared_resource != L4_Myself().raw) {
			printf("%lx failed after %d loops\n", L4_Myself().raw, iter);
		}
		assert(L4_Myself().raw == shared_resource);
		mutex_unlock(&mutex);

		iter++;

		if (iter % 50000 == 0) {
			printf("Thread %lx has performed %d loops\n", L4_Myself().raw, iter);
		}
	}
	printf("Finished!\n");
	L4_WaitForever();
}

int high_started = 0;
int high_done = 0;
int low_done = 0;

static void
high_priority(void)
{
	L4_KDB_SetThreadName(L4_Myself(), "hi");
	printf("High priority started\n");
	/* Grab lock */
	high_started = 1;

	mutex_lock(&mutex);
	assert(low_done == 1);
	high_started = 0;
	high_done = 1;
	mutex_unlock(&mutex);
	printf("High finished\n");
	L4_WaitForever();
}

static void
med_priority(void)
{
	L4_KDB_SetThreadName(L4_Myself(), "med");
	while(! high_done) {
		assert(high_started == 0);
	}
	printf("Medium finished\n");
	L4_WaitForever();
}


static void
low_priority(void)
{
	int i, j = 0;

	L4_KDB_SetThreadName(L4_Myself(), "lo");
	/* Grab lock */
	mutex_lock(&mutex);
	while(j++ < 20) { for(i=0; i < 99999; i++) ;  }
	low_done = 1;
	mutex_unlock(&mutex);
	printf("Low finished\n");

	L4_WaitForever();
}

int
main(int argc, char **argv)
{
	timer_t timer;
	int r;
	timer_init();

	printf("Self locking test\n");
	mutex_count_lock(&mutex);
	mutex_count_lock(&mutex);
	mutex_count_lock(&mutex);
	assert(mutex.holder == L4_Myself().raw);

	mutex_count_unlock(&mutex);
	assert(mutex.holder == L4_Myself().raw);
	mutex_count_unlock(&mutex);
	mutex_count_unlock(&mutex);

	printf("Priority inversion test\n");

	timer = timer_create();  /* We delete it in the delete test */
	easy_thread_create(low_priority, 85);
	r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
	timer_wait();
	easy_thread_create(med_priority, 90);
	r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
	timer_wait();
	easy_thread_create(high_priority, 95);


	r = timer_request(timer, MILLISECS(50), TIMER_ONESHOT);
	timer_wait();

	printf("Semaphore test program\n");
	for(int i = 0; i < CONCURRENT; i++) {
		easy_thread_create(thread_run, 100);
	}

	L4_WaitForever();
	return 0;
}
