#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

// Function-under-test declaration
void janet_buffer_push_cstring(JanetBuffer *, const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_357(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C string
    char *cstring = (char *)malloc(size + 1);
    if (cstring == NULL) {
        return 0;
    }
    memcpy(cstring, data, size);
    cstring[size] = '\0';

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10); // Initializing with a small size

    // Call the function-under-test
    janet_buffer_push_cstring(&buffer, cstring);

    // Clean up
    janet_buffer_deinit(&buffer);
    free(cstring);

    return 0;
}