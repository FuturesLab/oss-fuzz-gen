#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vvoter();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert it to a string and print (for debugging purposes)
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // In a real fuzzing scenario, you might want to do more with the string
            // Here, we simply print it (commented out to avoid cluttering output)
            // printf("%s\n", component_str);
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

    LLVMFuzzerTestOneInput_153(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
