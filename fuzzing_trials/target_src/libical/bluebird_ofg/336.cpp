#include <sys/stat.h>
#include "libical/ical.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h> // Include for strlen

extern "C" int LLVMFuzzerTestOneInput_336(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    if (size == 0 || data[size - 1] != '\0') {
        // Create a new buffer with null-termination
        uint8_t *null_terminated_data = new uint8_t[size + 1];
        memcpy(null_terminated_data, data, size);
        null_terminated_data[size] = '\0';

        // Initialize libical component from null-terminated input data
        icalcomponent *component = icalcomponent_new_from_string(reinterpret_cast<const char*>(null_terminated_data));

        // Clean up the allocated buffer
        delete[] null_terminated_data;

        // Ensure component is not NULL
        if (component != NULL) {
            // Call the function-under-test
            struct icaltime_span span = icalcomponent_get_span(component);

            // Optionally, perform operations with `span` if needed
            // For example, check span properties or print them
            // printf("Start: %ld, End: %ld, Is Busy: %d\n", span.start, span.end, span.is_busy);

            // Clean up
            icalcomponent_free(component);
        }
    } else {
        // Input data is already null-terminated
        icalcomponent *component = icalcomponent_new_from_string(reinterpret_cast<const char*>(data));

        // Ensure component is not NULL
        if (component != NULL) {
            // Call the function-under-test
            struct icaltime_span span = icalcomponent_get_span(component);

            // Optionally, perform operations with `span` if needed
            // For example, check span properties or print them
            // printf("Start: %ld, End: %ld, Is Busy: %d\n", span.start, span.end, span.is_busy);

            // Clean up
            icalcomponent_free(component);
        }
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

    LLVMFuzzerTestOneInput_336(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
