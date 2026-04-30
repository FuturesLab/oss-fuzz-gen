#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_str = new char[size + 1];
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_str);

    // Ensure that the component is not NULL
    if (comp != NULL) {
        // Call the function-under-test
        struct icaltimetype dtstamp = icalcomponent_get_dtstamp(comp);

        // Clean up the component
        icalcomponent_free(comp);
    }

    // Clean up the allocated string
    delete[] ical_str;

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

    LLVMFuzzerTestOneInput_87(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
