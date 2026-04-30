#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1365(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an enumeration value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_querylevel querylevel = static_cast<icalproperty_querylevel>(data[0] % 3);

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_querylevel(querylevel, nullptr);

    // Clean up if necessary
    if (prop != nullptr) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_1365(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
