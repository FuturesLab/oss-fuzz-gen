#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

extern int libbpf_strerror(int err, char *buf, size_t size);

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int err = *(int *)data;

    // Allocate a buffer for the error string
    size_t buf_size = 256; // Arbitrary buffer size
    char buf[buf_size];

    // Call the function-under-test
    libbpf_strerror(err, buf, buf_size);

    // Optionally, print the error string for debugging
    printf("Error: %d, Message: %s\n", err, buf);

    return 0;
}