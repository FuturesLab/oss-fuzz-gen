#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy and strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1155(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != nullptr) {
        // Call the function-under-test
        const char *result = icalproperty_get_recuraccepted(prop);

        // Use the result in some way to prevent it from being optimized away
        if (result != nullptr) {
            // Just print the result length for debugging purposes
            size_t resultLength = strlen(result);
            (void)resultLength;
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_1155(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
