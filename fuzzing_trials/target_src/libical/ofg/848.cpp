#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_848(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract both parameters
    if (size < sizeof(icalproperty_kind) + sizeof(int)) {
        return 0;
    }

    // Extract the icalproperty_kind from the input data
    icalproperty_kind kind;
    std::memcpy(&kind, data, sizeof(icalproperty_kind));

    // Extract the integer value from the input data
    int value;
    std::memcpy(&value, data + sizeof(icalproperty_kind), sizeof(int));

    // Call the function under test
    bool result = icalproperty_enum_belongs_to_property(kind, value);

    // Use the result to avoid any compiler optimizations that might skip the call
    volatile bool avoid_optimization = result;

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

    LLVMFuzzerTestOneInput_848(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
