extern "C" {
#include <libical/ical.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating an icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to store the input data as a string
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalcomponent from the input data
    icalcomponent *component = icalparser_parse_string(inputData);
    free(inputData);

    if (component != nullptr) {
        // Call the function-under-test
        char *icalString = icalcomponent_as_ical_string_r(component);

        // Free the returned string if it's not nullptr
        if (icalString != nullptr) {
            free(icalString);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_121(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
