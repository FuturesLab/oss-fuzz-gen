#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    // Allocate memory for a JanetBuffer
    JanetBuffer *buffer = (JanetBuffer *)malloc(sizeof(JanetBuffer));
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Ensure that the size is non-zero and within a reasonable range for initialization
    int32_t init_size = (size > 0) ? (int32_t)(data[0] % 1000) + 1 : 1;

    // Call the function-under-test
    janet_buffer_init(buffer, init_size);

    // Clean up allocated memory
    free(buffer);

    return 0;
}