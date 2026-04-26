#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1120(const uint8_t *data, size_t size) {
    // Ensure the data size is reasonable to avoid excessive memory usage
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char*>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalproperty object
    icalproperty *prop = icalproperty_new_from_string(buffer);
    if (prop != nullptr) {
        // Call the function-under-test
        const char *refid = icalproperty_get_refid(prop);

        // Optionally, you can perform some checks or operations on refid
        if (refid != nullptr) {
            // Example operation: check the length of refid
            size_t refid_length = strlen(refid);
            (void)refid_length; // Suppress unused variable warning
        }

        // Clean up the icalproperty object
        icalproperty_free(prop);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1120(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
