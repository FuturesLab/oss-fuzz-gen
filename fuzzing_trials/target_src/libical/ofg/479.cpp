#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_479(const uint8_t *data, size_t size) {
    // Ensure that the size is non-zero for valid string creation
    if (size == 0) {
        return 0;
    }

    // Initialize a dummy icalproperty object
    icalproperty *property = icalproperty_new(ICAL_LOCATION_PROPERTY);
    if (property == NULL) {
        return 0; // Exit if unable to create a new property
    }

    // Create a null-terminated string from the input data
    char *location = (char *)malloc(size + 1);
    if (location == NULL) {
        icalproperty_free(property);
        return 0; // Exit if memory allocation fails
    }
    memcpy(location, data, size);
    location[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty_set_location(property, location);

    // Additional operations to increase code coverage
    const char *retrieved_location = icalproperty_get_location(property);
    if (retrieved_location != NULL) {
        // Perform some operations on the retrieved location
        size_t retrieved_length = strlen(retrieved_location);
        if (retrieved_length > 0) {
            // Example operation: check if the location contains a specific character
            if (strchr(retrieved_location, 'A') != NULL) {
                // Do something if 'A' is found in the location
            }
        }
    }

    // Clean up
    free(location);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_479(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
