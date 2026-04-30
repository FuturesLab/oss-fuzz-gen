#include <stdint.h>

// Wrap the C headers and declarations in extern "C" to ensure proper linkage
extern "C" {
    #include <libical/icalproperty.h> // Include the correct header for icalproperty_kind and related functions
}

extern "C" int LLVMFuzzerTestOneInput_847(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract necessary parameters
    if (size < sizeof(icalproperty_kind) + sizeof(int)) {
        return 0;
    }

    // Extract parameters from the input data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);
    int enum_value = static_cast<int>(data[1]);

    // Call the function-under-test
    bool result = icalproperty_enum_belongs_to_property(kind, enum_value);

    // Use the result to avoid compiler optimizations (e.g., unused variable)
    volatile bool use_result = result;

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

    LLVMFuzzerTestOneInput_847(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
