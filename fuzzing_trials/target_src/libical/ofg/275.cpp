#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for icalproperty_vanew_maxresults
    int maxresults = 10; // Arbitrary non-zero integer value

    // Ensure data is not NULL and has a size greater than 0
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Create a copy of the data to pass as a void pointer
    void *user_data = malloc(size);
    if (user_data == nullptr) {
        return 0;
    }
    memcpy(user_data, data, size);

    // Call the function-under-test with a sentinel null pointer
    icalproperty *property = icalproperty_vanew_maxresults(maxresults, user_data, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(user_data);

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

    LLVMFuzzerTestOneInput_275(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
