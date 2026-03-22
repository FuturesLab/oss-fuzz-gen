#include <stdint.h>
#include <stddef.h>

// Assuming the function is declared in some header file, include it here
// #include "dwarf.h"

// // Mock implementation of the function for demonstration purposes
// int dwarf_get_MACRO_name(unsigned int index, const char **name) {
//     static const char *names[] = {"MACRO1", "MACRO2", "MACRO3"};
//     if (index < 3) {
//         *name = names[index];
//         return 0; // Success
//     }
//     return -1; // Failure
// }

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    unsigned int index;
    const char *name = NULL;

    if (size < sizeof(unsigned int)) {
        return 0; // Not enough data to form an unsigned int
    }

    // Use the first bytes of the input data as the index
    index = *((unsigned int *)data);

    // Call the function-under-test
    int result = dwarf_get_MACRO_name(index, &name);

    // Optionally, do something with the result or name
    // For fuzzing purposes, we just want to ensure the function is called

    return 0;
}

#ifdef __cplusplus
}
#endif