#include <string.h>
#include <sys/stat.h>
extern "C" {
#include "libical/ical.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    // Ensure the data can be null-terminated
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_VERSION_PROPERTY);

    // Null-terminate the data to safely convert it to a C-string
    char *version = new char[size + 1];
    memcpy(version, data, size);
    version[size] = '\0';

    // Call the function-under-test
    icalproperty_set_version(property, version);

    // Verify the version property is set correctly
    const char *set_version = icalproperty_get_version(property);
    if (set_version && strcmp(set_version, version) == 0) {
        std::cout << "Version set correctly: " << set_version << std::endl;
    } else {
        std::cout << "Version set incorrectly or not set." << std::endl;
    }

    // Clean up
    icalproperty_free(property);
    delete[] version;

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

    LLVMFuzzerTestOneInput_402(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
