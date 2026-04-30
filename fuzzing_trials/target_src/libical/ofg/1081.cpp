#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1081(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vvoter();

    // Perform basic operations to ensure the component is used
    if (component != NULL) {
        // Convert the component to a string and print it
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally, we might print or log the string, but for fuzzing, we just ensure it's not NULL
            // printf("%s\n", str); // Uncomment if needed for debugging
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

    LLVMFuzzerTestOneInput_1081(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
