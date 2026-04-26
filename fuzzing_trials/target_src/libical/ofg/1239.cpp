#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1239(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string for icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data as a string
    char *ical_data = new char[size + 1];
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Ensure the component is not NULL before calling the function
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *parent = icalcomponent_get_parent(component);

        // Normally, you would do something with 'parent', but for fuzzing, we just ensure the call is made
        (void)parent;

        // Clean up
        icalcomponent_free(component);
    }

    // Clean up the temporary buffer
    delete[] ical_data;

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

    LLVMFuzzerTestOneInput_1239(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
