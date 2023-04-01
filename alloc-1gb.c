#include <stdio.h>
#include <stdlib.h>

#include "mem_util.h"

#define MB (1*1024*1024)
#define TOTAL_SIZE_MB 1024

int compare_addrs(const void * x, const void * y) {
    return *((long *)x) > *((long *)y);
}

int main() {
    long memory_initial = capture_memory_usage();
    printf("memory usage initial: %ld KB\n", memory_initial);

    // if total size = 10 MB, we will allocate
    // the array of size 10, allowing us to store 10 addresses
    long *addrs = (long *) malloc(TOTAL_SIZE_MB * sizeof(long));

    // holding total memory usage ... expected.
    long long int total_mem_usage_expected = 0;

    // allocating TOTAL_SIZE_MB itereatively in chunks of 1MB each 
    for (int i = 0; i < TOTAL_SIZE_MB; i++) {
        // allocating 1 MB
        char* arr = (char*) malloc(MB);
        total_mem_usage_expected += MB;

        // storing the address of allocated chunk
        addrs[i] = (long int) arr;

        // printing out expected and actual memory usage
        printf("%p - memory usage - expected %lld MB, actual %ld + %ld KB\n",
            arr,
            total_mem_usage_expected/MB,
            memory_initial, (capture_memory_usage() - memory_initial));
    }

    qsort(addrs, TOTAL_SIZE_MB, sizeof(long), compare_addrs);

    // total malloc'ed memory
    printf("total malloc'ed memory: %ld MB\n",
        (addrs[TOTAL_SIZE_MB-1] - addrs[0])/MB + 1);

    // total memory usage
    printf("total memory usage: %ld MB\n", capture_memory_usage()/1024);

    return 0;
}
