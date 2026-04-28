#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_991(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int maxresultssize = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        maxresultssize |= data[i] << (i * 8);
    }

    // Use the remaining data as a string for extra data
    char *extra_data = nullptr;
    if (size > sizeof(int)) {
        size_t extra_data_size = size - sizeof(int);
        extra_data = (char *)malloc(extra_data_size + 1);
        if (extra_data == nullptr) {
            return 0;
        }
        memcpy(extra_data, data + sizeof(int), extra_data_size);
        extra_data[extra_data_size] = '\0'; // Null-terminate the string
    }

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_maxresultssize(maxresultssize, extra_data, nullptr);

    // Clean up if necessary
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(extra_data);

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

    LLVMFuzzerTestOneInput_991(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
