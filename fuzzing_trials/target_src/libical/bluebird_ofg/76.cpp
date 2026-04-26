#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    int sequence = 0;

    // Check if size is sufficient to extract an integer for sequence
    if (size >= sizeof(int)) {
        // Extract an integer from the data to use as the sequence number
        sequence = *(reinterpret_cast<const int*>(data));
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

    LLVMFuzzerTestOneInput_76(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
