#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    // Create a temporary buffer to hold the data for the icalproperty
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }
    
    // Copy data into buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);
    free(buffer);

    if (component == NULL) {
        return 0;
    }

    // Iterate over properties in the component
    for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {

        // Call the function-under-test
        int percent_complete = icalproperty_get_percentcomplete(prop);
        (void)percent_complete; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_257(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
