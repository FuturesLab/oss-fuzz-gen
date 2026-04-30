extern "C" {
    #include <libical/ical.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_790(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely use it as a C string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // If memory allocation fails, exit the fuzzer
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Check if the input data is non-empty and likely to be a valid input
    if (size > 0 && null_terminated_data[0] != '\0') {
        // Call the function-under-test
        icalproperty *prop = icalproperty_new_source(null_terminated_data);

        // Clean up
        if (prop != NULL) {
            icalproperty_free(prop);
        }
    }

    free(null_terminated_data);
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

    LLVMFuzzerTestOneInput_790(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
