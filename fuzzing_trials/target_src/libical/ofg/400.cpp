#include <cstdint> // Include standard library for uint8_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_400(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int tzoffsetto = *(reinterpret_cast<const int*>(data));

    // Create a dummy non-NULL pointer for the second argument
    void *dummyPtr = reinterpret_cast<void*>(0x1);

    // Call the function-under-test with a sentinel value
    icalproperty *property = icalproperty_vanew_tzoffsetto(tzoffsetto, dummyPtr, nullptr);

    // Clean up the created icalproperty object
    if (property != NULL) {
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

    LLVMFuzzerTestOneInput_400(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
