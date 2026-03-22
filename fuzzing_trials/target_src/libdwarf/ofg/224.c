#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assume the function is declared in a header file or elsewhere
int dwarf_get_EH_name(unsigned int encoding, const char **name);

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0; // Not enough data to form an unsigned int
    }

    unsigned int encoding = *(const unsigned int *)data;
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_EH_name(encoding, &name);

    // Optionally print the result and name for debugging purposes
    if (name != NULL) {
        printf("Result: %d, Name: %s\n", result, name);
    } else {
        printf("Result: %d, Name: NULL\n", result);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif