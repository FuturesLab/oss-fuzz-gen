#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Initialize a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    
    // Ensure the component is not NULL
    if (component == NULL) {
        free(input_data);
        return 0;
    }

    // Add a duration property to the component using fuzzed data
    icalproperty *duration_prop = icalproperty_new_duration(icaldurationtype_from_string(input_data));
    if (duration_prop != NULL) {
        icalcomponent_add_property(component, duration_prop);

        // Call the function-under-test
        struct icaldurationtype duration = icalcomponent_get_duration(component);
    }

    // Clean up
    icalcomponent_free(component);
    free(input_data);

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

    LLVMFuzzerTestOneInput_50(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
