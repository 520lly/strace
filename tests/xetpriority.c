#include "tests.h"
#include <asm/unistd.h>

#if defined __NR_getpriority && defined __NR_setpriority

# include <stdio.h>
# include <sys/resource.h>
# include <unistd.h>

int
main(void)
{
	const int pid = getpid();
	long rc = syscall(__NR_getpriority, PRIO_PROCESS,
			  (unsigned long) 0xffffffff00000000 | pid);
	printf("getpriority(PRIO_PROCESS, %d) = %ld\n", pid, rc);

	rc = syscall(__NR_setpriority, PRIO_PROCESS,
		     (unsigned long) 0xffffffff00000000 | pid,
		     (unsigned long) 0xffffffff00000000);
	if (rc)
		printf("setpriority(PRIO_PROCESS, %d, 0) = %ld %s (%m)\n",
		       pid, rc, errno2name());
	else
		printf("setpriority(PRIO_PROCESS, %d, 0) = 0\n", pid);

	puts("+++ exited with 0 +++");
	return 0;
}

#else

SKIP_MAIN_UNDEFINED("__NR_getpriority && _NR_setpriority")

#endif
