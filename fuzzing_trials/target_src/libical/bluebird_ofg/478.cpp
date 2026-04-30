#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_478(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xpatch();

    // Perform some basic operations on the returned component to ensure it's valid
    if (component != NULL) {
        // For example, let's convert it to a string and then free it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string for debugging (optional)
            // printf("%s\n", component_str);

            // Free the string
            icalmemory_free_buffer(component_str);
        }

        // Free the component
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_478(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
