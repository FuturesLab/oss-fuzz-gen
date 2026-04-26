#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Initialize the library
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == nullptr) {
        return 0;
    }

    // Create a temporary buffer to hold the property value
    char *prop_buffer = (char *)malloc(size + 1);
    if (prop_buffer == nullptr) {
        icalcomponent_free(component);
        return 0;
    }

    // Copy data into the buffer and null-terminate it
    memcpy(prop_buffer, data, size);
    prop_buffer[size] = '\0';

    // Create an icalproperty from the buffer
    icalproperty *property = icalproperty_new_from_string(prop_buffer);
    free(prop_buffer);

    if (property == nullptr) {
        icalcomponent_free(component);
        return 0;
    }

    // Call the function-under-test
    struct icaldurationtype duration = icalproperty_get_refreshinterval(property);

    // Clean up
    icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_72(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
