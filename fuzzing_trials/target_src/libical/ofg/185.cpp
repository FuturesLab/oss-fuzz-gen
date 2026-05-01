#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Ensure there is data to process
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Ensure the component is not NULL before proceeding
    if (component != NULL) {
        // Call the function-under-test
        const char *summary = icalcomponent_get_summary(component);

        // Use the summary in some way to avoid compiler optimizations
        if (summary != NULL) {
            std::cout << "Summary: " << summary << std::endl;
        }

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_185(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
