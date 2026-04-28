#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Initialize the fuzzing inputs
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Ensure that the inputs are not NULL
    if (property == NULL || component == NULL) {
        return 0;
    }

    // Call the function-under-test
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_188(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
