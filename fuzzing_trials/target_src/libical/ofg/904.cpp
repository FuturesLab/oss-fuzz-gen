#include <cstdint>
#include <cstddef>
#include <cstring>
#include <stdexcept>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_904(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = new char[size + 1];
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test
    try {
        icalproperty *prop = icalproperty_vanew_recurlimit(str, nullptr);

        // Check if the property is valid and perform additional operations if needed
        if (prop != nullptr) {
            // Optionally, perform operations on `prop` to ensure that it is being used
            // For example, you might want to check its type or other properties
            icalproperty_kind kind = icalproperty_isa(prop);
            if (kind == ICAL_RECURLIMIT_PROPERTY) {  // Corrected the identifier
                // Perform additional operations if needed
            }

            // Clean up
            icalproperty_free(prop);
        }
    } catch (const std::exception &e) {
        // Handle any exceptions that may arise
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

    LLVMFuzzerTestOneInput_904(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
