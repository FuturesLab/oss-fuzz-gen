#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_782(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 1) {
        return 0;
    }

    // Determine the property type based on the first byte of data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Allocate memory for an icalproperty object
    icalproperty *prop = icalproperty_new(kind);
    if (prop == NULL) {
        return 0;
    }

    // Copy the fuzz data into a buffer and set it as a value for the property
    char *buffer = (char *)malloc(size);
    if (buffer == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(buffer, data + 1, size - 1);
    buffer[size - 1] = '\0'; // Null-terminate the buffer

    // Set the value of the property
    icalvalue *value = icalvalue_new_string(buffer);
    if (value != NULL) {
        icalproperty_set_value(prop, value);
    }

    // Convert the property to a string
    const char *prop_str = icalproperty_as_ical_string(prop);
    if (prop_str != NULL) {
        // Parse the string back into an icalproperty
        icalproperty *parsed_prop = icalproperty_new_from_string(prop_str);
        if (parsed_prop != NULL) {
            // Perform operations on the parsed property if needed
            icalproperty_free(parsed_prop);
        }
        // No need to free prop_str as it is managed by libical
    }

    // Clean up
    free(buffer);
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

    LLVMFuzzerTestOneInput_782(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
