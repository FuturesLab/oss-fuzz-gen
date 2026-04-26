#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1273(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before using it as a string
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        return 0; // Handle allocation failure
    }

    memcpy(tzid, data, size);
    tzid[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_tzid(tzid);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(tzid);

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

    LLVMFuzzerTestOneInput_1273(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
