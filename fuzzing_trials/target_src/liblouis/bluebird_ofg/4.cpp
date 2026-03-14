#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../../liblouis/liblouis.h"
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for two strings
    char *string1 = (char *)malloc(size + 1);
    char *string2 = (char *)malloc(size + 1);

    // Copy data into the strings and null-terminate them
    memcpy(string1, data, size);
    string1[size] = '\0';
    memcpy(string2, data, size);
    string2[size] = '\0';

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lou_compileString
    lou_compileString(string1, (const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free allocated memory
    free(string1);
    free(string2);

    return 0;
}