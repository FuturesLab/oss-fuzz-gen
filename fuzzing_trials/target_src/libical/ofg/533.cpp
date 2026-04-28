#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    // Include necessary C headers from libical
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_533(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = nullptr;
    icalproperty_kind kind = ICAL_NO_PROPERTY;

    // Ensure data is not empty
    if (size > 0) {
        // Create a string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data into an icalcomponent
        component = icalparser_parse_string(inputData);

        // Free the input data as it's no longer needed
        free(inputData);
    }

    // Iterate over a few icalproperty_kind values for fuzzing
    for (int i = ICAL_NO_PROPERTY; i <= ICAL_X_PROPERTY; ++i) {
        kind = static_cast<icalproperty_kind>(i);

        // Call the function-under-test
        if (component != nullptr) {
            int count = icalcomponent_count_properties(component, kind);
        }
    }

    // Clean up
    if (component != nullptr) {
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_533(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
