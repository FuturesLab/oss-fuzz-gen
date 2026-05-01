#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include the header for memcpy

// Ensure C linkage for the function-under-test
extern "C" {
    struct icaltimetype icalproperty_get_datetime_with_component(icalproperty *, icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    icalproperty *property = nullptr;
    icalcomponent *component = nullptr;
    struct icaltimetype datetime;

    // Create an icalproperty from the input data if size is sufficient
    if (size > 0) {
        // Create a string from the input data
        char *str = (char *)malloc(size + 1);
        if (str == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(str, data, size);
        str[size] = '\0';

        // Attempt to parse the input string into an icalproperty
        property = icalproperty_new_from_string(str);
        free(str);

        // Create a basic icalcomponent for testing
        component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

        // Ensure neither property nor component is NULL before calling the function
        if (property != nullptr && component != nullptr) {
            // Call the function-under-test
            datetime = icalproperty_get_datetime_with_component(property, component);
        }

        // Clean up allocated resources
        if (property != nullptr) {
            icalproperty_free(property);
        }
        if (component != nullptr) {
            icalcomponent_free(component);
        }
    }

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

    LLVMFuzzerTestOneInput_115(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
