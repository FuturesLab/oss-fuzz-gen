#include <sys/stat.h>
#include <string.h>
#include <cstdint>
#include <cstdlib>
#include "libical/ical.h"
#include <cstring>

extern "C" {

// Define a callback function that matches the correct signature
void tzid_callback(icalparameter *param, void *data) {
    // Implement a simple callback that does nothing.
    // This is just a placeholder to match the function signature.
}

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // If memory allocation fails, return early
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a new icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    // Free the allocated null-terminated data
    free(null_terminated_data);

    if (component == NULL) {
        return 0; // If the component is NULL, return early
    }

    // Call the function-under-test with the component, callback, and user data
    icalcomponent_foreach_tzid(component, tzid_callback, NULL);

    // Free the icalcomponent after use
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
