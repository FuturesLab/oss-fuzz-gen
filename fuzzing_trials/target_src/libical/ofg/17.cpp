#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vfreebusy();

    // Perform operations on the component if necessary
    // For example, convert it to a string and print (usually not needed for fuzzing)
    if (component != NULL) {
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally, you would not print in a fuzzing harness
            // This is just to show that the component can be used
            // printf("%s\n", str);
        }

        // Free the string if it was allocated
        icalmemory_free_buffer(str);

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

    LLVMFuzzerTestOneInput_17(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
