#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <cstring>  // Include for memcpy
#include "libical/ical.h"

// Ensure the function-under-test and related functions are correctly wrapped for C++ linkage
extern "C" {
    struct icaltimetype icalproperty_get_lastmodified(const icalproperty *);
    icalproperty* icalproperty_new_from_string(const char *);
    void icalproperty_free(icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_464(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for safe string operations
    char *null_terminated_data = (char*)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new_from_string(null_terminated_data);

    // Free the allocated memory for null-terminated data
    free(null_terminated_data);

    // Ensure the icalproperty is not NULL
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype result = icalproperty_get_lastmodified(prop);

    // Clean up
    icalproperty_free(prop);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_464(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
