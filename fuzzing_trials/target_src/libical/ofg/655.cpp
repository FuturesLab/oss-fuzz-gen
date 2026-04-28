#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_655(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = icalcomponent_vanew(
        ICAL_VCALENDAR_COMPONENT,
        icalproperty_new_version("2.0"),
        icalproperty_new_prodid("-//Sample Corp//NONSGML Event//EN"),
        (void *)0);

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new_summary("Sample Summary");
    icalcomponent_add_property(component, property);

    // Ensure the data is large enough to use for fuzzing
    if (size < sizeof(icalparameter_kind)) {
        icalcomponent_free(component);
        return 0;
    }

    // Use the first byte of data to determine the icalparameter_kind
    icalparameter_kind kind = static_cast<icalparameter_kind>(data[0] % ICAL_NO_PARAMETER);

    // Call the function-under-test
    icalparameter *parameter = icalproperty_get_next_parameter(property, kind);

    // Clean up
    if (parameter != NULL) {
        icalparameter_free(parameter);
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

    LLVMFuzzerTestOneInput_655(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
