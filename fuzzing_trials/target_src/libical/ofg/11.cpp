#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize libical
    icalcomponent *component = NULL;
    icaltimetype dtend;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the input data into an icalcomponent
    component = icalparser_parse_string(ical_str);

    // Call the function-under-test if the component is successfully created
    if (component != NULL) {
        dtend = icalcomponent_get_dtend(component);
        // Optionally, you can add additional checks or operations on dtend
    }

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(ical_str);

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

    LLVMFuzzerTestOneInput_11(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
