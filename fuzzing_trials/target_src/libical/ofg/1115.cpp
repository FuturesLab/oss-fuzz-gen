#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>  // Include the libical header for icalproperty and icaltimetype

extern "C" int LLVMFuzzerTestOneInput_1115(const uint8_t *data, size_t size) {
    // Initialize libical
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_exdate(icaltime_null_time());

    // Ensure the property is not NULL
    if (property == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Check if data is large enough to form a valid icaltimetype
    if (size >= sizeof(struct icaltimetype)) {
        struct icaltimetype *input_time = (struct icaltimetype *)data;
        
        // Set the exdate property with the fuzzed time
        icalproperty_set_exdate(property, *input_time);

        // Call the function under test
        struct icaltimetype exdate = icalproperty_get_exdate(property);
        
        // Use the exdate to ensure it is being processed
        if (!icaltime_is_null_time(exdate)) {
            // Perform some operation if needed
        }
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_1115(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
