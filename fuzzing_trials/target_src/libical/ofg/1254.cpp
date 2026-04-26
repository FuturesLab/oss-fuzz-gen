#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_1254(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzid = new char[size + 1];
    std::memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Validate the input to ensure it's a plausible TZID
    if (std::strlen(tzid) == 0 || std::strchr(tzid, '/') == nullptr) {
        delete[] tzid;
        return 0;
    }

    // Call the function under test
    icalproperty *prop = icalproperty_vanew_tzid(tzid, nullptr);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Perform additional operations to ensure the function is utilized
        const char *retrieved_tzid = icalproperty_get_tzid(prop);
        if (retrieved_tzid) {
            // Optionally perform assertions or further operations
            std::cout << "Retrieved TZID: " << retrieved_tzid << std::endl;
        }

        // Clean up
        icalproperty_free(prop);
    }

    delete[] tzid;

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

    LLVMFuzzerTestOneInput_1254(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
