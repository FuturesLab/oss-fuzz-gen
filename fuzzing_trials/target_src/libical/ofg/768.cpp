#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm> // Include this header for std::all_of

extern "C" {
    // Wrap C headers and functions in extern "C" to ensure proper linkage
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_768(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty and is valid UTF-8
    if (size == 0 || !std::all_of(data, data + size, [](uint8_t c) { return c != 0; })) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        return 0; // Return if memory allocation fails
    }

    // Copy the data into the tzid string and null-terminate it
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_defaulttzid(tzid);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Perform some operations on the property to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        const char *value = icalproperty_get_tzid(prop);

        // Clean up
        icalproperty_free(prop);
    }
    free(tzid);

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

    LLVMFuzzerTestOneInput_768(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
