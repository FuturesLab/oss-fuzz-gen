#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include "libical/ical.h"
#include <cstring> // Include for strlen

extern "C" {

// Callback function that matches the required signature for icalcomponent_foreach_tzid
void tzid_callback(icalparameter *param, void *data) {
    // Example callback function that does nothing
}

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0; // Handle memory allocation failure
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize an icalcomponent from the data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);
    free(null_terminated_data); // Free the allocated memory
    if (component == NULL) {
        return 0;
    }

    // Define a non-null pointer for the third parameter
    void *user_data = (void *)1; // Arbitrary non-null pointer

    // Call the function-under-test
    icalcomponent_foreach_tzid(component, tzid_callback, user_data);

    // Clean up
    icalcomponent_free(component);

    return 0;
}

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

    LLVMFuzzerTestOneInput_56(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
