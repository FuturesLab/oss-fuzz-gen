#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring> // Include for memcpy

extern "C" {
    // Ensure all libical headers and functions are wrapped with extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_721(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Create a new icalproperty from the input string
    icalproperty *prop = icalproperty_new_from_string(inputString);

    // Ensure prop is not NULL before calling the function
    if (prop != NULL) {
        // Call the function-under-test
        const char *charset = icalproperty_get_xlicmimecharset(prop);

        // Use the result in some way to prevent optimizations from removing the call
        if (charset != NULL) {
            // Do something with charset, e.g., print or log
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Clean up the allocated string
    delete[] inputString;

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

    LLVMFuzzerTestOneInput_721(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
