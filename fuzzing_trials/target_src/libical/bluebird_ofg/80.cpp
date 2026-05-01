#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Convert the input data to a string
    char *ical_str = (char *)malloc(size + 1);
    if (!ical_str) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_str);

    // Free the allocated string
    free(ical_str);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype recurrence_id = icalcomponent_get_recurrenceid(component);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_80(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
