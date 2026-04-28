#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
#include <libical/ical.h>

// Define a callback function that matches the expected signature for icalcomponent_foreach_tzid
void tzid_callback(icalparameter *param, void *data) {
    // This is a placeholder callback function.
    // You can implement any logic here if needed for testing.
}

int LLVMFuzzerTestOneInput_722(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Parse the buffer into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(buffer);
    free(buffer);

    if (comp == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent_foreach_tzid(comp, tzid_callback, NULL);

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_722(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
