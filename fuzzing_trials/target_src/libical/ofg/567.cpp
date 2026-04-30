#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_567(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalvalue
    if (size < 1) {
        return 0;
    }

    // Initialize the libical library
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Determine the kind of icalvalue to create
    icalvalue_kind kind = ICAL_STRING_VALUE; // Assuming a default kind, adjust as needed

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalvalue from the input data
    icalvalue *value = icalvalue_new_from_string(kind, null_terminated_data);

    // Clean up the temporary null-terminated data
    free(null_terminated_data);

    // Ensure the value is not NULL
    if (value == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Correctly create a property with the value
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property != NULL) {
        icalproperty_set_value(property, value);
        icalcomponent_add_property(component, property);
    }

    // Call the function under test
    char *ical_string = icalcomponent_as_ical_string(component);

    // Clean up
    if (ical_string != NULL) {
        free(ical_string);
    }
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

    LLVMFuzzerTestOneInput_567(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
