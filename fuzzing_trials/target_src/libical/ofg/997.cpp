#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_997(const uint8_t *data, size_t size) {
    // Initialize libical
    icalproperty *prop = nullptr;

    // Ensure that the input data is not empty
    if (size > 0) {
        // Create a temporary buffer to null-terminate the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == nullptr) {
            return 0; // Exit if memory allocation fails
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Parse the input data as an iCalendar property
        prop = icalproperty_new_from_string(buffer);

        // Free the temporary buffer
        free(buffer);
    }

    // If a valid property was created, get its version
    if (prop != nullptr) {
        const char *version = icalproperty_get_version(prop);
        // Use the version for further processing or testing
        // (e.g., printing, logging, etc.)
        (void)version; // Suppress unused variable warning

        // Free the created property
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_997(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
