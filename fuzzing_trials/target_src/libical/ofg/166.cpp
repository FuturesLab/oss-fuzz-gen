#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();

    // Check if the vcalendar was created successfully
    if (vcalendar != NULL) {
        // Perform operations on the vcalendar if needed
        // For example, add properties or subcomponents

        // Clean up and free the vcalendar component
        icalcomponent_free(vcalendar);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_166(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
