#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xdaylight();

    // Perform basic operations on the component to ensure it's valid
    if (component != NULL) {
        // Add a property to the component
        icalproperty *prop = icalproperty_new_comment("Fuzzing test");
        icalcomponent_add_property(component, prop);

        // Convert the component to a string and print it (for debugging purposes)
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // In a real fuzzing scenario, you might want to log or further process the string
            // Here we just ensure that the conversion to string works
        }

        // Clean up
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

    LLVMFuzzerTestOneInput_15(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
