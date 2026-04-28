#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract both an icalcomponent and a status
    if (size < 2) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Extract status from the input data
    icalproperty_status status = static_cast<icalproperty_status>(data[0]);

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new_status(status);

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcomponent_set_status(component, status);

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

    LLVMFuzzerTestOneInput_392(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
