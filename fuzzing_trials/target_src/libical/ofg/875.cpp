#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_875(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a non-empty string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *location = new char[size + 1];
    memcpy(location, data, size);
    location[size] = '\0';

    // Call the function-under-test with non-null inputs
    icalproperty *prop = icalproperty_vanew_location(location, nullptr);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Perform additional operations to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_LOCATION_PROPERTY) {
            const char *retrieved_location = icalproperty_get_location(prop);
            if (retrieved_location && strcmp(retrieved_location, location) == 0) {
                // Further operations can be added here to maximize coverage
                // Example: Modify the location property and check the result
                icalproperty_set_location(prop, "New Location");
                const char *new_location = icalproperty_get_location(prop);
                if (new_location && strcmp(new_location, "New Location") == 0) {
                    // Additional checks or operations
                }
            }
        }

        // Clean up
        icalproperty_free(prop);
    }

    delete[] location;

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

    LLVMFuzzerTestOneInput_875(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
