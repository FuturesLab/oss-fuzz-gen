#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdarg>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_822(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Ensure null-termination of the string
    char *str = new char[size + 1];
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test with a sentinel
    icalproperty *prop = icalproperty_vanew_target(str, nullptr);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Attempt to retrieve the string value to ensure the property is used
        const char* retrieved_str = icalproperty_get_target(prop);
        if (retrieved_str != nullptr) {
            // Perform some operation with the retrieved string
            // For example, compare it with the original to ensure it was set correctly
            if (strcmp(retrieved_str, str) != 0) {
                // Log or handle discrepancy if needed
            }
        }

        // Clean up
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

    LLVMFuzzerTestOneInput_822(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
