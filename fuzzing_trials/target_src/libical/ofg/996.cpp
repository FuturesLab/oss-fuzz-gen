#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_996(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *ical_str = static_cast<char *>(malloc(size + 1));
    if (ical_str == nullptr) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(ical_str);
    if (prop != nullptr) {
        // Call the function-under-test
        const char *version = icalproperty_get_version(prop);

        // Optionally print the version for debugging purposes
        if (version != nullptr) {
            std::cout << "Version: " << version << std::endl;
        }

        // Free the created icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated string
    free(ical_str);

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

    LLVMFuzzerTestOneInput_996(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
