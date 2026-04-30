#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

// Fuzzing harness for icalcomponent_new_vfreebusy
extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vfreebusy();

    // Check if the component is created successfully
    if (component != nullptr) {
        // Perform operations on the component if needed
        // For example, convert the component to a string and print it
        char *str = icalcomponent_as_ical_string(component);
        if (str != nullptr) {
            // Normally, you might do something with str, like logging or further processing
            // but for this fuzzing harness, we'll just ensure it's created
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

    LLVMFuzzerTestOneInput_2(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
