#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1002(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *location_type = static_cast<char *>(malloc(size + 1));
    if (location_type == nullptr) {
        return 0;
    }

    // Copy the data to the location_type and null-terminate it
    memcpy(location_type, data, size);
    location_type[size] = '\0';

    // Call the function under test
    icalproperty *property = icalproperty_vanew_locationtype(location_type, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(location_type);

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

    LLVMFuzzerTestOneInput_1002(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
