#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Initialize the library
    icalerror_clear_errno();

    // Create a temporary string buffer to hold the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(input);
    free(input);

    if (comp == NULL) {
        return 0; // Exit if parsing fails
    }

    // Iterate over properties using icalcomponent_get_first_property
    icalproperty *prop;
    for (prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY)) {
        // Perform operations on the property if needed
        // For now, just assert that the property is not NULL
        assert(prop != NULL);
    }

    // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_123(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
