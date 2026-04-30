#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Added for malloc and free
#include <string.h>  // Added for memcpy

extern "C" {
    #include <libical/ical.h>  // Corrected to include the appropriate path for ical headers

    icalcomponent_kind icalcomponent_isa(const icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data for the icalcomponent
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Ensure the component is not NULL before calling the function
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_kind kind = icalcomponent_isa(component);

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

    LLVMFuzzerTestOneInput_59(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
