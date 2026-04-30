#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used
    if (size < 2) {
        return 0;
    }

    // Create a dummy icalproperty and icalcomponent
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Call the function under test
    icalproperty_set_parent(property, component);

    // Clean up
    icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
