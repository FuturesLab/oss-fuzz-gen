#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xdaylight();

    // Perform any other operations or checks on the component if needed
    if (component != NULL) {
        // Example: Convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally you might use the component_str for further processing
            // For fuzzing purposes, we just ensure it is not NULL
            // In a real fuzzing scenario, you might want to log or check this string
        }

        // Free the component after use
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_14(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
