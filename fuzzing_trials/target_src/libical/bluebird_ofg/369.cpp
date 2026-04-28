#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for strlen

extern "C" {
    #include "libical/ical.h"

    // Include necessary C headers, source files, functions, and code here.
    bool icalcomponent_is_valid(const icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Return early if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Initialize the icalcomponent with some data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    // Free the allocated memory for null-terminated data
    free(null_terminated_data);

    // Ensure the component is not NULL
    if (component != NULL) {
        // Call the function-under-test
        bool is_valid = icalcomponent_is_valid(component);

        // Optionally, you can print or log the result
        // printf("Component is valid: %d\n", is_valid);

        // Free the icalcomponent after use
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

    LLVMFuzzerTestOneInput_369(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
