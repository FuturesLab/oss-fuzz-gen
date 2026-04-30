#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vtimezone();

    // Ensure the component is not NULL before proceeding
    if (component != NULL) {
        // Perform operations on the component if necessary
        // For example, convert it to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print or log the component string if needed
            // printf("%s\n", component_str); // Uncomment for debugging
        }

        // Clean up and free the component to avoid memory leaks
        icalcomponent_free(component);
    }

    return 0; // Return 0 to indicate successful execution
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

    LLVMFuzzerTestOneInput_82(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
