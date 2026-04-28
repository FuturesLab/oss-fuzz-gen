#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    // Initialize libical
    icalerror_set_error_state(ICAL_MALFORMEDDATA_ERROR, ICAL_ERROR_NONFATAL);

    // Ensure the input size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into an icalproperty
    icalproperty *property = icalproperty_new_from_string(input_data);

    // Call the function-under-test
    if (property != NULL) {
        icalcomponent *parent = icalproperty_get_parent(property);

        // Use the parent component if necessary
        // (For fuzzing purposes, we don't need to do anything specific with it)
    }

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(input_data);

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

    LLVMFuzzerTestOneInput_258(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
