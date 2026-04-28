#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_489(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *vjournal = icalcomponent_new_vjournal();

    // Check if the component was created successfully
    if (vjournal != NULL) {
        // Perform operations on the vjournal if necessary
        // For example, convert it to a string and print it
        char *str = icalcomponent_as_ical_string(vjournal);
        if (str != NULL) {
            // Normally, you might log or further process the string
            // Here, we just ensure the string is not NULL
        }

        // Free the string if it was allocated
        if (str != NULL) {
            icalmemory_free_buffer(str);
        }

        // Free the icalcomponent to avoid memory leaks
        icalcomponent_free(vjournal);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_489(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
