#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the icalproperty and initialize it
    icalproperty *prop = icalproperty_new(ICAL_TZNAME_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzname = (char *)malloc(size + 1);
    if (tzname == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(tzname, data, size);
    tzname[size] = '\0';

    // Call the function-under-test
    icalproperty_set_tzname(prop, tzname);

    // Additional function calls to increase code coverage
    const char *retrieved_tzname = icalproperty_get_tzname(prop);
    if (retrieved_tzname != NULL) {
        // Use the retrieved_tzname in some way to ensure it is accessed
        if (strcmp(tzname, retrieved_tzname) != 0) {
            // Handle the case where the set and retrieved values differ
        }
    }

    // Clean up
    free(tzname);
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

    LLVMFuzzerTestOneInput_81(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
