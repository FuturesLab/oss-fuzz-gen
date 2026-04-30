#include <sys/stat.h>
#include <string.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data and ensure it's null-terminated
    char *buffer = static_cast<char*>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Free the buffer as it's no longer needed
    free(buffer);

    if (component == nullptr) {
        return 0;
    }

    // Iterate over a few icalproperty_kind values to test the function
    for (int kind = ICAL_ANY_PROPERTY; kind <= ICAL_X_PROPERTY; ++kind) {
        icalcomponent_count_properties(component, static_cast<icalproperty_kind>(kind));
    }

    // Clean up the icalcomponent
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

    LLVMFuzzerTestOneInput_14(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
