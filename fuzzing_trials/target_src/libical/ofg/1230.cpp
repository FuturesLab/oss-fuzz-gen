#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1230(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Ensure there is some data to work with
    if (size < sizeof(int)) {
        icalcomponent_free(component);
        return 0;
    }

    // Use the first four bytes of data as an integer for the sequence
    int sequence = 0;
    for (size_t i = 0; i < sizeof(int) && i < size; ++i) {
        sequence |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    icalcomponent_set_sequence(component, sequence);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1230(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
