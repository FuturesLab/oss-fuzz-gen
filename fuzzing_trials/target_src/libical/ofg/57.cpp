#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    if (size < sizeof(int) + 1) {
        return 0; // Ensure there's enough data for an integer and at least one character for a string
    }

    // Extract an integer from the data
    int pollitemid = *(reinterpret_cast<const int*>(data));

    // Use the remaining data as the string for icalproperty
    const char *extra_data = reinterpret_cast<const char*>(data + sizeof(int));

    // Ensure extra_data is null-terminated
    size_t extra_data_size = size - sizeof(int);
    char *null_terminated_extra_data = (char*)malloc(extra_data_size + 1);
    if (null_terminated_extra_data == NULL) {
        return 0; // Failed to allocate memory
    }
    memcpy(null_terminated_extra_data, extra_data, extra_data_size);
    null_terminated_extra_data[extra_data_size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_pollitemid(pollitemid, null_terminated_extra_data, nullptr);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(null_terminated_extra_data);

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

    LLVMFuzzerTestOneInput_57(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
