#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Initialize a memory context for the icalcomponent
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Convert the input data to a string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == nullptr) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    component = icalparser_parse_string(ical_string);

    // Ensure the component is not NULL
    if (component != nullptr) {
        // Call the function-under-test
        bool result = icalcomponent_check_restrictions(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated string
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_42(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
