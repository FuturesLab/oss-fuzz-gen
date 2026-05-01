#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Check if the data size is sufficient to perform meaningful operations
    if (size == 0) {
        return 0;  // No data to process
    }

    // Call the function-under-test
    icalcomponent *vevent = icalcomponent_new_vevent();
    
    // Check if the vevent was created successfully
    if (vevent != NULL) {
        // Perform operations on the vevent if necessary
        // For example, you might want to add properties or subcomponents
        // Here, we just clean up the created component

        // Free the created vevent component
        icalcomponent_free(vevent);
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

    LLVMFuzzerTestOneInput_69(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
