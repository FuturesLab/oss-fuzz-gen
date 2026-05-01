#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Initialize a icalcomponent from the input data
    icalcomponent *component = nullptr;
    if (size > 0) {
        char *data_copy = (char *)malloc(size + 1);
        if (data_copy == nullptr) {
            return 0;
        }
        memcpy(data_copy, data, size);
        data_copy[size] = '\0'; // Ensure null-termination
        component = icalparser_parse_string(data_copy);
        free(data_copy);
    }

    // If component is not NULL, proceed to call the function-under-test
    if (component != nullptr) {
        // Iterate over all possible icalproperty_kind values
        for (int kind = ICAL_NO_PROPERTY; kind <= ICAL_X_PROPERTY; ++kind) {
            icalproperty_kind property_kind = static_cast<icalproperty_kind>(kind);
            // Call the function-under-test
            int count = icalcomponent_count_properties(component, property_kind);
            (void)count; // Suppress unused variable warning
        }
        // Free the component after use
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_79(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
