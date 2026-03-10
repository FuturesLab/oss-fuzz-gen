#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h"
}

// Fuzzer entry point
extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a C-string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(cstr, data, size);
    cstr[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    char *result = lou_setDataPath(cstr);

    // Free the allocated memory
    free(cstr);

    // Free the result if needed
    if (result != NULL) {
        free(result);
    }

    return 0;
}