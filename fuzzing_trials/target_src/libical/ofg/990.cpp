#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_990(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int maxResultSize = *reinterpret_cast<const int*>(data);

    // Ensure maxResultSize is within a reasonable range to prevent unexpected behavior
    if (maxResultSize < 0 || maxResultSize > 1000) {
        return 0;
    }

    // Create a dummy non-NULL pointer for the void* parameter
    void* dummyPointer = reinterpret_cast<void*>(const_cast<uint8_t*>(data + sizeof(int)));

    // Call the function-under-test
    icalproperty* property = icalproperty_vanew_maxresultssize(maxResultSize, dummyPointer);

    // Clean up if necessary
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

    LLVMFuzzerTestOneInput_990(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
