#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_366(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *tzurl = new char[size + 1];
    std::memcpy(tzurl, data, size);
    tzurl[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_tzurl(tzurl);

    // Additional operations to increase code coverage
    if (prop != NULL) {
        // Access some properties or perform operations to ensure the function is used effectively
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_TZURL_PROPERTY) {
            const char *retrieved_tzurl = icalproperty_get_tzurl(prop);
            if (retrieved_tzurl != NULL) {
                // Compare or use the retrieved_tzurl to ensure it's processed
                std::strcmp(retrieved_tzurl, tzurl);
            }
        }

        // Clean up
        icalproperty_free(prop);
    }
    
    delete[] tzurl;

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

    LLVMFuzzerTestOneInput_366(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
