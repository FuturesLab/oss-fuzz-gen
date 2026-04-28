#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <cstdlib> // For malloc and free
#include <cstring> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1032(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *ical_data = (char *)malloc(size + 1);
    if (!ical_data) return 0;
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the iCalendar data to create an icalcomponent
    icalcomponent *root_component = icalparser_parse_string(ical_data);

    // Free the allocated data
    free(ical_data);

    if (root_component != NULL) {
        // Call the function-under-test
        icalcomponent *first_real_component = icalcomponent_get_first_real_component(root_component);

        // Do something with the result if needed
        // ...

        // Free the icalcomponent
        icalcomponent_free(root_component);
    }

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

    LLVMFuzzerTestOneInput_1032(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
