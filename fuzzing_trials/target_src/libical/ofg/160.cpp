#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Use the buffer to create an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Check if the component was created successfully
    if (component != nullptr) {
        // Call the function-under-test
        icalcomponent_convert_errors(component);

        // Clean up the created component
        icalcomponent_free(component);
    }

    // Free the allocated buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_160(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
