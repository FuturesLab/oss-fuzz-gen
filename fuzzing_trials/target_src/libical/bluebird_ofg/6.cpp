#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize a icalcomponent and icalcompiter
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcompiter iter;

    // Ensure the data is not empty and within a reasonable size
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to store the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer != NULL) {
            memcpy(buffer, data, size);
            buffer[size] = '\0';

            // Attempt to parse the buffer into an icalcomponent
            icalcomponent *parsed_component = icalparser_parse_string(buffer);
            if (parsed_component != NULL) {
                // Initialize the iterator with the parsed component
                iter = icalcomponent_begin_component(parsed_component, ICAL_ANY_COMPONENT);

                // Call the function-under-test
                icalcomponent *prior_component = icalcompiter_prior(&iter);

                // Clean up
                icalcomponent_free(parsed_component);
            }

            free(buffer);
        }
    }

    // Clean up
    icalcomponent_free(component);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_6(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
