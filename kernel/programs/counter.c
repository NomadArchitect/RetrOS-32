#include <process.h>
#include <sync.h>
#include <util.h>
#include <screen.h>

static int counters = 0;
static int value = 0;
static lock_t c_lock;


void reset_value()
{
    value = 0;
}

void add()
{
    lock(&c_lock);
    value++;
    unlock(&c_lock);
}


void counter()
{
    int id = counters++;

    int num = 0;
	while(1)
    {
		num = (num+1) % 100000000;
		if(num % 100000000 == 0)
		{  
            add();
			scrprintf(10, 10+id, "Counter: %d   ", value);
		}
	};
}

void init_counter()
{   
    lock_init(&c_lock);
    int pid = ATTACH_PROCESS("Counter", &counter);
    ATTACH_FUNCTION(pid, "reset", &reset_value);
}