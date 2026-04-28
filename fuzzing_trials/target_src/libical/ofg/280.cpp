#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure data is non-empty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzidaliasof = new char[size + 1];
    std::memcpy(tzidaliasof, data, size);
    tzidaliasof[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_tzidaliasof(tzidaliasof);

    // Check if the property was created successfully and perform operations
    if (property != nullptr) {
        // For fuzzing effectiveness, attempt to access or manipulate the property
        // This can help increase code coverage by exercising more code paths
        const char *retrieved_tzidaliasof = icalproperty_get_tzidaliasof(property);
        if (retrieved_tzidaliasof != nullptr) {
            std::cout << "Retrieved TZID alias: " << retrieved_tzidaliasof << std::endl;
        }
        icalproperty_free(property);
    }

    delete[] tzidaliasof;

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

    LLVMFuzzerTestOneInput_280(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
