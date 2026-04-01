#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern int dwarf_get_ACCESS_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int access_code;
    const char *access_name = NULL;

    // Copy the first 4 bytes from data to access_code
    access_code = *(unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_ACCESS_name(access_code, &access_name);

    // Optionally print the result and access_name for debugging purposes
    if (result == 0 && access_name != NULL) {
        printf("Access code: %u, Access name: %s\n", access_code, access_name);
    }

    return 0;
}