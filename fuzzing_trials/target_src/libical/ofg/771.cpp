#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    // No need to redeclare icalproperty_vanew_owner as it is already declared in the included header
}

extern "C" int LLVMFuzzerTestOneInput_771(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *owner_str = new char[size + 1];
    std::memcpy(owner_str, data, size);
    owner_str[size] = '\0';

    // Call the function-under-test with a sentinel value
    icalproperty *property = icalproperty_vanew_owner(owner_str, nullptr);

    // Clean up
    delete[] owner_str;
    if (property != nullptr) {
        icalproperty_free(property);
    }

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

    LLVMFuzzerTestOneInput_771(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
