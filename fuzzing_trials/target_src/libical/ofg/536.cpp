#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_536(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be used
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold a null-terminated string
    char *buffer = static_cast<char*>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalproperty from the buffer
    icalproperty *prop = icalproperty_new_from_string(buffer);

    // Ensure the property is valid before proceeding
    if (prop != nullptr) {
        // Call the function under test
        const char *result = icalproperty_as_ical_string(prop);

        // Optionally, do something with the result to avoid compiler optimizations
        if (result != nullptr) {
            volatile size_t result_length = strlen(result);
            (void)result_length; // Use the result_length to avoid unused variable warning
        }

        // Clean up
        icalproperty_free(prop);
    }

    // Free the temporary buffer
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
