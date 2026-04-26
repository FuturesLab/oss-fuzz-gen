#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_926(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create an icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Free the input data buffer
    free(inputData);

    if (component != nullptr) {
        // Call the function-under-test
        char *tzNames = icaltimezone_get_tznames_from_vtimezone(component);

        // Free the result if it was allocated
        if (tzNames != nullptr) {
            free(tzNames);
        }

        // Free the icalcomponent
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

    LLVMFuzzerTestOneInput_926(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
