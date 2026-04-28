#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_1372(const uint8_t *data, size_t size) {
    // Ensure the data is non-empty and null-terminated to safely pass as a C-style string
    if (size == 0) {
        return 0; // No meaningful input to process
    }

    char *null_terminated_data = new char[size + 1];
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Check if the input is a valid string for the function under test
    // This can be a simple heuristic, for example, checking for valid characters or structure
    if (strchr(null_terminated_data, '\n') != nullptr) {
        delete[] null_terminated_data;
        return 0; // Skip inputs with newlines as they might not be valid
    }

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_xlicmimeoptinfo(null_terminated_data);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    delete[] null_terminated_data;

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

    LLVMFuzzerTestOneInput_1372(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
