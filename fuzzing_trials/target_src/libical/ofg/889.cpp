#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_889(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char*>(malloc(size + 1));
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If the component is successfully parsed, extract the first property
    if (component != NULL) {
        icalproperty *property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

        // If a property is found, call the function-under-test
        if (property != NULL) {
            const char *error = icalproperty_get_xlicerror(property);

            // Use the error value in some way to prevent optimization out
            if (error != NULL) {
                // Do something with error, like printing or logging
            }
        }

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the buffer
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_889(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
