#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" int LLVMFuzzerTestOneInput_536(const uint8_t *data, size_t size) {
    // Allocate a new buffer with an extra byte for the null terminator
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0; // If allocation fails, return early
    }

    // Copy the input data to the new buffer
    memcpy(null_terminated_data, data, size);

    // Null-terminate the copied data
    null_terminated_data[size] = '\0';

    // Create an icalcomponent from the null-terminated input data
    icalcomponent *component = icalparser_parse_string(null_terminated_data);

    // Free the null-terminated buffer
    free(null_terminated_data);

    // Ensure the component is not NULL before proceeding
    if (component != NULL) {
        // Call the function-under-test
        const char *relcalid = icalcomponent_get_relcalid(component);

        // Perform any additional operations if necessary
        // For example, you could log or check the returned relcalid

        // Free the component to avoid memory leaks
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

    LLVMFuzzerTestOneInput_536(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
