#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Define a dummy JanetCFunction for testing purposes
typedef void (*JanetCFunction)(void);

void dummy_function_95(void) {
    // This is a placeholder function
}

// Function-under-test
void janet_register(const char *name, JanetCFunction func);

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the name string and ensure it's null-terminated
    char name[256];
    size_t copy_size = size < 255 ? size : 255;
    memcpy(name, data, copy_size);
    name[copy_size] = '\0';

    // Call the function-under-test
    janet_register(name, dummy_function_95);

    return 0;
}