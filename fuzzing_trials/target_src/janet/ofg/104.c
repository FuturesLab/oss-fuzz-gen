#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

// Function signature for the function-under-test
JanetBuffer *janet_pointer_buffer_unsafe(void *ptr, int32_t size, int32_t capacity);

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract two int32_t values
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Extract two int32_t values from the input data
    int32_t buffer_size = *(int32_t *)data;
    int32_t buffer_capacity = *(int32_t *)(data + sizeof(int32_t));

    // Ensure buffer_size is not negative and does not exceed the remaining data
    if (buffer_size < 0 || buffer_size > (int32_t)(size - sizeof(int32_t) * 2)) {
        return 0;
    }

    // Ensure buffer_capacity is non-negative
    if (buffer_capacity < 0) {
        return 0;
    }

    // Allocate memory for the buffer
    void *buffer_data = malloc(buffer_size);
    if (!buffer_data) {
        return 0;
    }

    // Copy the input data into the buffer
    memcpy(buffer_data, data + sizeof(int32_t) * 2, buffer_size);

    // Call the function-under-test
    JanetBuffer *result = janet_pointer_buffer_unsafe(buffer_data, buffer_size, buffer_capacity);

    // Clean up
    free(buffer_data);

    // Normally, you would do something with the result, but for fuzzing, we just return
    return 0;
}