#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
#include <libical/ical.h>
#include <libical/icalparameter.h>  // Include for icalparameter functions
}

extern "C" int LLVMFuzzerTestOneInput_628(const uint8_t *data, size_t size) {
    // Check if the size of the data is sufficient to perform operations
    if (size == 0) {
        return 0;
    }

    // Initialize the icalparameter
    icalparameter *parameter = icalparameter_new(ICAL_ANY_PARAMETER);
    if (parameter == NULL) {
        return 0;
    }

    // Use the data to set a parameter value
    // Copy data into a null-terminated string for safe use
    char buffer[256];
    size_t copy_size = size < sizeof(buffer) - 1 ? size : sizeof(buffer) - 1;
    memcpy(buffer, data, copy_size);
    buffer[copy_size] = '\0';

    // Set the parameter value using the fuzz data
    icalparameter_set_x(parameter, buffer);

    // Get the parameter value
    const char *value = icalparameter_get_x(parameter);

    // Perform additional operations to increase code coverage
    if (value != NULL) {
        // Example: Compare the set and retrieved values
        if (strcmp(buffer, value) != 0) {
            // Handle unexpected behavior if necessary
        }
    }

    // Clean up
    icalparameter_free(parameter);

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

    LLVMFuzzerTestOneInput_628(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
