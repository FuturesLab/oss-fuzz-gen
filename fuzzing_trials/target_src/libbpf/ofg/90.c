#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assume the function is declared in a library header
int libbpf_unregister_prog_handler(int prog_id);

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int prog_id = *(const int*)data;

    // Call the function-under-test
    int result = libbpf_unregister_prog_handler(prog_id);

    // Optionally, print the result for debugging purposes
    printf("Result: %d\n", result);

    return 0;
}