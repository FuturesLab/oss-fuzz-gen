#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h>  // Assuming the correct path for libical header
}

extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the input data is not empty and has a reasonable size
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to store the input data as a string
        char *input_data = (char *)malloc(size + 1);
        if (input_data != NULL) {
            // Copy the input data and null-terminate it
            memcpy(input_data, data, size);
            input_data[size] = '\0';

            // Set the summary of the component using the input data
            icalcomponent_set_summary(component, input_data);

            // Call the function-under-test
            const char *summary = icalcomponent_get_summary(component);

            // Optionally, perform some checks or operations with the summary
            if (summary != NULL) {
                // Example operation: print the summary
                // printf("Summary: %s\n", summary);
            }

            // Free the allocated memory for input_data
            free(input_data);
        }
    }

    // Clean up the component
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_184(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
