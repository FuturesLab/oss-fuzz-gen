#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_322(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be a valid string
    if (size == 0 || data[size - 1] != '\0') {
        return 0; // Ensure null-terminated string
    }

    // Convert input data to a string
    const char* input = reinterpret_cast<const char*>(data);

    // Use the input to create an icaltime
    struct icaltimetype result = icaltime_from_string(input);

    // Check if the result is valid to increase code coverage
    if (!icaltime_is_null_time(result)) {
        // Perform some operation with the result to ensure it's processed
        const char* output = icaltime_as_ical_string(result);
        if (output) {
            // Free the output string if it was allocated
            icalmemory_free_buffer(const_cast<char*>(output));
        }
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

    LLVMFuzzerTestOneInput_322(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
