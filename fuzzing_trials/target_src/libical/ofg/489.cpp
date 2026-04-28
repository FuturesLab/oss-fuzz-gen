#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_489(const uint8_t *data, size_t size) {
    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZID_PROPERTY);

    // Ensure the data is not empty
    if (size > 0) {
        // Convert the input data to a string
        char *tzid = (char *)malloc(size + 1);
        if (tzid == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(tzid, data, size);
        tzid[size] = '\0';

        // Set the TZID property
        icalproperty_set_tzid(prop, tzid);

        // Free the temporary string
        free(tzid);
    }

    // Call the function-under-test
    const char *result = icalproperty_get_tzid(prop);

    // Use the result in some way to avoid compiler optimizations
    if (result != NULL) {
        // Do something with the result, e.g., print it
        // Note: In a real fuzzing scenario, you might not print to avoid I/O overhead
    }

    // Free the icalproperty object
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

    LLVMFuzzerTestOneInput_489(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
