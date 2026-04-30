#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_574(const uint8_t *data, size_t size) {
    // Allocate memory for the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_XLICMIMECID_PROPERTY);

    // Ensure the data is not empty and size is reasonable
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to hold the data
        char *buffer = static_cast<char*>(malloc(size + 1));
        if (buffer != NULL) {
            // Copy the data into the buffer and null-terminate it
            memcpy(buffer, data, size);
            buffer[size] = '\0';

            // Set the xlicmimecid property using the buffer
            icalproperty_set_xlicmimecid(property, buffer);

            // Call the function-under-test
            const char *result = icalproperty_get_xlicmimecid(property);

            // Check the result to ensure the function is being tested
            if (result != NULL) {
                // Further processing can be done here if needed
                // For example, verifying the result matches the input
            }

            // Free the buffer
            free(buffer);
        }
    }

    // Free the icalproperty object
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_574(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
