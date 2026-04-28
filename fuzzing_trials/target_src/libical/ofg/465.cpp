#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_465(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = nullptr;
    icalproperty_kind kind = ICAL_NO_PROPERTY;

    // Ensure that the size is sufficient to create a valid icalcomponent
    if (size > 0) {
        // Create a temporary string buffer from the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the string

        // Parse the input data to create an icalcomponent
        component = icalparser_parse_string(buffer);

        // Free the buffer as it is no longer needed
        free(buffer);

        // If the component is successfully created, proceed to fuzz the function
        if (component != nullptr) {
            // Iterate over all possible property kinds
            for (int i = ICAL_NO_PROPERTY; i <= ICAL_X_PROPERTY; ++i) {
                kind = static_cast<icalproperty_kind>(i);
                
                // Call the function-under-test
                icalproperty *property = icalcomponent_get_next_property(component, kind);

                // Optionally, perform some operations on the returned property
                if (property != nullptr) {
                    // Example operation: get the property name
                    const char *property_name = icalproperty_kind_to_string(icalproperty_isa(property));
                }
            }

            // Free the component after use
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_465(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
