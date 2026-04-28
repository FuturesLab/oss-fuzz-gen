extern "C" {
#include "libical/icalproperty.h"
#include <string.h> // Include for memcpy
}

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_1025(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = new char[size + 1];
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function under test
    icalproperty *prop = icalproperty_vanew_source(str, nullptr);

    // Additional steps to increase code coverage
    if (prop != nullptr) {
        // Attempt to access some property attributes
        const char *source = icalproperty_get_source(prop);
        if (source != nullptr) {
            // Process the source string to trigger more code paths
            size_t source_len = strlen(source);
            for (size_t i = 0; i < source_len; ++i) {
                // Dummy operation to simulate processing
                volatile char c = source[i];
                (void)c;
            }
        }

        // Free the property
        icalproperty_free(prop);
    }

    delete[] str;

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

    LLVMFuzzerTestOneInput_1025(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
