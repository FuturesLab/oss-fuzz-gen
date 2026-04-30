#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <string>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    std::string input(reinterpret_cast<const char*>(data), size);

    // Initialize an icalproperty object with a dummy property type
    icalproperty *property = icalproperty_new_xlicmimecid(input.c_str());

    // Call the function-under-test
    const char *result = icalproperty_get_xlicmimecid(property);

    // Use the result in some way to prevent optimization
    if (result) {
        // Just a dummy operation to use the result
        volatile char first_char = result[0];
        (void)first_char;
    }

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_105(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
