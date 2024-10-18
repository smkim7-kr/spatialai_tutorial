#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
        // Since 13 % 4 != 0, thread 0 takes responnsiblity for one more element i.e. (4, 3, 3, 3)
		for (int i = 0; i < 13; i++) {
			printf("[Thread %d] executes loop iteration %d\n", omp_get_thread_num(), i);
		}
	}

	return 0;
}