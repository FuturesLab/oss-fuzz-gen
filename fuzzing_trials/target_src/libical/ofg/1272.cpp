#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_1272(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and has a minimum length
    if (size < 3) { // Assuming a minimum length for a valid TZID
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *tzid = new char[size + 1];
    std::memcpy(tzid, data, size);
    tzid[size] = '\0';  // Null-terminate the string

    // Check if the tzid is a valid string for the function under test
    // For example, a valid TZID might need to be in a specific format
    // Here, we just print it for debugging purposes
    std::cout << "Testing TZID: " << tzid << std::endl;

    // Call the function under test
    icalproperty *prop = icalproperty_new_tzid(tzid);

    // Clean up
    if (prop != nullptr) {
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

    LLVMFuzzerTestOneInput_1272(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
