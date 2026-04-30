#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_802(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize libical
    icalcomponent *comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Use the input data to set a property value, ensuring it's not null
    char *value = (char*)malloc(size + 1);
    if (value == NULL) {
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    // Create a new pollproperties property with the input value
    icalproperty *prop = icalproperty_new_pollproperties(value);

    // Add property to component
    icalcomponent_add_property(comp, prop);

    // Call the function-under-test
    const char *result = icalproperty_get_pollproperties(prop);

    // Clean up
    free(value);
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_802(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
