#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/libbpf/include/uapi/linux/perf_event.h"
#include "libbpf.h"

// Dummy callback functions
void sample_fn(void *ctx, int cpu, void *data, __u32 size) {
    // Sample handling logic
}

void lost_fn(void *ctx, int cpu, __u64 lost) {
    // Lost event handling logic
}

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure the input size is at least the size of struct perf_buffer_opts
    if (size < sizeof(struct perf_buffer_opts)) {
        return 0;
    }

    // Initialize parameters for perf_buffer__new
    int map_fd = 1; // Dummy file descriptor
    size_t page_cnt = 8; // Example page count
    void *ctx = (void *)data; // Use data as context

    // Initialize and copy data to a struct perf_buffer_opts
    struct perf_buffer_opts opts;
    memset(&opts, 0, sizeof(struct perf_buffer_opts)); // Zero out the structure

    // Safely copy the input data into opts, ensuring no overflow
    // Adjust the size to copy only up to the size of opts
    memcpy(&opts, data, sizeof(opts) < size ? sizeof(opts) : size);

    // Call the function-under-test
    struct perf_buffer *pb = perf_buffer__new(map_fd, page_cnt, sample_fn, lost_fn, ctx, &opts);

    // Cleanup
    if (pb) {
        perf_buffer__free(pb);
    }

    return 0;
}