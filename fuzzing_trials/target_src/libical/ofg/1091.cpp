#include <cstdint>  // Include for uint8_t
#include <cstdlib>  // Include for malloc and free
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1091(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    icalvalue *value = icalvalue_new_string("default");

    // Check if the size is sufficient to create a string
    if (size > 0) {
        // Create a string from the data
        char *str = (char *)malloc(size + 1);
        if (str != NULL) {
            memcpy(str, data, size);
            str[size] = '\0';

            // Create a new icalvalue from the string
            icalvalue *new_value = icalvalue_new_string(str);
            if (new_value != NULL) {
                // Set the value to the property
                icalproperty_set_value(property, new_value);
            }

            // Free the allocated string
            free(str);
        }
    }

    // Clean up
    icalproperty_free(property);
    icalvalue_free(value);

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

    LLVMFuzzerTestOneInput_1091(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
