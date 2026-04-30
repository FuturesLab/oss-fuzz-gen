#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy and strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == nullptr) return 0;
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != nullptr) {
        // Call the function-under-test
        const char *organizer = icalproperty_get_organizer(prop);

        // Use the result in some way to prevent optimization out
        if (organizer != nullptr) {
            // Print the organizer to a buffer or do some other operation
            // (for demonstration purposes, we will just check its length)
            size_t length = strlen(organizer);
            (void)length; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_61(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
