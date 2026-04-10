#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Define a dummy JanetCFunction for testing purposes
typedef void (*JanetCFunction)(void);

// Dummy function to act as JanetCFunction
void dummy_function(void) {
    // Do nothing
}

// Function-under-test
void janet_register(const char *name, JanetCFunction cfun);

int LLVMFuzzerTestOneInput_1481(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size < 1) return 0;

    // Allocate memory for the string and ensure it is null-terminated
    char *name = (char *)malloc(size + 1);
    if (!name) return 0;
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test with the fuzzed input
    janet_register(name, dummy_function);

    // Free allocated memory
    free(name);

    return 0;
}