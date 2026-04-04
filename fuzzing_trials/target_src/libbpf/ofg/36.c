#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/perf_event.h>

// Assuming the perf_buffer struct is defined somewhere in the included headers
struct perf_buffer {
    // Dummy fields for illustration
    int dummy_field1;
    int dummy_field2;
};

extern int perf_buffer__poll(struct perf_buffer *, int);

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize a perf_buffer structure
    struct perf_buffer pb;
    pb.dummy_field1 = 1; // Assigning some non-zero values
    pb.dummy_field2 = 2;

    // Use the first byte of data as the integer parameter
    int poll_timeout = (size > 0) ? (int)data[0] : 1; // Default to 1 if size is 0

    // Call the function under test
    int result = perf_buffer__poll(&pb, poll_timeout);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}