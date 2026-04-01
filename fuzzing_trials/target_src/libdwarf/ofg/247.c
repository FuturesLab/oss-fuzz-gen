#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Assuming the function is declared in a header file
int dwarf_get_FORM_name(unsigned int form, const char **name);

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int form = *((unsigned int *)data);

    // Initialize a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_FORM_name(form, &name);

    // For debugging purposes, print the result and name if needed
    // Note: In a real fuzzing environment, avoid printing to reduce noise
    // printf("Result: %d, Name: %s\n", result, name ? name : "NULL");

    return 0;
}

#ifdef __cplusplus
}
#endif