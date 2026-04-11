#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

// Function-under-test
void janet_buffer_push_cstring(JanetBuffer *buffer, const char *cstring);

int LLVMFuzzerTestOneInput_358(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for use as a C string
    char *cstring = (char *)malloc(size + 1);
    if (cstring == NULL) {
        return 0;
    }
    memcpy(cstring, data, size);
    cstring[size] = '\0';  // Null-terminate the string

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initialize with a small buffer size

    // Call the function-under-test
    janet_buffer_push_cstring(&buffer, cstring);

    // Clean up
    free(cstring);
    janet_buffer_deinit(&buffer);

    return 0;
}