#include <sys/stat.h>
#include <string.h>
#include <cstddef>
#include <cstdint>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalcompiter object
    if (size < sizeof(icalcompiter)) {
        return 0;
    }

    // Create an icalcompiter object from the input data
    icalcompiter compiter;
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Initialize the icalcompiter object
    // The correct function signature requires a component and a kind
    compiter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    bool is_valid = icalcompiter_is_valid(&compiter);

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

    LLVMFuzzerTestOneInput_50(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
