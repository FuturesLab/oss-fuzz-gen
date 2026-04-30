#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_341(const uint8_t *data, size_t size) {
    // Initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_DTEND_PROPERTY);

    // Ensure that the data is not empty and can be used to set a value
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            icalproperty_free(prop);
            return 0;
        }

        // Copy the data into the temporary buffer and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';

        // Set the property value using the data
        icalvalue *value = icalvalue_new_from_string(ICAL_DATETIME_VALUE, temp_data);
        if (value != NULL) {
            icalproperty_set_value(prop, value);
        }

        // Free the temporary buffer
        free(temp_data);
    }

    // Call the function-under-test
    struct icaltimetype dtend = icalproperty_get_dtend(prop);

    // Clean up
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

    LLVMFuzzerTestOneInput_341(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
