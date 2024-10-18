#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
        // only iterations 0, 3, 6, 9, 12 will be printed, thread takes (2, 1, 1, 1) elements
		for (int i = 0; i < 13; i+=3) {
			printf("[Thread %d] executes loop iteration %d\n", omp_get_thread_num(), i);
		}
	}

	return 0;
}