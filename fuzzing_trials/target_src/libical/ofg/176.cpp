#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a property
    if (size < 2) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a new icalproperty
    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (property == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Use the input data to set a value for the property
    char value[size + 1];
    for (size_t i = 0; i < size; ++i) {
        value[i] = static_cast<char>(data[i]);
    }
    value[size] = '\0'; // Null-terminate the string

    icalproperty_set_summary(property, value);

    // Call the function-under-test
    icalcomponent_add_property(component, property);

    // Clean up
    icalcomponent_free(component);
    // Note: The property is freed when the component is freed

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

    LLVMFuzzerTestOneInput_176(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
