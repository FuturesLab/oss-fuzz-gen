#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_432(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a non-null string
    if (size == 0) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a location string from the input data
    char *location = (char *)malloc(size + 1);
    if (location == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(location, data, size);
    location[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalcomponent_set_location(component, location);

    // Additional operations to ensure code coverage
    // Retrieve the location to ensure it's set correctly
    const char *retrieved_location = icalcomponent_get_location(component);
    if (retrieved_location != NULL) {
        // Perform some operation with the retrieved location
        // This ensures the fuzz target actually uses the set location
        printf("Retrieved location: %s\n", retrieved_location);
    }

    // Clean up
    free(location);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_432(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
