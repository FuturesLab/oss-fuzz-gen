#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

// Ensure standard libraries are included before project-specific libraries
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_864(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < 1) return 0;

    // Select a property type based on the first byte of input data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Create a icalproperty object of the selected kind
    icalproperty *prop = icalproperty_new(kind);

    // Use the input data to set a property value if possible
    if (prop != NULL && size > 1) {
        // Create a string from the input data
        char *input_str = (char *)malloc(size);
        if (input_str == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(input_str, data + 1, size - 1);
        input_str[size - 1] = '\0';

        // Set a property value using the input data
        switch (kind) {
            case ICAL_COMMENT_PROPERTY:
                icalproperty_set_comment(prop, input_str);
                break;
            case ICAL_DESCRIPTION_PROPERTY:
                icalproperty_set_description(prop, input_str);
                break;
            // Add more cases for different property types if needed
            default:
                break;
        }

        // Call the function-under-test
        icalproperty_participanttype result = icalproperty_get_participanttype(prop);

        // Clean up
        free(input_str);
    }

    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_864(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
