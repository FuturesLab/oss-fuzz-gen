#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_951(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size == 0) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_LOCATION_PROPERTY);
    if (prop == nullptr) {
        return 0; // Exit if the property creation fails
    }

    // Set the location using the input data, ensuring it's null-terminated
    char *location = (char *)malloc(size + 1);
    if (location == nullptr) {
        icalproperty_free(prop);
        return 0; // Exit if memory allocation fails
    }
    memcpy(location, data, size);
    location[size] = '\0';

    // Use the input data to set the location
    icalproperty_set_location(prop, location);

    // Additionally, test other related functions to increase coverage
    const char *result = icalproperty_get_location(prop);
    if (result != nullptr) {
        // Compare the result with the input location
        if (strcmp(result, location) == 0) {
            // Placeholder to ensure the compiler does not optimize away the comparison
            volatile int dummy = 0;
            dummy += result[0];
        }
    }

    // Convert the property to a string and back to test serialization/deserialization
    const char *prop_str = icalproperty_as_ical_string(prop); // Changed char * to const char *
    if (prop_str != nullptr) {
        icalproperty *parsed_prop = icalproperty_new_from_string(prop_str);
        if (parsed_prop != nullptr) {
            icalproperty_free(parsed_prop);
        }
        free((void*)prop_str); // Cast to void* to free const char*
    }

    // Clean up
    icalproperty_free(prop);
    free(location);

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

    LLVMFuzzerTestOneInput_951(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
