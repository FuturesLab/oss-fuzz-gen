#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_698(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *ical_str = (char *)malloc(size + 1);
    if (!ical_str) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_str);
    free(ical_str);

    if (component == NULL) {
        return 0;
    }

    // Iterate over properties in the component
    for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {

        // Call the function-under-test
        int order = icalproperty_get_patchorder(prop);

        // Use the result in some way, e.g., print or log it
        // Here we just suppress unused variable warning
        (void)order;
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

    LLVMFuzzerTestOneInput_698(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
