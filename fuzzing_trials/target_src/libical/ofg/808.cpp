#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include the header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_808(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string for icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_string);
    if (comp == NULL) {
        free(ical_string);
        return 0;
    }

    // Iterate over properties and call the function-under-test
    for (icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY)) {
        // Call the function-under-test
        int offset = icalproperty_get_tzoffsetfrom(prop);
        (void)offset;  // Suppress unused variable warning
    }

    // Clean up
    icalcomponent_free(comp);
    free(ical_string);

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

    LLVMFuzzerTestOneInput_808(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
